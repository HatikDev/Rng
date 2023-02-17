import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import math
import os

def makeImage(inputPath, outputPath, legend):
    df = pd.read_csv(inputPath, skipinitialspace=True)

    X = [i for i in range(3, 102)]
    # st = [2, 4, 8, 16, 32, 64]
    # l = [[str(i + 1)] * st[i] for i in range(len(st))]
    # x_tricks = list()
    # for el in l:
    #     for e in el:
    #         x_tricks.append(e)
    # x_tricks = x_tricks[:99]

    # title = inputPath.split("/")[-1]
    # title = title.split(".")[0]
    # title = title[6:] # remove "output"
    plt.title(legend)
    plt.plot(X, df.iloc[3:102, 1], color='b', label='000')
    plt.plot(X, df.iloc[3:102, 3], color='r', label='001')
    plt.plot(X, df.iloc[3:102, 5], color='g', label='010')
    plt.plot(X, df.iloc[3:102, 7], color='c', label='011')
    plt.plot(X, df.iloc[3:102, 9], color='m', label='100')
    plt.plot(X, df.iloc[3:102, 11], color='y', label='101')
    plt.plot(X, df.iloc[3:102, 13], color='k', label='110')
    plt.plot(X, df.iloc[3:102, 15], color='#abc', label='111')

    # plt.xticks(X, x_tricks)
    plt.legend()
    plt.savefig(outputPath)
    plt.close()

tree = os.walk("calculation")

files = list()
for i in tree:
    files = i[2]

for file in files:
    makeImage("calculation/" + file, "calculation/result" + file[:-3] + "png", file[6:-4])