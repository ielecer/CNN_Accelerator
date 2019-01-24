# Define all the layer classes here needed to build a neural network with
# forward and backward propagation.

# Import required libraries and classes.
import numpy as np
from functions import softmax, cross_entropy_error

# Define class Relu about activiation function Relu with forward and
# backward propagation.
class Relu:
	def __init__(self):
		# self.mask will be assigned in forward() and utilized in backward().
		self.mask = None

	# It element in array x is larger than 0, it keeps. Otherwise it sets to 0.
	def forward(self, x):
		# Assign boolean type data to array self.mask with the same shape as x.
		self.mask = (x <= 0)
		# Define out variable with the same content as x.
		out = x.copy()
		# If the element in array self.mask is True, then the corresponding element 
		# in array out will be set to 0.
		out[self.mask] = 0

		return out

	# It element in array x is larger than 0, it keeps. Otherwise it sets to 0.
	def backward(self, dout):
		dout[self.mask] = 0
		dx = dout

		return dx

# Define class Sigmoid about activiation function Sigmoid with forward and
# backward propagation.
class Sigmoid:
	def __init__(self):
		# self.out will be assigned in forward() and utilized in backward().
		self.out = None

	def forward(self, x):
		out = 1 / (1 + np.exp(-x))
		self.out = out

		return out

	def backward(self, dout):
		dx = dout * (1.0 - self.out) * self.out

		return dx

# Define class Affine about activiation function Affine with forward and
# backward propagation.
class Affine:
	def __init__(self, W, b):
		self.W = W
		self.b = b
		self.x = None
		self.dw = None
		self.db = None

	def forward(self, x):
		self.x = x
		out = np.dot(x, self.W) + self.b

		return out

	def backward(self, dout):
		dx = np.dot(dout, self.W.T) # T: Transposition
		self.dW = np.dot(self.x.T, dout)
		# sum of dout in axis=0 (vertical direction)
		self.db = np.sum(dout, axis=0)

		return dx

# Define class SoftmaxWithLoss about activiation function SoftmaxWithLoss with 
# forward and backward propagation.
class SoftmaxWithLoss:
	def __init__(self):
		self.loss = None
		self.y = None 	# output of softmax
		self.t = None 	# ont-hot vector

	def forward(self, x, t):
		self.t = t
		self.y = softmax(x)
		self.loss = cross_entropy_error(self.y, self.t)

		return self.loss

	def backward(self, dout=1):
		batch_size = self.t.shape[0]
		dx = (self.y - self.t) / batch_size # Why divides batch_size?

		return dx


	

