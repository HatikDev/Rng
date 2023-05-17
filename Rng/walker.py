import os

path = "."

folders_set = set()
for dir, _, files in os.walk(path):
    if len(dir) == 0 or dir == ".":
        continue
    number = int(''.join([i for i in dir if len(i) > 0 and i.isdigit()]))
    if number < 21:
        folders_set.add(number)

for folder in folders_set:
    for _, _, file in os.walk(str(folder) + "/"):
        for name in file:
            if name.split('.')[-1] == 'csv':
                newname = str(*name.split('.')[:-1]) + str(folder) + ".csv"
                os.rename(str(folder) + "/" + name, str(folder) + "/" + newname)