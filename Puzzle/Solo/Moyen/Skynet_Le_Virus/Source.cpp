#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <deque>
#include <climits>
#include <queue>

using namespace std;

#define Node_Elt Node<Type_Element>
#define Edge_Elt Edge<Type_Element>
#define Graphe_Elt Graphe<Type_Element>
#define Dij_Node_Elt Dij_Node<Type_Element>

#define INDEX_FIN -1

template<class Type_Element>
class Edge;
template<class Type_Element>
class Node;
template<class Type_Element>
class Graphe;

//------------------------------Classe---------------------------------

template<class Type_Element>
class Graphe
{
	template <class> friend class Dijkstra;
private:
	//Un boolen pour savoir si de base, le graphe est orienté opu non
	bool m_oriented;
	//Un graphe est un tableau de pointeur sur des noeuds
	std::vector<Node_Elt*> m_Node;
	//On ajoute un noeud à la liste des noeuds //Recquiert, élément pas déja dans le graphe
	Node_Elt* addNode(Type_Element Elt);
	//Fonction de recherche d'un élément dans le graphe. renvoi le pointeur si le noeud si l'élément est déja présent. NULL sinon.
	Node_Elt* findNode(Type_Element Elt);
	//Démarque tout les noeuds
	void unmark_all_nodes();
	//Démarque tout les edges
	void unmark_all_edges();
	//Marque les edges dans les deux sens
	void mark_edge(Node_Elt* Node1, Node_Elt* Node2);
	//---Debut Méthodes Dijkstra
		//Initialise les variables de Dijkstra
		void dij_init();
		//Renvoi le noeud de plus petit élement  non marqué, NULL sinon
		Node_Elt* dij_min();
	//---Fin Méthodes Dijkstra
	//---Debut Parcour du graphe en Profondeur (DFS)
		void dfs_recurs(Node_Elt* node_cour, void(*pointeur_fct)(Node_Elt*));
	//---Fin Parcour du graphe en Profondeur (DFS)
public:
	//Création du graphe vide. De base non orienté
	Graphe(bool oriented = false);
	//Graphe();
	~Graphe();
	//Fonction de recherche d'un élément. Renvoi true si l'élément est déja dans le graphe, false sinon
	bool find(Type_Element Elt);
	//On ajoute le segment au graphe. Le dernier paramètre est un booléen pour savoir si on met un segment dans les deux sens (de base non orienté)
	void add(Type_Element Elt1, Type_Element Elt2, int cost, bool oriented);
	//Si booléen non fournis, on utilise abec le boolen fournis à la création du graphe
	void add(Type_Element Elt1, Type_Element Elt2, int cost);
	//Si booléen non fournis, et cout non fournis, on utilise abec le boolen fournis à la création du graphe et un cout de 1
	void add(Type_Element Elt1, Type_Element Elt2);
	//Suppression du noeud
	void removeNode(Node_Elt* Node_to_suppr);
	void removeNode(Type_Element Elt_to_suppr);
	//Supprime une arrête
	void remove_Edge(Type_Element Elt1, Type_Element Elt2);
	//On crée un export dot qui permet d'afficher le contenu du graphe
	void exportDot();
	//---Debut Méthodes Dijkstra
		//Applique l'algorithme de Dijkstra
		void dij_compute(Type_Element Elt_debut);
		//Renvoi le cout du plus court chemin
		int dij_get_cost(Type_Element Elt_Fin);
		//Renvoi la chemin dans une deque
		deque<Type_Element> dij_get_path(Type_Element Elt_Fin);
	//---Fin Méthodes Dijkstra
	//---Debut Parcour du graphe en Largeur (BFS)
		//Applique l'algorithme en partant du noeud qui contient l'élément Elt_Debut
		void bfs_compute(Type_Element Elt_Debut, void(*pointeur_fct)(Node_Elt*));
		//Applique l'algorithme en partant d'un noeud quelconque
		void bfs_compute(void(*pointeur_fct)(Node_Elt*));
	//---Fin Parcour du graphe en Largeur (BFS)
	//---Debut Parcour du graphe en Profondeur (DFS)
		//Applique l'algorithme en partant du noeud qui contient l'élément Elt_Debut
		void dfs_compute(Type_Element Elt_Debut, void(*pointeur_fct)(Node_Elt*));
		//Applique l'algorithme en partant d'un noeud quelconque
		void dfs_compute(void(*pointeur_fct)(Node_Elt*));
	//---Fin Parcour du graphe en Profondeur (DFS)
};

