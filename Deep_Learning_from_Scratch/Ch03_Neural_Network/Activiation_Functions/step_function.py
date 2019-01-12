import numpy as np

def step_function(x):
	y = x > 0		# Compare x with 0 which returns boolean type to y.
	return y.astype(np.int)		# Transform boolean type to int value.

# Test function
print(step_function(np.array([-1.0, 2.0])))