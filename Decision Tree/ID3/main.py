import time
import os
import numpy as np
from sklearn.tree import export_graphviz

import sys
base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.append(base_dir)
#from ID3 import *
#from ID3.ID3_implement import ID3

def load_data(path):
    data = []
    with open(path) as f:
        for line in f.readlines():
            if '[' in line or ']' in line:
                continue
            else:
                data_str = line.split('\t')
                data.append([float(x) for x in data_str])
    data = np.array(data)
    return data




if __name__ == '__main__':
    data = load_data('../data/traindata.txt')
    X, y = data[:, :-1], data[:, -1].astype(np.int16)  # Assuming the last column is the target variable
    id3 = ID3()
    id3.fit(X, y)
    dot = id3.draw_tree()
    dot.view()

    test_data = load_data('../data/testdata.txt')
    X_test, y_test = test_data[:, :-1], test_data[:, -1].astype(np.int16)
    y_pred = id3.predict(X_test)
    accuracy = np.sum(y_pred == y_test) / len(y_test)
    print(f'Accuracy: {accuracy * 100:.2f}%')





