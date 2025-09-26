import numpy as np

class Neuron:
    def __init__(self, w=0.1, bias=0.1):
        self.w = w
        self.bias = bias
    
    def predict(self, x):
        return x * self.w + self.bias
    
    def train(self, X, y, learning_rate=0.01, epochs=1000):
        for epoch in range(epochs):
            total_error = 0
            
            for x, target in zip(X, y):
                prediction = self.predict(x)
                error = prediction - target
                
                self.w -= learning_rate * error * x
                self.bias -= learning_rate * error
                
                total_error += abs(error)
            
            if epoch % 10 == 0:
                print(f"Эпоха {epoch}, w={self.w:.2f}, bias={self.bias:.2f}, Ошибка={total_error:.2f}")
            
            if total_error < 0.001:
                print(f"Обучение завершено на эпохе {epoch}!")
                break

X = np.arange(10)
y = np.arange(10) *15 + 10

neuron = Neuron()
neuron.train(X, y)

print("\nТестирование:")
for x in X:
    print(f"{x} -> {neuron.predict(x):.1f} (ожидается: {x*15 + 10})")

print(f"\nИтоговые параметры: w={neuron.w:.2f}, bias={neuron.bias:.2f}")





import numpy as npqq
import matplotlib.pyplot as plt

# Данные
X = np.array([
    [7, 7],   # Яблоко
    [8, 8],   # Яблоко 
    [2, 15],  # Банан
    [3, 18]   # Банан
])
y = np.array([0, 0, 1, 1])

class Neuron:
    def __init__(self, input_size):
        self.weights = np.random.randn(input_size) * 0.1
        self.bias = np.random.randn() * 0.1
        
    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))
    
    def predict(self, x):
        z = np.dot(x, self.weights) + self.bias
        return self.sigmoid(z)
    
    def train(self, X, y, epochs=1000, lr=0.1):
        history = []
        for epoch in range(epochs):
            total_loss = 0
            dw = np.zeros_like(self.weights)
            db = 0
            
            for i in range(len(X)):
                x = X[i]
                target = y[i]
                
                pred = self.predict(x)
                error = pred - target
                
                dw += error * x
                db += error
                
                total_loss += - (target * np.log(pred) + (1-target) * np.log(1-pred))
            
            self.weights -= lr * dw / len(X)
            self.bias -= lr * db / len(X)
            
            avg_loss = total_loss / len(X)
            history.append(avg_loss)
            
            if epoch % 100 == 0:
                print(f"Эпоха {epoch}, Loss: {avg_loss:.4f}")
        
        return history

neuron = Neuron(input_size=2)
loss_history = neuron.train(X, y, epochs=1000, lr=0.1)

test_data = np.array([
    [7.5, 7],
    [2.5, 16]
])

print("\nПредсказания:")
for x in test_data:
    prob = neuron.predict(x)
    print(f"{x} → {'Банан' if prob > 0.5 else 'Яблоко'} (вероятность: {prob:.2f})")

print(f"\nВеса: {neuron.weights}, Смещение: {neuron.bias}")

# Визуализация
plt.figure(figsize=(12, 5))

# 1. График loss
plt.subplot(1, 2, 1)
plt.plot(loss_history)
plt.title('График обучения')
plt.xlabel('Эпоха')
plt.ylabel('Loss')

# 2. Граница решения
plt.subplot(1, 2, 2)
plt.scatter(X[:,0], X[:,1], c=y, cmap='bwr', s=100)
plt.xlabel("Диаметр (см)")
plt.ylabel("Длина (см)")

x_vals = np.linspace(1, 9, 100)
y_vals = -(neuron.weights[0] * x_vals + neuron.bias) / neuron.weights[1]
plt.plot(x_vals, y_vals, 'g--')
plt.title('Граница решения')

plt.tight_layout()
plt.show()