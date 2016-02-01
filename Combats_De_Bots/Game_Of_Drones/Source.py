import sys
import math

#Variables Globales : BEGIN ---------------------------------------------------------------------------------------
#Liste des zones : contient des éléments de type Zone
listZones = list()
#Liste des joueurs
listPlayers = list()
#Liste des drones
listDrones = list()

#Methodes de debuggages avec affichage
def printListZones():
    for zone in listZones:
        print(zone,file=sys.stderr)

def printListPlayers():
    for player in listPlayers:
        print(player,file=sys.stderr)

def printListDrones():
    for drone in listDrones:
        print(drone,file=sys.stderr)

# p: number of players in the game (2 to 4 players)
# id: ID of your player (0, 1, 2, or 3)
# d: number of drones in each team (3 to 11)
# z: number of zones on the map (4 to 8)
p, id, d, z = [int(i) for i in input().split()]
#Variables Globales : END -----------------------------------------------------------------------------------------

#Renvoi la distance euclidienne entre deux points
def getDist(x1,y1,x2,y2):
    return math.sqrt((x2 - x1)**2 + (y2 - y1)**2)

#Zone : BEGIN -----------------------------------------------------------------------------------------------------
class Zone:
    #Classe qui repésente une zone
    #Attributs:
    # - x : Position en x de la zone
    # - y : Position en y de la zone
    # - ID : id de la zone (unique) => Démarre à 0
    # - ownerID :  ID of the team controlling the zone (0, 1, 2, or 3) or -1 if it is not controlled.
    # - listIDDroneInZone : list des id des drones dans la zone pour chaque joueur
    
    #Incrementé a chaque nouelle zone crée
    nbZoneCreated = 0
    
    #Constructeur de la classe
    def __init__(self,x,y):
        self.x = x
        self.y = y
        self.ID = Zone.nbZoneCreated
        Zone.nbZoneCreated += 1
        self.ownerID = -1
        self.listIDDroneInZone = list()
        
    #Méthode pour générer un string de notre objet
    def __str__(self):
        return "Zone: id = {}, x = {}, y = {}, ownerID = {}, nbDrones = {}".format(self.ID,self.x,self.y,self.ownerID,len(self.listIDDroneInZone))
        
    #Méthode pour attribuer le propriétaire à une zone
    def setOwner(self, ownerID):
        self.ownerID = ownerID

    #Retourne l'ID de la zone
    def getZoneID(self):
        return self.ID

    #Détermine si le zone dont l'id est passé en paramètre se situe dans la zone
    #Renvoi un booleen
    def isDroneInZone(self, IDDrone):
        return getDist(self.x, self.y, listDrones[IDDrone].getX(), listDrones[IDDrone].getY()) <= 100

    #Ajout d'un drone a la liste des drones dans la zone
    def putDroneInZone(self,IDDrone):
        self.listIDDroneInZone.append(IDDrone)

    #Renvoi le nombre de drone du joeur considéré dans la zone souhaité
    def getNbDroneInZone(self,playerID):
        IDmin = playerID*d
        IDmax = IDmin + d - 1
        self.listIDDroneInZone.sort()
        counter = 0
        for e in self.listIDDroneInZone:
            if e >= IDmin and e <= IDmax:
                counter += 1
        return counter

    #Méthode qui s'occupe d'effacer ce qui doit l'être a chaque nouveau tour
    def clearNewTurn(self):
        del self.listIDDroneInZone[:]
        self.ownerID = -1
        
#Zone : END ----------------------------------------------------------------------------------------------------------

#Player : Begin ----------------------------------------------------------------------------------------------------------
class Player:
    #Clase qui représente un joueur
    #Attributs:
    # - ID : id du joueur unique
    # - listIDZoneControlled = list des id des zones controlées par ce joueur
    # - listIDDroneControlled = list des id des drones controlées par le joueur
    # - listIDDroneByZone : list de list des id de drones dans les zones
    
    #Nombre de joueur crée
    nbPlayerCreated = 0
    
    #Constrcuteur de la classe
    def __init__(self):
        self.ID = Player.nbPlayerCreated
        Player.nbPlayerCreated += 1
        self.listIDZoneControlled = list()
        self.listIDDroneControlled = list()
        self.listIDDroneByZone = list()
        for i in range(z):
            self.listIDDroneByZone.append(list())
        
    #Ajout d'une novelle zone controlée par le joueur
    def addZoneControlled(self, IDZone):
        self.listIDZoneControlled.append(IDZone)
        
    #Ajout d'un drone au joeur
    def addDroneControlled(self, IDDrone):
        self.listIDDroneControlled.append(IDDrone)

    #AJout d'un drone dans une zone
    def addDroneInZone(self,IDDrone, IDZone):
        self.listIDDroneByZone[IDZone].append(IDDrone)

    #Renvoi le nombre de drone du joeur dans la zone voulue
    def getNbDroneInZone(self,IDZone):
        return len(self.listIDDroneByZone[IDZone])
        
    #Méthode qui s'occupe d'effacer ce qui doit l'être a chaque nouveau tour
    def clearNewTurn(self):
        del self.listIDZoneControlled[:]
        del self.listIDDroneControlled[:]
        for i in range(z):
            del self.listIDDroneByZone[i][:]
        
