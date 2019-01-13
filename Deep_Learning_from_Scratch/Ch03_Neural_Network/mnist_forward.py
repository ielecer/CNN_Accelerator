# coding: utf-8
import sys, os
sys.path.append(os.pardir)		# Add parent directory into system path.
from dataset.mnist import load_mnist
import numpy as np
import pickle
from PIL import Image 		# PIL: Python Image Library

def img_show(img):
	pil_img = Image.fromarray(np.uint8(img))
	pil_img.show()

def softmax(a):
	c = np.max(a)
	exp_a = np.exp(a - c)		# avoid overflow when a is large enough
	sum_exp_a = np.sum(exp_a)
	y = exp_a / sum_exp_a
	return y

def sigmoid(x):
	return 1 / (1 + np.exp(-x))

# It costs few minutes for the first loading.
def get_data():
	(x_train, t_train), (x_test, t_test) = \
	load_mnist(normalize=True, flatten=True, one_hot_label=False)
	return x_test, t_test  # Data used to test.

# Load parameters which come from learning phase.
def init_network():
	with open("sample_weight.pkl", 'rb') as f:
		network = pickle.load(f)
	return network

def predict(network, x):
	W1, W2, W3 = network['W1'], network['W2'], network['W3']
	b1, b2, b3 = network['b1'], network['b2'], network['b3']

	a1 = np.dot(x, W1) + b1
	z1 = sigmoid(a1)
	a2 = np.dot(z1, W2) + b2
	z2 = sigmoid(a2)
	a3 = np.dot(z2, W3) + b3
	y = softmax(a3)
	return y

x, t = get_data()
network = init_network()

# # Check the shape of input data and weights
# W1, W2, W3 = network['W1'], network['W2'], network['W3']
# print(x.shape)
# print(len(x))
# print(x[0].shape)
# print(W1.shape)
# print(W2.shape)
# print(W3.shape)

batch_size = 100		# batch processing
accuracy_cnt = 0
for i in range(0, len(x), batch_size):
	x_batch = x[i:i+batch_size]
	y_batch = predict(network, x_batch)
	# axis=0: 0th dimension indicates column direction.
	# axis=1: 1st dimension indicates row direction.
	# np.argmax: access the index of maximum value for the whole row direction.
	p = np.argmax(y_batch, axis=1)
	# Compare 100 results with 100 tags to get 100 boolean values and
	# then sum them all.
	accuracy_cnt += np.sum(p == t[i:i+batch_size])

print("Accuracy:" + str(float(accuracy_cnt) / len(x)))
