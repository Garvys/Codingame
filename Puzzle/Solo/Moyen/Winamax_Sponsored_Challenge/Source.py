import sys
import math
from collections import deque

#Récupération de la valeur d'une carte a partir de sin nom
def getValue(card):
    #On enleve la couleur
    card = card[:len(card)-1]
    if card.isdigit():
        cardNOColor = int(card)
    else:
        #Ce n'est pas un chiffre
        card = str(card)
        if card == 'J':
            cardNOColor = 11
        elif card == 'Q':
            cardNOColor = 12
        elif card == 'K':
            cardNOColor = 13
        elif card == 'A':
            cardNOColor = 14
        else:
            print("Carte non reconnue",file=sys.stderr)
    return cardNOColor
        
#Récupération de la valeurs des cartes pour un joueur
def getCards():
    n = int(input())  # the number of cards for player
    pCards = deque()
    for i in range(n):
        cardp_1 = str(input())  # the n cards of player
        pCards.append(getValue(cardp_1))
    return pCards
    
#Récupération des jeux
p1Cards = getCards()
p2Cards = getCards()
manche = 0

#Boucle de jeu
while 1:
    manche += 1
    if len(p1Cards) == 0:
        print("2 {}".format(manche-1))
        break
    if len(p2Cards) == 0:
        print("1 {}".format(manche-1))
        break
    if p1Cards[0] > p2Cards[0]:
        p1Cards.append(p1Cards.popleft())
        p1Cards.append(p2Cards.popleft())
        if len(p2Cards) == 0:
            print("1 {}".format(manche))
            break
    elif p1Cards[0] < p2Cards[0]:
        p2Cards.append(p1Cards.popleft())
        p2Cards.append(p2Cards.popleft()) 
        if len(p1Cards) == 0:
            print("2 {}".format(manche))
            break
    else: #Battaille!
        buff1 = deque([p1Cards.popleft()])
        buff2 = deque([p2Cards.popleft()])
        bataille = True
        while bataille:
            if len(p1Cards) < 4 or len(p2Cards) < 4:
                print("PAT")
                quit()
            for i in range(3):
                buff1.append(p1Cards.popleft())
                buff2.append(p2Cards.popleft())
            if p1Cards[0] > p2Cards[0]:
                bataille = False
                buff1.append(p1Cards.popleft())
                buff2.append(p2Cards.popleft()) 
                p1Cards.extend(buff1)
                p1Cards.extend(buff2)
            elif p1Cards[0] < p2Cards[0]:
                bataille = False
                buff1.append(p1Cards.popleft())
                buff2.append(p2Cards.popleft())
                p2Cards.extend(buff1)
                p2Cards.extend(buff2)
            else:
                buff1.append(p1Cards.popleft())
                buff2.append(p2Cards.popleft())

