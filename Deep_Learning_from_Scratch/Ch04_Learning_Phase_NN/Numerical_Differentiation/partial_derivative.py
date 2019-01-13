# (partial) derivative
def numerical_diff(f, x):
	h = 1e-4		# 0.0001
	return (f(x+h) - f(x-h)) / (2*h)

# multivariate function
def function_2(x):
	return x[0]**2 + x[1]**2

# univarite function
def function_tmp1(x0):
	return x0**2 + 4.0**2

def function_tmp2(x1):
	return 3.0**2 + x1**2


print(numerical_diff(function_tmp1, 3.0))
print(numerical_diff(function_tmp2, 4.0))
