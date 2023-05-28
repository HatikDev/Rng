import pandas as pd
import matplotlib.pyplot as plt
import os
import sys

def make_image(inputPath, outputPath, legend, count):
    df = pd.read_csv(inputPath, skipinitialspace=True)

    X = [i for i in range(3, count)]
    plt.title(legend)

    colors = ['b', 'r', 'g', 'c',' m', 'y', 'k', '#abc']
    labels = ['000', '001', '010', '011', '100', '101', '110', '111']
    for i in range(8):
        column_number = 2 * i + 1
        plt.plot(X, df.iloc[3:count, column_number], color=colors[i], label=labels[i])

    plt.legend()
    plt.savefig(outputPath)
    plt.close()

def main():
    input_folder = sys.argv[1]
    output_folder = sys.argv[2]
    count = sys.argv[3]

    tree = os.walk(".")
    files = tree[2]
    for file in files:
        make_image(input_folder + file, output_folder + file[:-3] + "png", file[6:-4], count)

if __name__ == "__main__":
    main()