//---------------------------Méthodes--------------------------------

template<class Type_Element>
Node_Elt* Graphe_Elt::addNode(Type_Element Elt)
{
	//Elt n'est pas déja dans le graphe
	Node_Elt* Noeud = new Node_Elt(Elt);
	m_Node.push_back(Noeud);
	//Renvoi le pointeur sur le noeud cré
	return Noeud;
}

template<class Type_Element>
Node_Elt* Graphe_Elt::findNode(Type_Element Elt)
{
	//On parcoure la liste des noeuds
	for (typename std::vector<Node_Elt*>::iterator it = m_Node.begin(); it != m_Node.end(); ++it)
	{
		//Si le noeud courant possède l'élément recherchée
		if ((*it)->m_Element == Elt)
		{
			return *it;
		}
	}
	//Pas trouvé
	return NULL;
}

template<class Type_Element>
void Graphe_Elt::unmark_all_nodes()
{
	for (typename std::vector<Node_Elt*>::iterator itnoeud = m_Node.begin(); itnoeud != m_Node.end(); ++itnoeud)
	{
		(*itnoeud)->m_node_marked = false;
	}
}

template<class Type_Element>
void Graphe_Elt::unmark_all_edges()
{
	//On parcoure tout les noeuds
	for (typename std::vector<Node_Elt*>::iterator itnoeud = m_Node.begin(); itnoeud != m_Node.end(); ++itnoeud)
	{
		//On parcoure toutes les arrêtes du noeud
		for (typename std::vector<Edge_Elt*>::iterator itedge = (*itnoeud)->m_Edge.begin(); itedge != (*itnoeud)->m_Edge.end(); ++itedge)
		{
			(*itedge)->m_edge_marked = false;
		}
	}
}

template<class Type_Element>
void Graphe_Elt::mark_edge(Node_Elt* Node1, Node_Elt* Node2)
{
	Edge_Elt* edge = Node1->findEdge(Node2);
	edge->mark_edge();
	if (!m_oriented)
	{
		edge = Node2->findEdge(Node1);
		edge->mark_edge();
	}
}

template<class Type_Element>
Graphe_Elt::Graphe(bool oriented)
{
	m_oriented = oriented;
}

template<class Type_Element>
Graphe_Elt::~Graphe()
{
	//On parcoure tout les noeuds
	for (typename std::vector<Node_Elt*>::iterator itnoeud = m_Node.begin(); itnoeud != m_Node.end(); ++itnoeud)
	{
		//(*itnoeud)->~Node();
		delete (*itnoeud);
	}
}

