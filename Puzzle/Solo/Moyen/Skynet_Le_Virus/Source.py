import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

# n: the total number of nodes in the level, including the gateways
# l: the number of links
# e: the number of exit gateways
n, l, e = [int(i) for i in input().split()]
graph = list()
for i in range(n):
    graph.append(list())
for i in range(l):
    # n1: N1 and N2 defines a link between these nodes
    n1, n2 = [int(j) for j in input().split()]
    graph[n1].append(n2)
    graph[n2].append(n1)
    
lOut = list()
for i in range(e):
    ei = int(input())  # the index of a gateway node
    lOut.append(ei)

# game loop
while True:
    si = int(input())  # The index of the node on which the Skynet agent is positioned this turn

    for gateWay in lOut:
        if si in graph[gateWay]:
            print("{} {}".format(si,gateWay))
            break
    else:
        print("wait")
    # Write an action using print
    # To debug: print("Debug messages...", file=sys.stderr)
    
    # Example: 0 1 are the indices of the nodes you wish to sever the link between
    
