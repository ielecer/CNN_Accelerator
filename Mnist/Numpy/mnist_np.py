import sys, os
sys.path.append(os.pardir)
import numpy as np
from dataset.mnist import load_mnist
from two_layer_net import TwoLayerNet

# Import data.
(x_train, t_train), (x_test, t_test) = \
	load_mnist(normalize=True, one_hot_label=True)

network = TwoLayerNet(input_size=784, hidden_size=50, output_size=10)

iters_num = 10000
train_size = x_train.shape[0]	# 60000
batch_size = 100
learning_rate = 0.1
train_loss_list = []
train_acc_list = []
test_acc_list = []

iter_per_epoch = max(train_size / batch_size, 1)

for i in range(iters_num):
	batch_mask = np.random.choice(train_size, batch_size)
	x_batch = x_train[batch_mask]
	t_batch = t_train[batch_mask]

	# Calculate gradients using BP.
	grad = network.gradient(x_batch, t_batch)

	# Update parameters.
	for key in ('W1', 'b1', 'W2', 'b2'):
		network.params[key] -= learning_rate * grad[key]

	# Reocrd loss rate.
	loss = network.loss(x_batch, t_batch)
	train_loss_list.append(loss)

	# Record and compare accuracy to check whether there exists overfitting.
	if i % iter_per_epoch == 0:
		train_acc = network.accuracy(x_train, t_train)
		test_acc = network.accuracy(x_test, t_test)
		train_acc_list.append(train_acc)
		test_acc_list.append(test_acc)
		print(train_acc, test_acc)