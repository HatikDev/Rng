import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import math
import os

kMaxLen = 102

def makeImage(inputPath, outputPath, legend):
    df = pd.read_csv(inputPath, skipinitialspace=True)
    plt.rcParams["figure.figsize"] = (20, 10)

    X = [i for i in range(3, kMaxLen)]
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
    plt.plot(X, df.iloc[3:kMaxLen, 1], color='b', label='000')
    plt.plot(X, df.iloc[3:kMaxLen, 3], color='r', label='001')
    plt.plot(X, df.iloc[3:kMaxLen, 5], color='g', label='010')
    plt.plot(X, df.iloc[3:kMaxLen, 7], color='c', label='011')
    plt.plot(X, df.iloc[3:kMaxLen, 9], color='m', label='100')
    plt.plot(X, df.iloc[3:kMaxLen, 11], color='y', label='101')
    plt.plot(X, df.iloc[3:kMaxLen, 13], color='k', label='110')
    plt.plot(X, df.iloc[3:kMaxLen, 15], color='#abc', label='111')

    # plt.xticks(X, x_tricks)
    plt.legend()
    plt.savefig(outputPath, dpi=100)
    plt.close()

tree = os.walk("calculation")

files = list()
for i in tree: # TODO fix bug with folders
    files = i[2]
    break

for file in files:
    legend = str(*file.split('.')[:-1])
    makeImage("calculation/" + file, "calculation/result" + file[:-3] + "png", legend)