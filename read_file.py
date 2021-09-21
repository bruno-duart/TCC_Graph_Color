import glob
import numpy as np

path = "/home/brunoduarte/Downloads/graph_color/*-FullIns_*.col"

files = glob.glob(pathname=path)

"""for file in files:
    print(file)"""

with open(files[3], 'r') as f:
    for line in f:
        l = line.split()
        if(len(l) > 0):
            print(l)
            if (l[0] == 'c'):
                continue
            if l[0] == 'p':
                matrix = np.zeros((int(l[2]), int(l[2])))
            elif l[0] == 'e':
                matrix[int(l[1])-1][int(l[2])-1] = 1
                matrix[int(l[2])-1][int(l[1])-1] = 1
print(matrix[29])