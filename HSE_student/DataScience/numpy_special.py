import numpy as np
from scipy import special

x = [1, 6, 10]

print("gamma(x) =", special.gamma(x))
print("gammaln(x) =", special.gammaln(x))
print("beta(x, 2) =", special.beta(x, 2))
x = np.arange(10)
y = np.zeros(10)
y = np.power(2, x, out=y[::2])
print(y)