#Player : END ----------------------------------------------------------------------------------------------------------

#Drone : BEGIN ----------------------------------------------------------------------------------------------------------
class Drone:
    #Classe qui représente un drone
    #Attributs:
    # - ID : id du drone (unique)
    # - x : position en x du drone
    # - y : position en y du drone
    # - ownerID : id du joueur qui le controlle
    # - zoneID : id de la zone dans la quelle se trouve le drone. -1 is aucune
    
    #Nombre de drone crée
    nbDroneCreated = 0
    
    #Constructeur
    def __init__(self):
        self.ID = Drone.nbDroneCreated
        Drone.nbDroneCreated += 1
        self.x = -1
        self.y = -1
        self.ownerID = -1
        self.zoneID = -1
    
    #Mise a jour de la position du drone
    def updatePosDrone(self,x,y):
        self.x = x
        self.y = y
        self.zoneID = -1
        self.analysePos()
        self.informPlayer()
        
    def addOwner(self, ownerID):
        self.ownerID = ownerID

    #Determine si le drone se situe dans une zone
    def analysePos(self):
        for zone in listZones:
            if zone.isDroneInZone(self.ID):
                self.zoneID = zone.getZoneID()
                listZones[zone.getZoneID()].putDroneInZone(self.ID)
                break

    #Modifie le joeur en lui précisant si un drone est dans une zone
    def informPlayer(self):
        if self.zoneID != -1:
            listPlayers[self.ID // d].addDroneInZone(self.ID,self.zoneID)

    #Renvoi la position en X du drone
    def getX(self):
        return self.x

    #Renvoi la position en Y du drone
    def getY(self):
        return self.y
        
    #Méthode qui s'occupe d'effacer ce qui doit l'être a chaque nouveau tour
    def clearNewTurn(self):
        self.x = -1
        self.y = -1
#Drone : END ----------------------------------------------------------------------------------------------------------

#Récupération des coordonnées des zones
for i in range(z):
    xzone, yzone = [int(j) for j in input().split()]
    listZones.append(Zone(xzone,yzone))

#Création des différents joueurs
for i in range(p):
    listPlayers.append(Player())

#Création des différents drones
for i in range(d*p):
    listDrones.append(Drone())
    
#Fonction qui s'occupe d'effacer ce qui doit l'être a chaque nouveau tour
def updateListNewTurn():
    #Reinitialisation des lists
    for zone in listZones:
        zone.clearNewTurn()
    for player in listPlayers:
        player.clearNewTurn()
    for drone in listDrones:
        drone.clearNewTurn()
    #Mise a jour du proprietaire de chaque zone
    for i in range(z):
        ownerID = int(input())
        listZones[i].setOwner(ownerID)  # ID of the team controlling the zone (0, 1, 2, or 3) or -1 if it is not controlled. The zones are given in the same order as in the initialization.
        listPlayers[ownerID].addZoneControlled(i)
    #Récupération de la position de tous les drones
    for i in range(p):
        for j in range(d):
            # dx: The first D lines contain the coordinates of drones of a player with the ID 0, the following D lines those of the drones of player 1, and thus it continues until the last player.
            dx, dy = [int(k) for k in input().split()]
            idDroneCour = i*d + j
            #Mise a jour de la position du drone
            listDrones[idDroneCour].updatePosDrone(dx,dy)
            #Chaque drone est controlée par un joueur        
            listPlayers[i].addDroneControlled(idDroneCour)
            listDrones[idDroneCour].addOwner(i)
            
# game loop
while True:
    #Mise a jour des valeurs des classes
    updateListNewTurn()
   
    #Sortie : nouvelle position désirée des drones   
    for i in range(d):
        print(xzone,yzone)
    

 # To debug: print("Debug messages...", file=sys.stderr)