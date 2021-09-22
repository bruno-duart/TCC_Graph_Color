#import glob
import numpy as np

path = "/home/brunoduarte/Downloads/graph_color/DSJC1000.9.col"#.col"

#files = glob.glob(pathname=(path+'.col'))

"""for file in files:
    print(file)"""

with open(path, 'r') as f:
    for line in f:
        l = line.split()
        if(len(l) > 0):
            if (l[0] == 'c'):
                continue
            if l[0] == 'p':
                matrix = np.zeros((int(l[2]), int(l[2])))
            elif l[0] == 'e':
                matrix[int(l[1])-1][int(l[2])-1] = 1
                matrix[int(l[2])-1][int(l[1])-1] = 1
print(len(matrix))
for line in matrix:
    for num in line:
        print(int(num), end=' ')
    print()
#print(matrix)