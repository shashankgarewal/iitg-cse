import pandas as pd
import numpy as np
from collections import defaultdict

def df_merge(path_a, path_b):
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
    
    df['steps'] = (df['timestamp'] - df['timestamp'].min()).dt.total_seconds() / 3600
    
    return df

# ad records have some gaps in recorded timestamps

transition_counts = defaultdict(lambda: defaultdict(int))

for entry in df:

    if entry['step'].skip(1) - entry['step'] != 1.0:
        continue
    transition_counts[entry['cpc']][entry['cpc'].skip[1]] += 1
    
    
# Convert counts to probabilities
transition_probs = defaultdict(dict)

for curr_state, next_states in transition_counts.items():
    total = sum(next_states.values())
    for next_state, count in next_states.items():
        transition_probs[curr_state][next_state] = count / total
    

def df_to_markov_chain(df):
    #sort by timestamp
    df = df.sort_values(by='timestamp')
    df['step'] = int((df['timestamp'] - df['timestamp'].min()).total_seconds() / 3600)
    
    #create a new column for the next cpc and cpm values
    df['next_cpc'] = df['cpc'].shift(-1)
    df['next_cpm'] = df['cpm'].shift(-1)
    
    #drop the last row since it has no next value
    df = df[:-1]
    
    #create a markov chain dataframe
    markov_chain_df = df[['cpc', 'cpm', 'next_cpc', 'next_cpm']]
    
    return markov_chain_df