import sys
import math
from collections import deque
# l - longueur d'un nombre maya
# h - hauteur d'un nombre maya
l, h = [int(i) for i in input().split()]

#Dictionnaire maya des nombres
numbers = []
for i in range(h):
    numbers.append(str(input()))

#Renvoi le nombre entier associé au nombre Maya
def numberToMaya(N):
    out = []
    N = int(N)
    for i in range(h):
        out.append(numbers[i][N*l:N*l+l])
    return out

#Renvoi le nombre Maya associé au nombre entier
def mayaToNumber(maya):
    for n in range(20):
        if numberToMaya(n) == maya:
            return n
    print("Nombre maya non reconnus",file=sys.stderr)

#Récupération d'un nombre Maya en base 20 sur stdin et le transforme en nombre entier
def getNumber():
    #Liste des nombres entiers sans prise en compte de la base 20
    num = []
    s1 = int(input())
    for i in range(s1//h):
        inMaya = []
        for o in range(h):
            inMaya.append(str(input()))
        num.append(mayaToNumber(inMaya))
    #Prise en compte de la base 20
    res = 0
    while len(num) > 0:
        res += num[0]*20**(len(num)-1)
        num.remove(num[0])
    return res

    
#Récupération des deux nombres
num1 = getNumber()
num2 = getNumber()

#Evaluation du résultat entier
result = eval("{}{}{}".format(num1,str(input()),num2))

#Découpage du résultat selon la base 20
d = deque()
while result > 0:
    d.appendleft(result % 20)
    result = result // 20

#Cas particulier : si res = 0
if len(d) == 0:
    d.append(0)

#Affichage du nombre Maya résultat
for e in d:  
    maya = numberToMaya(e)
    for i in range(h):
        print(maya[i])
