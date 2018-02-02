import numpy as np
m = int(input())
grid = []
for i in range(0, m):
	grid.append(input())
try:
	k = grid[2].index('p')
except:
	k = -1
print(k)
