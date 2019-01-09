# -*- coding: utf-8 -*-
import input_data
import tensorflow as tf
import numpy as np
mnist = input_data.read_data_sets('MNIST_data', one_hot=True)
sess = tf.InteractiveSession()

def Record_Tensor(tensor, name):
	print ("Recording tensor " + name + " ...")
	f = open('./record/'+ name + '.dat', 'w')
	array = tensor.eval()
	#print ("The range: ["+str(np.min(array))+":"+str(np.max(array))+"]")
	if np.size(np.shape(array)) == 1:
		Record_Array1D(array, name, f)
	else:
		if np.size(np.shape(array)) == 2:
			Record_Array2D(array, name, f)
		else:
			if np.size(np.shape(array)) == 3:
				Record_Array3D(array, name, f)
			else:
				Record_Array4D(array, name, f)
	f.close()

def Record_Array1D(array, name, f):
	for i in range(np.shape(array)[0]):
		f.write(str(array[i]) + "\n");

def Record_Array2D(array, name, f):
	for i in range(np.shape(array)[0]):
		for j in range(np.shape(array)[1]):
			f.write(str(array[i][j]) + "\n");

def Record_Array3D(array, name, f):
	for i in range(np.shape(array)[0]):
		for j in range(np.shape(array)[1]):
			for k in range(np.shape(array)[2]):
				f.write(str(array[i][j][k]) + "\n");

def Record_Array4D(array, name, f):
	for i in range(np.shape(array)[0]):
		for j in range(np.shape(array)[1]):
			for k in range(np.shape(array)[2]):
				for l in range(np.shape(array)[3]):
					f.write(str(array[i][j][k][l]) + "\n");

# Input Layer
# tf.name_scope(): A context manager for use when defining a Python op.
with tf.name_scope('input'):
	# tf.placeholder(dtype, shape=None, name=None): inserts a placeholder
	# for a tensor that will be always fed.
	x = tf.placeholder("float", shape=(None, 784), name="image_input")
	y_ = tf.placeholder("float", shape=(None, 10), name="label_input")

def weight_variable(shape):
	# tf.truncated_normal(shape, mean=0.0, stddev=1.0, dtype=tf.float32,
	# seed=None, name=None): Outputs random values from a truncated 
	# normal distribution.
	initial = tf.truncated_normal(shape, stddev=0.1);
	# Create a variable.
	# tf.Variable(<initial-value>, name=<optional-name>): the tf.Variable() 
	# constructor requires an initial value for the variable, which can 
	# be a Tensor of any type and shape. 
	return tf.Variable(initial)

def bias_variable(shape):
	# tf.constant(value, dtype=None, shape=None, name='Const', verify_shape
	# =False): creates a constant tensor.
	initial = tf.constant(0.1, shape=shape) # bias = 0.1
	return tf.Variable(initial)

def conv2d(x, W):
	# tf.nn.conv2d(input, filter, strides, padding, use_cudnn_on_gpu=True,
	# data_format='NHWC', dilations=[1, 1, 1, 1], name=None): computes a 2-D 
	# convolution given 4-D input and filter tensors. 
	# Must have strides[0] = strides[3] = 1. For the most common case of the
	# same horizontal and vertices strides, strides = [1, stride, stride, 1].
	return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')

def max_pool_2x2(x):
	# tf.nn.max_pool(value, ksize, strides, padding, data_format='NHWC',
	# name=None): Performs the max pooling on the input.
	return tf.nn.max_pool(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')

# First Convolutional Layer
with tf.name_scope('1st_CNN'):
	W_conv1 = weight_variable([3, 3, 1, 16]) # 4-D tensor: 3*3*1*16, 16 is depth
	b_conv1 = bias_variable([16])
	# -1 can be used to infer the shape of (?). tf.reshape() turns x into  a 
	# 4-D tensor: (?)*28*28*1, where (?) depends on x's shape which is a 2-D 
	# tensor (None, 784).
	x_image = tf.reshape(x, [-1, 28, 28, 1])
	h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1)
	h_pool1 = max_pool_2x2(h_conv1)

# Second Convolutional Layer
with tf.name_scope('2rd_CNN'):
	W_conv2 = weight_variable([3, 3, 16, 32])
	b_conv2 = bias_variable([32])
	h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)
	h_pool2 = max_pool_2x2(h_conv2)

# Densely Connected Layer
with tf.name_scope('Densely_NN'):
	W_fc1 = weight_variable([ 7* 7* 32, 128])
	b_fc1 = bias_variable([128])
	h_pool2_flat = tf.reshape(h_pool2, [-1, 7*7*32])
	h_fc1=tf.nn.relu(tf.matmul(h_pool2_flat , W_fc1) + b_fc1)

# Dropout
with tf.name_scope('Dropout'):
	keep_prob = tf.placeholder("float")
	h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)

# Readout Layer
with tf.name_scope('Softmax'):
	W_fc2 = weight_variable([128, 10])
	b_fc2 = bias_variable([10])
	y_conv = tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2) + b_fc2)

with tf.name_scope('Loss'):
	cross_entropy = -tf.reduce_sum(y_*tf.log(y_conv))

with tf.name_scope('Train'):
	train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)

with tf.name_scope('Accuracy'):
	correct_prediction = tf.equal(tf.argmax(y_conv ,1), tf.argmax(y_,1))
	accuracy = tf.reduce_mean(tf.cast(correct_prediction , "float"))

# merged = tf.merge_all_summaries()
# writer = tf.train.SummaryWriter("logs/", sess.graph)
writer = tf.summary.FileWriter("logs/", tf.get_default_graph())
writer.close()

tf.initialize_all_variables().run()

for i in range(10000):
	batch = mnist.train.next_batch(50);
	if i%20 == 0:
		train_accuracy = accuracy.eval(feed_dict={x:batch[0], y_: batch[1], keep_prob:1.0});
		print("step %d, training accuracy %g"%(i, train_accuracy));
	train_step.run(feed_dict={x: batch[0], y_: batch[1], keep_prob:0.5});

print("test accuracy %g"%accuracy.eval(feed_dict={x: mnist.test.images, y_: mnist.test.labels, keep_prob: 1.0}))

# Record weights and bias for all the layers
Record_Tensor(W_conv1, "W_conv1")
Record_Tensor(b_conv1, "b_conv1")
Record_Tensor(W_conv2, "W_conv2")
Record_Tensor(b_conv2, "b_conv2")
Record_Tensor(W_fc1, "W_fc1")
Record_Tensor(b_fc1, "b_fc1")
Record_Tensor(W_fc2, "W_fc2")
Record_Tensor(b_fc2, "b_fc2")
sess.close()
