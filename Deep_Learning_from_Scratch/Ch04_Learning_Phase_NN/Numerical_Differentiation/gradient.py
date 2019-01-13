import numpy as np

# multivariate function
def function_2(x):
	return x[0] ** 2 + x[1] ** 2

# make gradient
def numerical_gradient(f, x):
	h = 1e-4
	# Generate an array with the same shape as x to store gradients.
	grad = np.zeros_like(x)

	for idx in range(x.size):
		# use variable tem_val to store the initial value of x[idx].
		tmp_val = x[idx]
		# calculate f(x+h)
		x[idx] = tmp_val + h
		fxh1 = f(x)

		# calculate f(x-h)
		x[idx] = tmp_val - h
		fxh2 = f(x)

		grad[idx] = (fxh1 - fxh2) / (2 * h)
		# Recover the initial value of x[idx] to the changed x[idx].
		x[idx] = tmp_val

	return grad

print(numerical_gradient(function_2, np.array([3.0, 4.0])))
print(numerical_gradient(function_2, np.array([0.0, 2.0])))
print(numerical_gradient(function_2, np.array([3.0, 0.0])))
