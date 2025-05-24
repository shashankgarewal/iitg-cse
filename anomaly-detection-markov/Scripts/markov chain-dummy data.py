# This script demonstrates a simple Markov Chain model for anomaly detection on a sequence of dummy events. 
# It builds a transition matrix from normal sequences and computes the log-probability of test sequences to identify anomalies.

from collections import defaultdict
import numpy as np

normal_sequences = [
    ['login', 'view_page', 'add_to_cart', 'checkout', 'logout'],
    ['login', 'view_page', 'logout'],
    ['login', 'view_page', 'add_to_cart', 'view_page', 'checkout', 'logout'],
    ['login', 'view_page', 'view_page', 'logout'],
]

# Build transition counts matrix with default values of 0
transition_counts = defaultdict(lambda: defaultdict(int))
for seq in normal_sequences:
    for i in range(len(seq) - 1):
        curr_state = seq[i]
        next_state = seq[i + 1]
        transition_counts[curr_state][next_state] += 1


# Built transition probability matrix for markov chain
transition_probs = defaultdict(dict)
for curr_state, next_states in transition_counts.items():
    total = sum(next_states.values())
    for next_state, count in next_states.items():
        transition_probs[curr_state][next_state] = count / total

# Function to compute sequence log-probability
def compute_log_probability(sequence, matrix):
    log_prob = 0
    for i in range(len(sequence) - 1):
        curr_state = sequence[i]
        next_state = sequence[i + 1]
        prob = matrix.get(curr_state, {}).get(next_state, 1e-6)  # Use small value for unseen transitions instead of 0
        log_prob += np.log(prob)
    return log_prob

# Test sequences
test_sequences = [
    ['login', 'view_page', 'add_to_cart', 'checkout', 'logout'],  # Normal
    ['login', 'add_to_cart', 'checkout', 'logout'],              # Anomalous
    ['view_page', 'login', 'checkout', 'logout'],        # Anomalous
]

# Threshold for anomaly detection
threshold = -10

# Check each sequence
for seq in test_sequences:
    logp = compute_log_probability(seq, transition_probs)
    is_anomaly = logp < threshold
    print(f"Sequence: {seq}")
    print(f"Log Probability: {logp:.4f}")
    print(f"Anomalous? {'YES' if is_anomaly else 'NO'}\n")
