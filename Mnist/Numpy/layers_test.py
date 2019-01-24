# Test classes in script layers.py.

# Import required libraries and classes.
import numpy as np
from layers import Relu, Sigmoid, Affine, SoftmaxWithLoss

#############################
# Test class Relu.
#############################
# Instantiate class Relu.
relu = Relu()

# Define x and dout with np.array data type.
x = np.array([[1.0, 0.5], [-2.0, 3.0]])
dout = np.array([[1.0, 0.5], [-2.0, 3.0]])

# # Pass!
# print(relu.forward(x))
# print(relu.backward(dout))

#############################
# Test class Sigmoid.
#############################
# Instantiate class Sigmoid.
sigmoid = Sigmoid()

# Define x and dout with np.array data type.
x = np.array([[1.0, 0.5], [-2.0, 3.0]])
dout = np.array([[1.0, 0.5], [-2.0, 3.0]])

# # Pass!
# print(sigmoid.forward(x))
# print(sigmoid.backward(dout))

#############################
# Test class Affine.
#############################
# Define parameters of class Affline
W = np.array([[1, 1, 1], [2, 2, 2]])		# (2, 3)
b = np.array([0, 0, 0])									# (3, )

# Instantiate class Affine.
affine = Affine(W, b)

# Define x and dout with np.array data type.
x = np.array([[1, 2], [3, 4]]) 					# (2, 2)
dout = np.array([[1, 2, 3], [4, 5, 6]]) # (2, 3)

# # Pass!
# print(affine.forward(x))
# print(affine.backward(dout))
# print(affine.dW)
# print(affine.db)

#############################
# Test class SoftmaxWithLoss.
#############################
# Instantiate class SoftmaxWithLoss.
softmaxWithLoss = SoftmaxWithLoss()

# Define x and t with np.array data type.
x = np.array([[1, 2], [3, 4]]) 					# (2, 2)
t = np.array([1, 1])										# (2, )

# # Pass!
# print(softmaxWithLoss.forward(x, t))
# print(softmaxWithLoss.y)
# print(softmaxWithLoss.backward())
