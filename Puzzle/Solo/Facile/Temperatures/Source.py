import sys
from math import fabs

n = int(input())
if n == 0:
    print("0")
    quit()
temp = input().split()
min = sys.maxsize
for elt in temp:
    elt = int(elt)
    if((fabs(elt) < fabs(min)) or (fabs(elt) == fabs(min) and elt > 0)):
        min = elt
print(min)


