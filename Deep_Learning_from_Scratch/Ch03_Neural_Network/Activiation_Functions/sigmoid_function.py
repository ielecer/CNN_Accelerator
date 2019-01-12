import numpy as np

def sigmoid_function(x):
	return 1 / (1 + np.exp(-x))

# Test function
x = np.array([-1.0, 1.0, 2.0])
print(sigmoid_function(x))
