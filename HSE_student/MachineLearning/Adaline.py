'''
    Реализация Адалайна в данном коде взята из книги 
    "Машинное обучение с PyTorch и ScikitLearning" в качестве 
     обучения и подкрепления теории на практике
'''

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

class AdalineGD:
    eta : float
    n_iter : int
    random_state : int
    
    def __init__(self, eta=0.01, n_iter=50, random_state=1):
        self.eta = eta
        self.n_iter = n_iter
        self.random_state = random_state
        
    def fit(self, X, y):
        rgen = np.random.RandomState(self.random_state)
        self.w_ = rgen.normal(loc=0.0, scale=0.01, size=X.shape[1])
        
        self.b_ = np.float64(0.)
        self.losses_ = []
        
        for _ in range(self.n_iter):
            net_input = self.net_input(X)
            output = self.activation(net_input)
            errors = (y - output)
            self.w_ += self.eta * 2.0 * X.T.dot(errors) / X.shape[0]
            self.b_ += self.eta * 2.0 * errors.mean()
            loss = (errors**2).mean()
            self.losses_.append(loss)
            
        return self
    
    def net_input(self, X):
        return np.dot(X, self.w_) + self.b_
    
    def activation(self, X):
        return X
    
    def predict(self, X):
        return np.where(self.activation(self.net_input(X)) >= 0.5, 1, 0)


try:
    s = 'https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data'
    print('From URL:', s)
    df = pd.read_csv(s,
                     header=None,
                     encoding='utf-8')
    
except:
    s = "C:/Codes/HSE_learning/HSE_student/MachineLearning/iris.data"
    print('From local Iris path:', s)
    df = pd.read_csv(s,
                     header=None,
                     encoding='utf-8')
    
df.tail()
y = df.iloc[0:100, 4].values
y = np.where(y == 'Iris-setosa', 0, 1)
X = df.iloc[0:100, [0, 2]].values


'''Сравнение результатов Адалайн при разных скоростях.'''
fig, ax = plt.subplots(nrows=1, ncols=2, figsize=(10, 4))
adal = AdalineGD(n_iter=50, eta=0.1).fit(X, y)
ax[0].plot(range(1, len(adal.losses_) + 1), np.log10(adal.losses_), marker='o')
ax[0].set_xlabel('Эпохи')
ax[0].set_ylabel('log(Среднеквадратичная ошибка)')
ax[0].set_title('Adaline - скорость обучения 0.1')

ada2 = AdalineGD(n_iter=50, eta=0.01).fit(X, y)
ax[1].plot(range(1, len(ada2.losses_) + 1), ada2.losses_, marker='o')
ax[1].set_xlabel('Эпохи')
ax[1].set_ylabel('log(Среднеквадратичная ошибка)')
ax[1].set_title('Adaline - скорость обучения 0.00001')
plt.show()