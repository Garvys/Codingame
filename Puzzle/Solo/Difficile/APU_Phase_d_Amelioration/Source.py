import sys
import math

width = int(input())
height = int(input())
dictNumToPoint = dict()
dictPointToNum = dict()
cells = list()

def hashPoint(p):
	return int(p[0]*(height+2) + p[1])
	
for i in range(9):
	dictNumToPoint[i] = list()

for i in range(height):
	line = str(input())
	for j,c in enumerate(line):
		if c.isdigit():
			dictNumToPoint[int(c)].append([i,j])
			dictPointToNum[hashPoint([i,j])] = int(c)
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

def decreaseNumberNode(p):
	c = dictPointToNum[hashPoint(p)]
	print(dictNumToPoint,file=sys.stderr)
	print(p,file=sys.stderr)
	print(c,file=sys.stderr)
	dictNumToPoint[c].remove(p)
	dictNumToPoint[c-1].append(p)
	dictPointToNum[hashPoint(p)] -= 1

def addLink(p1,p2):
	decreaseNumberNode(p1)
	decreaseNumberNode(p2)
	print("{} {} {} {} 1".format(p1[1],p1[0],p2[1],p2[0]))




#Cas trivial si c(p) = sum(c[voisin])
def lol():
	for cell in [p for p in cells if dictPointToNum[hashPoint(p)] > 0]:
		listVoisin = getVoisin(cell)
		if dictPointToNum[hashPoint(cell)] == sum([min(dictPointToNum[hashPoint(p)],2) for p in listVoisin]):
			for voisin in listVoisin:
				for oo in range(min(2,dictPointToNum[hashPoint(voisin)])):
					addLink(cell,voisin)

def lol2():
	for cell in dictNumToPoint[1]:
		listVoisinPositiv = [ p for p in getVoisin(cell) if dictPointToNum[hashPoint(p)] > 0]
		if len(listVoisinPositiv) == 1:
			addLink(cell,listVoisinPositiv[0])

print(getVoisin([1,3]),file=sys.stderr)
for ll in range(10):
	lol()
	lol2()

for i in range(height):
	for j in range(width):
		print(i,j,":",hashPoint([i,j]),file=sys.stderr)