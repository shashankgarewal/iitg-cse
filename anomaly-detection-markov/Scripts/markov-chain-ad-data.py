## This script implements a Markov Chain model to detect anomalies in CPC and CPM data from ad exchanges.
import pandas as pd
import numpy as np
from collections import defaultdict
from itertools import pairwise
import matplotlib.pyplot as plt
import seaborn as sns

# pre-processes two CSV files containing timestamped data for compatibility with markov models.
def df_preprocessing(path_a, path_b, quantize: bool = False):
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
        df['cpc'] = df['cpc'].round(1)
        df['cpm'] = df['cpm'].round(1)
    
    return df

# counts transitions between sequential states in a specified column of a DataFrame.
def transition_counter(df, col: str, transition_counts = None):
    if transition_counts is None:
        transition_counts = defaultdict(lambda: defaultdict(int))
    
    for (_, curr), (_, next) in pairwise(df.iterrows()):
        
        if curr['step'] + 1 != next['step']:
            continue

        prev_state = curr[col]
        curr_state = next[col]
        transition_counts[prev_state][curr_state] += 1
        
    return transition_counts 
    
    
# Convert transition counts to transition probabilities matrix.
def transition_probs_calculator(transition_counts):
    transition_probs = defaultdict(lambda: defaultdict(float))


    for prev_state, next_states in transition_counts.items():
        total = sum(next_states.values())
        for curr_state, count in next_states.items():
            transition_probs[prev_state][curr_state] = count / total if total > 0 else 0
            
    return transition_probs

def markov_anomaly_scorer(df, transition_probs, col: str, window=2, epsilon=1e-10):
    """ Scores anomalies in a DataFrame based on a Markov Chain model with context window.

    Args:
        df (dataframe): dataframe containing the states of a {col} to score
        transition_probs (defaultdict): transition probabilities for the Markov Chain
        col (str): column name to score, e.g. 'cpc' or 'cpm'
        window (int; min:2, max:len(df)): no of states to consider anomaly scoring. Defaults to 2.
        epsilon (float, ): Placeholder for unseen transition. Defaults to 1e-10.

    Returns:
        df: modified dataframe with scores for {col} states
    """
    df = df.copy()
    df[f'{col}_score'] = 0.0

    for i in range(window, df.shape[0]):
        score = 0
        
        all_states = df.iloc[i - window:i][col].values
        if len(all_states) < 2: continue
        for from_state, to_state in pairwise(all_states):
            try:
                prob = transition_probs[from_state][to_state]
                score += np.log(prob if prob > 0 else epsilon)
            except KeyError as e:
                print('error')
                print(f"KeyError: {e} for transition {from_state} to_state {next}")
                score += np.log(epsilon)  # assign minimal likelihood to unseen transition

        ## df.iloc[i, df.columns.get_loc(f'{col}_score')] = score # deprecated
        df.at[i-window, f'{col}_score'] = np.abs(score)

    return df


def markov_anomaly_detector(unknown_df, normal_df, threshold_cpc=0.01, threshold_cpm=0.01):
    ## Detects anomalies in CPC and CPM data using a Markov Chain model.
    # threshold_cpc = normal_df['prob_cpc'].max()
    # threshold_cpm = normal_df['prob_cpm'].max()
    
    df = unknown_df.copy()
    df['cpc_anomaly'] = df['cpc_score'] > threshold_cpc
    df['cpm_anomaly'] = df['cpm_score'] > threshold_cpm
    
    return df

def plot_anomalies(df):
    plt.figure(figsize=(12, 6))
    sns.lineplot(x='timestamp', y='cpc', data=df, color='blue', label='CPC', alpha=0.5)
    sns.lineplot(x='timestamp', y='cpm', data=df, color='red', label='CPM', alpha=0.5)
    
    sns.scatterplot(data=df[df['cpc_anomaly']], x='timestamp', y='cpc', color='blue', label='CPC Anomalies', marker='o')
    sns.scatterplot(data=df[df['cpm_anomaly']], x='timestamp', y='cpm', color='red', label='CPM Anomalies', marker='o')
    
    plt.title(f'Anomalies over time')
    plt.xlabel('Step')
    plt.ylabel('Value')
    plt.legend()
    plt.show()


if __name__ == "__main__": 
    
    dfs = {}
    cpc_transition_counts = defaultdict(lambda: defaultdict(int))
    cpm_transition_counts = defaultdict(lambda: defaultdict(int))
    
    ## Load and preprocess all exchange data, since in real-world, we would not know which exchange has anomalies beforehand.
    for i in range(2, 5):
        path_cpc = f'..\\Dataset\\realAdExchange\\exchange-{i}_cpc_results.csv'
        path_cpm = f'..\\Dataset\\realAdExchange\\exchange-{i}_cpm_results.csv'
        df = df_preprocessing(path_cpc, path_cpm, quantize=True)
        dfs[f'df{i}'] = df # for access in main if needed
        cpc_transition_counts = transition_counter(df, 'cpc', cpc_transition_counts)
        cpm_transition_counts = transition_counter(df, 'cpm', cpm_transition_counts)
    
    cpc_transition_matrix = transition_probs_calculator(cpc_transition_counts)
    cpm_transition_matrix = transition_probs_calculator(cpm_transition_counts)

    markov_model = {
        'cpc': cpc_transition_matrix,
        'cpm': cpm_transition_matrix
    }
    
    for i in range(2, 5):
        dfs[f'df{i}'] = markov_anomaly_scorer(dfs[f'df{i}'], cpc_transition_matrix, 'cpc', window=3)
        dfs[f'df{i}'] = markov_anomaly_scorer(dfs[f'df{i}'], cpm_transition_matrix, 'cpm', window=5)
    
    # df2 appears as the normal data, thereby all points in that range are considered as normal.    
    dfs['df3'] = markov_anomaly_detector(dfs['df3'], dfs['df2'], 
                                         threshold_cpc = dfs['df2']['cpc_score'].max(), 
                                         threshold_cpm = dfs['df2']['cpm_score'].max())
    dfs['df4'] = markov_anomaly_detector(dfs['df4'], dfs['df2'], 
                                         threshold_cpc = dfs['df2']['cpc_score'].max(), 
                                         threshold_cpm = dfs['df2']['cpm_score'].max())
    
    plot_anomalies(dfs['df3'])
    plot_anomalies(dfs['df4'])
    