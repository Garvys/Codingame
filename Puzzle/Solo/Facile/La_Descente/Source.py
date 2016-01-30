import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.


# game loop
while True:
    space_x, space_y = [int(i) for i in input().split()]
    listh = list()
    for i in range(8):
        listh.append(int(input()))  # represents the height of one mountain, from 9 to 0. Mountain heights are provided from left to right.

    print("FIRE" if max(listh) == listh[space_x] else "HOLD")
