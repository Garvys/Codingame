import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

n = int(input())
listPuissance = list()
for i in range(n):
    listPuissance.append(int(input()))
       
listPuissance.sort()

listDiffPuissance = list()

for i in range(n-1):
    listDiffPuissance.append(listPuissance[i+1] - listPuissance[i])

print(min(listDiffPuissance))
