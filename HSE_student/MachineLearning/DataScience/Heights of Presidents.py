import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn; seaborn.set_theme()

data = pd.read_csv('president_heights.csv')
heights = np.array(data['height(cm)'])
print(heights)
print("Mean height:        ", np.mean(heights))
print("Standart Deviation: ", np.std(heights))
print("Minimum height:     ", heights.min())
print("Maximum height:     ", heights.max())
print("25th Percentile:    ", np.percentile(heights, 25))
plt.hist(heights)
plt.title("Height Distribution of US Presidents")
plt.xlabel('height (cm)')
plt.ylabel('number')
plt.show()