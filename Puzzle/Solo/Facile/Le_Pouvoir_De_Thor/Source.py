import sys, math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

# LX: the X position of the light of power
# LY: the Y position of the light of power
# TX: Thor's starting X position
# TY: Thor's starting Y position
LX, LY, TX, TY = [int(i) for i in input().split()]

# game loop
while 1:
    E = int(input()) # The level of Thor's remaining energy, representing the number of moves he can still make.
    direction = ""
    if LY < TY:
        direction += "N"
        TY -= 1
    if LY > TY:
        direction += "S"
        TY += 1
    if LX < TX:
        direction += "W"
        TX -= 1
    if LX > TX:
        direction += "E"
        TX += 1
    print(direction)

