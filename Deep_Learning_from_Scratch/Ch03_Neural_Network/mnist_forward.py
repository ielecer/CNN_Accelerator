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

accuracy_cnt = 0
for i in range(len(x)):
	y = predict(network, x[i])
	p = np.argmax(y)
	if p == t[i]:
		accuracy_cnt += 1

print("Accuracy:" + str(float(accuracy_cnt) / len(x)))
