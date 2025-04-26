import numpy as np

def linear(x1, x2, w1, w2, bias):
    result = x1 * w1 + x2 * w2 + bias
    return 1 if result >= 0 else 0

def training(X, y, epochs = 100, learning_rate = 0.02):
    w1, w2, bias = 0.0, 0.0, 0.0
    flag = 0
    for epoch in range(epochs):
        total_errors = 0
        for x1, x2, aim in zip(X[:, 0], X[:, 1], y):
            
            answer = linear(x1, x2, w1, w2, bias)
            
            error = aim - answer
            total_errors += abs(error)
            
            w1 += learning_rate * error * x1
            w2 += learning_rate * error * x2
            bias += learning_rate * error
            
            if total_errors == 0:
                print(f"Обучение завершено на эпохе {epoch + 1}!")
                flag = 1
                break
        if flag == 1:
            break
    return w1, w2, bias


X = np.array([
    [0, 0],  # Холодно, нет ветра → 0
    [0, 1],  # Холодно, есть ветер → 1
    [1, 0],  # Тепло, нет ветра → 0
    [1, 1]   # Тепло, есть ветер → 1 (ветер делает погоду холоднее)
])
y = np.array([0, 1, 0, 1])  


w1, w2, bias = training(X, y)
print(f"Обученные веса: w1={w1:.2f}, w2={w2:.2f}, bias={bias:.2f}")