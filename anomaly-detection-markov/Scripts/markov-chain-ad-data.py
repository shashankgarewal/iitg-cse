import pandas as pd
import numpy as np
from collections import defaultdict
from itertools import pairwise
import matplotlib.pyplot as plt
import seaborn as sns


def df_preprocessing(path_a, path_b, quantize: bool = False):
    #read the dataframes
    dfa = pd.read_csv(path_a)
    dfb = pd.read_csv(path_b)
    
    #convert timestamp to datetime
    dfa['timestamp'] = pd.to_datetime(dfa['timestamp'])
    dfb['timestamp'] = pd.to_datetime(dfb['timestamp'])
    
    #rename columns and merge
    dfa = dfa.rename(columns={'value': 'cpc'})
    dfb = dfb.rename(columns={'value': 'cpm'})
    df = pd.merge(dfa, dfb, on='timestamp', how='outer')
    
    df['step'] = (df['timestamp'] - df['timestamp'].min()).dt.total_seconds() / 3600
    if quantize:
        # Quantize the 'cpc' and 'cpm' columns to 3 decimal places
        df['cpc'] = df['cpc'].round(2)
        df['cpm'] = df['cpm'].round(2)
    
    return df


def transition_counter(df, col: str, transition_counts = None):
    if transition_counts is None:
        transition_counts = defaultdict(lambda: defaultdict(int))
    
    for (_, curr), (_, next) in pairwise(df.iterrows()):
        
        if curr['step'] + 1 != next['step']:
            continue

        from_state = curr[col]
        to_state = next[col]
        transition_counts[from_state][to_state] += 1
        
    return transition_counts 
    
    
# Convert counts to probabilities
def estimate_markov_probs(transition_counts):
    transition_probs = defaultdict(lambda: defaultdict(float))


    for curr_state, next_states in transition_counts.items():
        total = sum(next_states.values())
        for next_state, count in next_states.items():
            transition_probs[curr_state][next_state] = count / total if total > 0 else 0
            
    return transition_probs


def df_probs(df, transition_probs, col: str, threshold=0):
    df = df.copy()
    df['anomaly'] = False
    
    for (id, curr), (_, next) in pairwise(df.iterrows()):
        if curr['step'] == next['step']:
            df.at[id, f'{col}_anomaly'] = True
        if curr['step'] + 1 != next['step']:
            continue
        
        prob = transition_probs[curr[col]][next[col]]
        df.at[id, f'prob_{col}'] = prob
        # df.at[id, f'log_prob_{col}'] = np.log(prob)
        
        if prob < threshold:
            df.at[id, f'{col}_anomaly'] = True
        
    return df

def anomaly_detection(unknown_df, normal_df):
    threshold_cpc = normal_df['prob_cpc'].max()
    threshold_cpm = normal_df['prob_cpm'].max()
    
    df = unknown_df.copy()
    df['cpc_anomaly'] = df['prob_cpc'] > threshold_cpc
    df['cpm_anomaly'] = df['prob_cpm'] > threshold_cpm
    
    return df

def plot_anomalies(df):
    plt.figure(figsize=(12, 6))
    sns.lineplot(x='timestamp', y='cpc', data=df, color='blue', label='CPC', alpha=0.5)
    sns.lineplot(x='timestamp', y='cpm', data=df, color='red', label='CPM', alpha=0.5)
    
    sns.scatterplot(data=df[df['cpc_anomaly']], x='timestamp', y='cpc', color='blue', label='CPC Anomalies', marker='o')
    sns.scatterplot(data=df[df['cpm_anomaly']], x='timestamp', y='cpm', color='red', label='CPM Anomalies', marker='*')
    
    plt.title(f'Anomalies over time')
    plt.xlabel('Step')
    plt.ylabel('Value')
    plt.legend()
    plt.show()

if __name__ == "__main__": 
    
    dfs = {}
    cpc_transition_counts = defaultdict(lambda: defaultdict(int))
    cpm_transition_counts = defaultdict(lambda: defaultdict(int))
    
    
    for i in range(2, 5):
        path_cpc = f'..\\Dataset\\realAdExchange\\exchange-{i}_cpc_results.csv'
        path_cpm = f'..\\Dataset\\realAdExchange\\exchange-{i}_cpm_results.csv'
        df = df_preprocessing(path_cpc, path_cpm, quantize=True)
        dfs[f'df{i}'] = df # for access in main if needed
        cpc_transition_counts = transition_counter(df, 'cpc', cpc_transition_counts)
        cpm_transition_counts = transition_counter(df, 'cpm', cpm_transition_counts)
    
    cpc_transition_matrix = estimate_markov_probs(cpc_transition_counts)
    cpm_transition_matrix = estimate_markov_probs(cpm_transition_counts)

    markov_model = {
        'cpc': cpc_transition_matrix,
        'cpm': cpm_transition_matrix
    }
    
    for i in range(2, 5):
        dfs[f'df{i}'] = df_probs(dfs[f'df{i}'], cpc_transition_matrix, 'cpc')
        dfs[f'df{i}'] = df_probs(dfs[f'df{i}'], cpm_transition_matrix, 'cpm')
        
    dfs['df3'] = anomaly_detection(dfs['df3'], dfs['df2'])
    dfs['df4'] = anomaly_detection(dfs['df4'], dfs['df2'])
    
    plot_anomalies(dfs['df3'])
    plot_anomalies(dfs['df4'])