import os

with open("tools/seeds.txt", mode="w") as f:
    for i in range(300):
        print(i, file=f)
