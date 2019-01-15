import sys, os
sys.path.append(os.pardir)
import numpy as np
from dataset.mnist import load_mnist
from two_layer_net import TwoLayerNet

(x_train, t_train), (x_test, t_test) = \
	load_mnist(normalize=True, one_hot_label=True)

train_loss_list = []

# super parameters
iters_num = 10000
train_size = x_train.shape[0]
batch_size = 100
learning_rate = 0.1

network = TwoLayerNet(input_size=784, hidden_size=50, output_size=10)

for i in range(iters_num):
	# access mini-batch
	batch_mask = np.random.choice(train_size, batch_size)
	x_batch = x_train[batch_mask]
	t_batch = t_train[batch_mask]

	# calculate gradient
	grad = network.numerical_gradient(x_batch, t_batch)
	# grad = network.gradient(x_batch, t_batch) # high speed version

	# update parameters
	for key in ('W1', 'b1', 'W2', 'b2'):
		network.params[key] -= learning_rate * grad[key]

	# record learning process
	loss = network.loss(x_batch, t_batch)
	train_loss_list.append(loss)