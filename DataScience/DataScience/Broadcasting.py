import numpy as np

a = [1,2,3]
b = np.arange(3,9)[:, np.newaxis]
c = a + b
d = np.arange(1,10).reshape((3,3))

print(a,'\n')
print(b,'\n')
print(c,'\n')
print(d,'\n')