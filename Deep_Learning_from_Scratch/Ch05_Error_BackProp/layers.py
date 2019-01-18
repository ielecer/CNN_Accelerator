import numpy as np

class Relu:
	def __init__(self):
		self.mask = None

	def forward(self, x):
		self.mask = (x <= 0)
		out = x.copy()
		out[self.mask] = 0

		return out

	def backward(self, dout):
		dout[self.mask] = 0
		dx = dout

		return dx

class Sigmoid:
	def __init__(self):
		delf.out = None

	def forward(self, x):
		out = 1 / (1 + np.exp(-x))
		self.out = out

		return out

	def backward(self, dout)
		dx = dout * (1.0 - self.out) * self.out

		return dx

# x = np.array([[1.0, -0.5], [-2.0, 3.0]])
# print(x)
# mask = (x <= 0)
# print(mask)