template<class Type_Element>
bool Graphe_Elt::find(Type_Element Elt)
{
	if (findNode(Elt) != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class Type_Element>
void Graphe_Elt::add(Type_Element Elt1, Type_Element Elt2, int cost, bool oriented)
{
	Node_Elt* Node1 = findNode(Elt1);
	if (Node1 == NULL)
	{
		//On crée le noeud uniquement si il n'existe pas déja
		Node1 = addNode(Elt1);
	}

	Node_Elt* Node2 = findNode(Elt2);
	if (Node2 == NULL)
	{
		//On crée le noeud uniquement si il n'existe pas déja
		Node2 = addNode(Elt2);
	}

	//On regarde si il existe déja un noeud dans la direction voulue
	if (Node1->findEdge(Node2) == NULL)
	{
		//Si c'est pas le cas, on ajoute une arrete
		Node1->addEdge(Node2, cost);
		//Si le graphe est non orienté et qu'il n'existe pas déja l'arrete
		if (!oriented && Node2->findEdge(Node1) == NULL)
		{
			Node2->addEdge(Node1, cost);
		}
	}
}

template<class Type_Element>
void Graphe_Elt::add(Type_Element Elt1, Type_Element Elt2, int cost)
{
	add(Elt1, Elt2, cost, m_oriented);
}

template<class Type_Element>
void Graphe_Elt::add(Type_Element Elt1, Type_Element Elt2)
{
	add(Elt1, Elt2, 1, m_oriented);
}

template<class Type_Element>
void Graphe_Elt::exportDot()
{
	unmark_all_edges();
	Edge_Elt* edge;
	cout << "digraph mon_graphe {" << endl;
	//On parcoure tout les noeuds
	for (typename std::vector<Node_Elt*>::iterator itnoeud = m_Node.begin(); itnoeud != m_Node.end(); ++itnoeud)
	{
		//On parcoure toutes les arrêtes du noeud
		for (typename std::vector<Edge_Elt*>::iterator itedge = (*itnoeud)->m_Edge.begin(); itedge != (*itnoeud)->m_Edge.end(); ++itedge)
		{
			edge = (*itnoeud)->findEdge((*itedge)->m_to);
			if (edge->m_edge_marked == false)
			{
				if (!m_oriented)
				{
					cout << "\"" << (*itnoeud)->m_Element << "\" -- \"" << (*itedge)->m_to->m_Element << "\"" << endl;
				}
				else
				{
					cout << "\"" << (*itnoeud)->m_Element << "\" -> \"" << (*itedge)->m_to->m_Element << "\"" << endl;
				}

				mark_edge(*itnoeud, (*itedge)->m_to);
			}

		}
	}
	cout << "}" << endl;
}

template<class Type_Element>
void Graphe_Elt::removeNode(Type_Element Elt_to_suppr)
{
	Node_Elt *node = findNode(Elt_to_suppr);
	if (node != NULL)
	{
		removeNode(node);
	}
}

template<class Type_Element>
void Graphe_Elt::removeNode(Node_Elt* Node_to_suppr)
{

}

template<class Type_Element>
void Graphe_Elt::remove_Edge(Type_Element Elt1, Type_Element Elt2)
{
	Node_Elt* n1 = findNode(Elt1);
	Node_Elt* n2 = findNode(Elt2);
	if (n1 == NULL || n2 == NULL)
	{
		cerr << "Erreur pour trouver les noeuds" << endl;
	}

	typename std::vector<Edge_Elt*>::iterator itedge_to_suppr;
	typename std::vector<Edge_Elt*>::iterator itedge;
	for (itedge = n1->m_Edge.begin(); itedge != n1->m_Edge.end(); itedge++)
	{
		if ((*itedge)->m_to == n2)
		{
			itedge_to_suppr = itedge;
			cerr << "found!" << endl;
			break;
		}
	}
	cerr << "lol" << endl;
    
	n1->m_Edge.erase(itedge_to_suppr);
}

//-----------------------------Classe-----------------------------------------------

template<class Type_Element>
class Node
{
	template <class> friend class Dijkstra;
	template <class> friend class Graphe;
	//Renvoi le nombre de voisin du noeud
	int getNbrVoisin();
private:
	//On stocke un élément dans le noeud
	Type_Element m_Element;
	//On stocke dans un tableaux les connexions entre ce noeud et d'autres noeuds
	std::vector<Edge_Elt*> m_Edge;
	//Noeud marqué?
	bool m_node_marked;
	//----Debut Variable Dijkstra
		//Pointeur sur le precedent
		Node_Elt* m_dij_prec;
		//Poids du noeud
		int m_dij_poids;
	//----Fin Variable Dijkstra
	//Constructeur
	Node(Type_Element Element);
	//Destructeur
	~Node();
	//Fonction de recherche. Renvoi, si il existe deja, le segment entre le noeud courant et Node_to. NULL sinon
	Edge_Elt* findEdge(Node_Elt* Node_to);
	//Ajoute un segment entre deux noeuds existant. Requiert que le segment n'existe pas déja.
	Edge_Elt* addEdge(Node_Elt* Node_to, int cost);
	//Marque le noeud
	void mark_node();

};

//-----------------------------------Méthodes--------------------------------

template<class Type_Element>
Node_Elt::Node(Type_Element Element)
{
	m_Element = Element;
}

template<class Type_Element>
Node_Elt::~Node()
{
	for (typename std::vector<Edge_Elt*>::iterator itedge = m_Edge.begin(); itedge != m_Edge.end(); ++itedge)
	{
		delete (*itedge);
	}
}

template<class Type_Element>
Edge_Elt* Node_Elt::findEdge(Node_Elt* Node_to)
{
	for (typename std::vector<Edge_Elt*>::iterator it = m_Edge.begin(); it != m_Edge.end(); ++it)
	{
		if ((*it)->m_to == Node_to)
		{
			return *it;
		}
	}
	return NULL;
}

template<class Type_Element>
Edge_Elt* Node_Elt::addEdge(Node_Elt* Node_to, int cost)
{
	Edge_Elt* new_edge = new Edge_Elt(Node_to, cost);
	m_Edge.push_back(new_edge);
	return new_edge;
}

template<class Type_Element>
void Node_Elt::mark_node()
{
	m_node_marked = true;
}

//Renvoi le nombre de voisin du noeud
template<class Type_Element>
int Node_Elt::getNbrVoisin()
{
	return (int) m_Edge->size();
}

//--------------------Classe--------------------------------------

template<class Type_Element>
class Edge
{
	template <class> friend class Node;
	template <class> friend class Graphe;
	template <class> friend class Dijkstra;
private:
	//Cout du chemin
	int m_cost;
	//Point d'arrivé
	Node_Elt* m_to;
	//Edge marqué?
	bool m_edge_marked;
	//Constructeur
	Edge(Node_Elt* to, int cost);
	//Marque edge
	void mark_edge();
};

//----------------------Méthodes------------------------------

template<class Type_Element>
Edge_Elt::Edge(Node_Elt* to, int cost)
{
	m_to = to;
	m_cost = cost;
}

template<class Type_Element>
void Edge_Elt::mark_edge()
{
	m_edge_marked = true;
}

template<class Type_Element>
void Graphe_Elt::dij_init()
{
	//On parcoure la liste des noeuds
	for (typename std::vector<Node_Elt*>::iterator it = m_Node.begin(); it != m_Node.end(); ++it)
	{
		//On initialise les variables de Dijkstra
		(*it)->m_dij_prec = NULL;
		(*it)->m_dij_poids = INT_MAX;
	}
}

template<class Type_Element>
Node_Elt* Graphe_Elt::dij_min()
{
	Node_Elt* min = NULL;
	//On parcoure la liste des noeuds
	for (typename std::vector<Node_Elt*>::iterator it = m_Node.begin(); it != m_Node.end(); ++it)
	{
		//Si le noeud courant n'est pas marqué
		if ( (*it)->m_node_marked == false)
		{
			//Si min est NULL
			if (min == NULL || (*it)->m_dij_poids < min->m_dij_poids)
			{
				min = *it;
			}
		}
	}

	//Si il ne reste que des noeuds non atteignables, alors on arrete dijkstra
	if (min != NULL && min->m_dij_poids == INT_MAX)
	{
		return NULL;
	}
	return min;
}

//On applique l'algorithme de Dijkstra
template<class Type_Element>
void Graphe_Elt::dij_compute(Type_Element Elt_debut)
{
	//On initialise les variables de Dijkstra
	dij_init();
	//On trouve le noeud de debut
	Node_Elt* node_debut = findNode(Elt_debut);
	if (node_debut == NULL)
	{
		cout << "Erreur : Le neoud de debut n'est pas présent dans le graphe" << endl;
		exit(1);
	}
	//On initialise les variables de Dijkstra du noeud de debut
	node_debut->m_dij_poids = 0;
	//On marque tous les noeuds comme non vus
	unmark_all_nodes();
	//On récupère le noeud de poids minimum non marqué
	Node_Elt* node_cour = dij_min();
	//Tant que tout les noeuds n'ont pas été vus
	while (node_cour != NULL)
	{
		//On marque node_cour come étant parcouru
		node_cour->mark_node();
		//On parcoure touts les suivant du noeuds courant
		for (typename std::vector<Edge_Elt*>::iterator it = node_cour->m_Edge.begin(); it != node_cour->m_Edge.end(); ++it)
		{
			Node_Elt* node_cour_suiv = (*it)->m_to;
			int dist_cour_suiv = (*it)->m_cost;
			if ((node_cour->m_dij_poids + dist_cour_suiv) < node_cour_suiv->m_dij_poids)
			{
				node_cour_suiv->m_dij_poids = node_cour->m_dij_poids + dist_cour_suiv;
				node_cour_suiv->m_dij_prec = node_cour;
			}
		}
		//On récupère le noeud de poids minimum non marqué
		node_cour = dij_min();
	}
}

//Renvoi le cout du plus court chemin
template<class Type_Element>
int Graphe_Elt::dij_get_cost(Type_Element Elt_Fin)
{
	Node_Elt* node_fin = findNode(Elt_Fin);
	if (node_fin == NULL)
	{
		cout << "ERREUR : Le noeud de fin n'est pas présent dans le graphe" << endl;
		exit(1);

	}
	return node_fin->m_dij_poids;
}

//Renvoi la chemin dans une deque
template<class Type_Element>
deque<Type_Element> Graphe_Elt::dij_get_path(Type_Element Elt_Fin)
{
	Node_Elt* node_fin = findNode(Elt_Fin);
	if (node_fin == NULL)
	{
		cout << "ERREUR : Le noeud de fin n'est pas présent dans le graphe" << endl;
		exit(1);
	}
	deque<Type_Element> chemin;
	Node_Elt* node_cour = node_fin;
	while (node_cour != NULL)
	{
		chemin.push_front(node_cour->m_Element);
		node_cour = node_cour->m_dij_prec;
	}
	return chemin;
}

int main()
{
	int N; // the total number of nodes in the level, including the gateways
	int L; // the number of links
	int E; // the number of exit gateways
	cin >> N >> L >> E; cin.ignore();

	//Graphe
	Graphe<int> G(true);
	for (int i = 0; i < L; i++) {
		int N1; // N1 and N2 defines a link between these nodes
		int N2;
		cin >> N1 >> N2; cin.ignore();
		G.add(N1, N2);
		G.add(N2, N1);
	}

	//Tableau des index des passerelles de sortie
	int *out = (int*)malloc(E * sizeof(int));

	for (int i = 0; i < E; i++) {
		int EI; // the index of a gateway node
		cin >> EI; cin.ignore();
		out[i] = EI;
		//On connecte chaque passerelle de sortie a une super sortie nommée -1
		G.add(EI, INDEX_FIN, 0);
	}

	// game loop
	while (1) {
		int SI; // The index of the node on which the Skynet agent is positioned this turn
		cin >> SI; cin.ignore();

		G.dij_compute(SI);
		
		deque<int> shortest_path;
		shortest_path = G.dij_get_path(INDEX_FIN);

		cout << shortest_path[0] << " " << shortest_path[1] << endl;
		G.remove_Edge(shortest_path[0], shortest_path[1]);
		G.remove_Edge(shortest_path[1], shortest_path[0]);

		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;

		//cout << "1 2" << endl; // Example: 0 1 are the indices of the nodes you wish to sever the link between
	}
}
