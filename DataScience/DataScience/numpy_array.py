import numpy as np

def output():
    print('a',a)
    print('b', b)
    print('c', c)
    print('d', d)
    print('e', e)
    print('f', f)
    print('g', g)
    print('h', h)
    print("i", i)
    print("j", j)
    print("hello, world")

a = np.array([1, 2, 5, 7, 3], dtype  = "float32")
b = np.array([range(i, i+3) for i in [2, 5, 4]])
c = np.zeros(10, dtype = "int32")
d = np.ones((3, 5), dtype = "float32")
e = np.arange(3,9)
f = np.full((2,3), 5)
g = np.linspace(0, 1, 5)
h = np.random.random((3, 3))
i = np.random.randint(0, 10, 4)
j = np.eye(3)

output()


