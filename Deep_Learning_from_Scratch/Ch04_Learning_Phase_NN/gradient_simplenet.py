import sys, os
sys.path.append(os.pardir)
import numpy as np
from common.functions import softmax, cross_entropy_error
from common.gradient import numerical_gradient

class simpleNet:
	def __init__(self):
		self.W = np.random.randn(2, 3) # Initialized with gauss distribution

	def predict(self, x):
		return np.dot(x, self.W)

	def loss(self, x, t):
		z = self.predict(x)
		y = softmax(z)
		loss = cross_entropy_error(y, t)

		return loss

# def f(W):
# 	return net.loss(x, t)
f = lambda w: net.loss(x, t)

net = simpleNet()
print(net.W)
x = np.array([0.6, 0.9])
print(net.predict(x))
t = np.array([0, 0, 1]) # tag
print(net.loss(x, t))

dW = numerical_gradient(f, net.W)
print(dW)