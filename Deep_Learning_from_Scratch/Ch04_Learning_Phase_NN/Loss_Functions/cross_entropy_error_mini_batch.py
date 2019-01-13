import numpy as np

def cross_entropy_error(y, t):
	if y.ndim == 1:		# One-dimensional array but whose batch_size is not 1.
		# reshape t and y to 2D arrays with batch_size=1
		t = t.reshape(1, t.size)
		y = y.reshape(1, y.size)

	delta = 1e-7
	batch_size = y.shape[0]
	return -np.sum(t * np.log(y + delta)) / batch_size		# normalization

t = [0, 0, 1, 0, 0, 0, 0, 0, 0, 0]

y1 = [0.1, 0.05, 0.6, 0.0, 0.05, 0.1, 0.0, 0.1, 0.0, 0.0]
print(cross_entropy_error(np.array(y1), np.array(t)))

y2 = [0.1, 0.05, 0.1, 0.0, 0.05, 0.1, 0.0, 0.6, 0.0, 0.0]
print(cross_entropy_error(np.array(y2), np.array(t)))

# f(y3) = [f(y1) + f(y2)] / 2
# Since y3 is 2D, it needs to reshape t to 2D.
y3 = [[0.1, 0.05, 0.1, 0.0, 0.05, 0.1, 0.0, 0.6, 0.0, 0.0],
	[0.1, 0.05, 0.6, 0.0, 0.05, 0.1, 0.0, 0.1, 0.0, 0.0]]
print(cross_entropy_error(np.array(y3), np.array(t)))