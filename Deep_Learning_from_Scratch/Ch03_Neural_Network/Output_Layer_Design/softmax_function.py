import numpy as np

def softmax_function(a):
	c = np.max(a)
	exp_a = np.exp(a - c)		# avoid overflow when a is large enough
	sum_exp_a = np.sum(exp_a)
	y = exp_a / sum_exp_a

	return y

a = np.array([1010, 1000, 990])
y = softmax_function(a)
print(y)
print(np.sum(y))

