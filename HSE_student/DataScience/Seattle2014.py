import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn; seaborn.set()

rainfall = pd.read_csv("Seattle2014.csv")['PRCP'].values
inches = rainfall / 254 # 1/10mm -> inches
inches.shape
print(inches)

plt.hist(inches, 40)

plt.show()