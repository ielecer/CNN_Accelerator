from gradient import numerical_gradient, function_2
import numpy as np

def gradient_descent(f, init_x, lr=0.01, step_num=100):
	x = init_x

	for i in range(step_num):
		grad = numerical_gradient(f, x)
		x -= lr * grad

	return x

init_x = np.array([-3.0, 4.0])
print(gradient_descent(function_2, init_x, lr=0.1, step_num=100))