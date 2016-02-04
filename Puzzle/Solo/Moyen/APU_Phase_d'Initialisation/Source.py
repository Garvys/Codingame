import sys
import math

# Don't let the machines win. You are humanity's last hope...
def findNeighbour(grid, w, h, x, y, dx, dy):
    cx = x + dx
    cy = y + dy
    while cx < w and cy < h:
        if grid[cy][cx] == '0':
            return [cx, cy]
        cx += dx
        cy += dy
    return [-1,-1]

width = int(input())  # the number of cells on the X axis
height = int(input())  # the number of cells on the Y axis
graph = list()
nodes = list()
for i in range(height):
    line = input()  # width characters, each either 0 or .
    graph.append(str(line.strip()))
    for j,x in enumerate(line):
        if x == '0':
            nodes.append([j,i])

for node in nodes:
    x = node[0]
    y = node[1]
    print(" ".join(map(str,node + findNeighbour(graph,width,height,x,y,1,0) + findNeighbour(graph,width,height,x,y,0,1))))
            

# Write an action using print
# To debug: print("Debug messages...", file=sys.stderr)

# Three coordinates: a node, its right neighbor, its bottom neighbor
    

