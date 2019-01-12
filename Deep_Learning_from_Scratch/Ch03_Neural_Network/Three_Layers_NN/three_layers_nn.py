# Build a three-layer neural network
import numpy as np

# Activiation functions
def sigmoid_function(x):
	return 1 / (1 + np.exp(-x))
# Only act as activiation function for output layer
def identity_function(x):
	return x

# Input data
X = np.array([1.0, 0.5])

# First layer
W1 = np.array([[0.1, 0.3, 0.5], [0.2, 0.4, 0.6]])
B1 = np.array([0.1, 0.2, 0.3])

A1 = np.dot(X, W1) + B1
print(A1)

Z1 = sigmoid_function(A1)
print(Z1)

# Second layer
W2 = np.array([[0.1, 0.4], [0.2, 0.5], [0.3, 0.6]])
B2 = np.array([0.1, 0.2])

A2 = np.dot(Z1, W2) + B2
print(A2)

Z2 = sigmoid_function(A2)
print(Z2)

# Third layer (Output layer)
W3 = np.array([[0.1, 0.3], [0.2, 0.4]])
B3 = np.array([0.1, 0.2])

A3 = np.dot(Z2, W3) + B3
print(A3)

Y = identity_function(A3)
print(Y)