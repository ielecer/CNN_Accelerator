import numpy as np

def relu_function(x):
	return np.maximum(0, x)

# Test function
x = np.array([-1.0, 1.0, 2.0])
print(relu_function(x))