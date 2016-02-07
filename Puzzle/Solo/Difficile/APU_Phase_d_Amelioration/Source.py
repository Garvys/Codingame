import sys
import math
import copy

width = int(input())
height = int(input())

class Grid:

	def __init__(self,dictP2N,dictN2P):
		self.dictP2N = copy.deepcopy(dictP2N)
		self.dictN2P = copy.deepcopy(dictN2P)

dictNumToPointInit = dict()
dictPointToNumInit = dict()
cells = list()

def hashPoint(p):
	return int(p[0]*(height+2) + p[1])
	
for i in range(9):
	dictNumToPointInit[i] = list()

for i in range(height):
	line = str(input())
	for j,c in enumerate(line):
		if c.isdigit():
			dictNumToPointInit[int(c)].append([i,j])
			dictPointToNumInit[hashPoint([i,j])] = int(c)
			cells.append([i,j])
	
def isOnGrid(p):
	i = p[0]
	j = p[1]
	return i >= 0 and i <= height and j >= 0 and j <= width

def isCell(p):
	return p in cells

def getVoisinInDir(i,j,di,dj,l):
	while 1:
		if isOnGrid([i+di,j+dj]) and isCell([i+di,j+dj]):
			l.append([i+di,j+dj])
			break
		if not isOnGrid([i+di,j+dj]):
			break
		if di > 0: di += 1
		if di < 0: di -= 1
		if dj > 0: dj += 1
		if dj < 0: dj -= 1

def getVoisin(p):
	i = p[0]
	j = p[1]
	l = list()
	getVoisinInDir(i,j,1,0,l)
	getVoisinInDir(i,j,-1,0,l)
	getVoisinInDir(i,j,0,1,l)
	getVoisinInDir(i,j,0,-1,l)
	return l

def decreaseNumberNode(p,g):
	c = g.dictP2N[hashPoint(p)]
	print(g.dictN2P,file=sys.stderr)
	print(p,file=sys.stderr)
	print(c,file=sys.stderr)
	g.dictN2P[c].remove(p)
	g.dictN2P[c-1].append(p)
	g.dictP2N[hashPoint(p)] -= 1

def addLink(p1,p2,g):
	decreaseNumberNode(p1,g)
	decreaseNumberNode(p2,g)
	print("{} {} {} {} 1".format(p1[1],p1[0],p2[1],p2[0]))

def getCellPos(g):
	return [p for p in cells if g.dictP2N[hashPoint(p)] > 0]


#Cas trivial si c(p) = sum(c[voisin])
def solveTrivialLink(g):
	for cell in getCellPos(g):
		listVoisin = getVoisin(cell)
		if g.dictP2N[hashPoint(cell)] == sum([min(g.dictP2N[hashPoint(p)],2) for p in listVoisin]):
			for voisin in listVoisin:
				for oo in range(min(2,g.dictP2N[hashPoint(voisin)])):
					addLink(cell,voisin,g)

def solve1Link(g):
	for cell in g.dictN2P[1]:
		listVoisinPositiv = [ p for p in getVoisin(cell) if g.dictP2N[hashPoint(p)] > 0]
		if len(listVoisinPositiv) == 1:
			addLink(cell,listVoisinPositiv[0],g)

grid = Grid(dictPointToNumInit,dictNumToPointInit)

for ll in range(10):
	solveTrivialLink(grid)
	solve1Link(grid)

for cell in getCellPos(grid):
	listVoisinPositiv = [p for p in getVoisin(cell) if grid.dictP2N[hashPoint(p)] > 0]
	if grid.dictP2N[hashPoint(cell)] == 1 and len(listVoisinPositiv) == 2:
		addLink(cell,listVoisinPositiv[0],grid)

for ll in range(10):
	solveTrivialLink(grid)
	solve1Link(grid)