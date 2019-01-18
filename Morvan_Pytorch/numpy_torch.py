import torch
import numpy as np

# abs
data = [[1, 2], [3, 4]]
tensor = torch.FloatTensor(data)		# 32bit

print(
			'\nabs',
			'\nnumpy: ', np.abs(data),
			'\ntorch: ', torch.abs(tensor)
	)

print(
			'\nabs',
			'\nnumpy: ', np.matmul(data, data),
			'\ntorch: ', torch.mm(tensor, tensor)
	)