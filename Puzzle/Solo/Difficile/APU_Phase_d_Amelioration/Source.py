import sys
import math
import copy

width = int(input())
height = int(input())

dictNumToPointInit = dict()
dictPointToNumInit = dict()
dictLinksInit = dict()
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

for cell in cells:
	dictLinksInit[hashPoint(cell)] = list()
	
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

class Grid:
	# dictP2N : dictionnaire qui a un point associe le nombre de lien nécessaire
	# dictN2P : dictionnaire qui a un nombre de lien nécessaire associe une liste de point
	# listStrings : liste de strings qui seront a afficher à la fin du programme
	# dictLinks : dict qui contient les liens d'un poit a l'autre

	def __init__(self,dictP2N,dictN2P,dictLinks):
		self.dictP2N = copy.deepcopy(dictP2N)
		self.dictN2P = copy.deepcopy(dictN2P)
		self.dictLinks = copy.deepcopy(dictLinks)
		self.listStrings = list()

	# Solve la grille
	def solve(self):
		while self.solveTrivialLink() > 0:
		    a = 0
		if self.isSolved():
			return 
		self.solveBySplit()

	def solveBySplit(self):
		for cell in self.dictN2P[1]:
			listVoisinPositiv = [p for p in getVoisin(cell) if self.dictP2N[hashPoint(p)] > 0]
			for i in range(len(listVoisinPositiv)):
				if self.isLinkAddable(cell,listVoisinPositiv[i]):
					grid = Grid(self.dictP2N,self.dictN2P,self.dictLinks)
					grid.addLink(cell,listVoisinPositiv[i])
					grid.solve()
					if grid.isSolved():
						self.dictP2N = copy.deepcopy(grid.dictP2N)
						self.dictN2P = copy.deepcopy(grid.dictN2P)
						self.listStrings.extend(grid.listStrings)
						return

	#Affiche sur la sortie standard les liens a ajouter pour solver la grille
	def printLinksToAdd(self):
		for s in self.listStrings:
			print(s)

	def isSolved(self):
		return len(cells) == len(self.dictN2P[0])

	def decreaseNumberNode(self,p):
		c = self.dictP2N[hashPoint(p)]
		#print(self.dictN2P,file=sys.stderr)
		#print(p,file=sys.stderr)
		#print(c,file=sys.stderr)
		self.dictN2P[c].remove(p)
		self.dictN2P[c-1].append(p)
		self.dictP2N[hashPoint(p)] -= 1

	def addLink(self,p1,p2):
		self.decreaseNumberNode(p1)
		self.decreaseNumberNode(p2)
		self.dictLinks[hashPoint(p1)].append(p2)
		self.dictLinks[hashPoint(p2)].append(p1)
		self.listStrings.append("{} {} {} {} 1".format(p1[1],p1[0],p2[1],p2[0]))

	def isLinkAddable(self,p1,p2):
		print("Test add link between",p1,"and",p2,file=sys.stderr)
		if p1[0] == p2[0]: #Meme ligne
			colMin = min(p1[1],p2[1])+1
			colMax = max(p1[1],p2[1])
			i = p1[0]
			for j in range(colMin,colMax):
				up = list()
				down = list()
				getVoisinInDir(i,j,-1,0,up)
				getVoisinInDir(i,j,1,0,down)
				if len(up) != 0 and len(down) != 0 and down[0] in self.dictLinks[hashPoint(up[0])]:
					return False
		else: #Meme colonne
			lineMin = min(p1[0],p2[0])+1
			lineMax = max(p1[0],p2[0])
			j = p1[1]
			for i in range(lineMin,lineMax):
				left = list()
				right = list()
				getVoisinInDir(i,j,0,-1,left)
				getVoisinInDir(i,j,0,1,right)
				if len(left) != 0 and len(right) != 0 and left[0] in self.dictLinks[hashPoint(right[0])]:
					return False
		return True

	def getCellPos(self):
		return [p for p in cells if self.dictP2N[hashPoint(p)] > 0]


	#Cas trivial si c(p) = sum(c[voisin])
	#Renvoi le nombre de lien ajouté
	def solveTrivialLink(self):
		numAdded = 0
		for cell in self.getCellPos():
			listVoisin = getVoisin(cell)
			if self.dictP2N[hashPoint(cell)] == sum([min(self.dictP2N[hashPoint(p)],2) for p in listVoisin]):
				for voisin in listVoisin:
					if self.isLinkAddable(cell,voisin):
						for oo in range(min(2,self.dictP2N[hashPoint(voisin)])):
							self.addLink(cell,voisin)
							numAdded += 1
		for cell in self.dictN2P[1]:
			listVoisinPositiv = [ p for p in getVoisin(cell) if self.dictP2N[hashPoint(p)] > 0]
			if len(listVoisinPositiv) == 1 and self.isLinkAddable(cell,listVoisinPositiv[0]):
				self.addLink(cell,listVoisinPositiv[0])
				numAdded += 1
		return numAdded


grid = Grid(dictPointToNumInit,dictNumToPointInit,dictLinksInit)

grid.solve()
grid.printLinksToAdd()