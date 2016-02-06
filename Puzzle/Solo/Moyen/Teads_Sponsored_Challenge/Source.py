import sys
import math

nodes = set()
removedNodes = set()
edges = list()

n = int(input())  # the number of adjacency relations
for i in range(n):
    # xi: the ID of a person which is adjacent to yi
    # yi: the ID of a person which is adjacent to xi
    xi, yi = [int(j) for j in input().split()]
    nodes.add(xi)
    nodes.add(yi)
    edges.append([xi,yi])

#Liste des suivants
graph = dict()

for node in nodes:
	graph[node] = set()

for edge in edges:
	graph[edge[0]].add(edge[1])
	graph[edge[1]].add(edge[0])

profondeur = 0

#Intialisation : on enleve les noeuds des extrémités
nodesToRemove = set()
nodesNextToRemove = set()
for node in nodes:
	if len(graph[node]) == 1:
		nodesToRemove.add(node)
		for n in graph[node]:
			if len(graph[n] - nodesToRemove) == 1:
				nodesNextToRemove.add(n) 
lastNode = set()
while(len(nodes - removedNodes) > 1):
	print("Supprimé : ", removedNodes,file=sys.stderr)
	print("A supprimer : ", nodesToRemove,file=sys.stderr)
	lastNode = set(nodes - removedNodes)
	removedNodes.update(nodesToRemove)
	nodesToRemove = set(nodesNextToRemove)
	nodesNextToRemove.clear()
	for node in nodesToRemove:
		#nodesNextToRemove.update(graph[node] - removedNodes)
		for n in (graph[node] - removedNodes):
			if len(graph[n] - nodesToRemove - removedNodes) == 1:
				nodesNextToRemove.add(n)
	profondeur +=1

print(profondeur)


