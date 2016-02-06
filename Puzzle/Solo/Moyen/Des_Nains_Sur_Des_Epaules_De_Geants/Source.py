import sys
import math

#Liste des noeuds (unique => set)
nodes = set()
#Liste des influences
edges = list()

n = int(input())  # the number of relationships of influence
for i in range(n):
    # x: a relationship of influence between two people (x influences y)
    x, y = [int(j) for j in input().split()]
    nodes.add(x)
    nodes.add(y)
    edges.append([x,y])

#Liste des suivants pour un noeud
graph = dict()
for node in nodes:
	graph[node] = list()

for edge in edges:
	graph[edge[0]].append(edge[1])

#Fonction réccurente pour trouver la taille max
def getSizeInfluence(node):
	oo = 0
	for n in graph[node]:
		oo = max(1+getSizeInfluence(n),oo)
	return oo

maxInfluence = 0
for node in nodes:
	maxInfluence = max(1+getSizeInfluence(node),maxInfluence)

# The number of people involved in the longest succession of influences
print(maxInfluence)
