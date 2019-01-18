import numpy as np
import torch

np_data = np.arange(6).reshape((2, 3))
torch_data = torch.from_numpy(np_data)
tensor2array = torch_data.numpy()

print(
			'\nnumpy', np_data,
			'\ntorch', torch_data,
			'\ntensor2array', tensor2array
	)