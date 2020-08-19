#include <iostream>
#include <fstream>

using namespace std;
fstream plik;

class graph {
public:
	struct node {
		int vertex;
		int from;
		int way;
		node* next;
	};

	struct edge {
		int val;
		edge*next;
	};

	struct queue{
		int val;
		queue* next;
	};

	graph();
	void ListaSasiedztwa();
	void wszerz(int s);
	void glab(int s);
	void Sortowanko(node *&H, int vertex, int way);

	int H;
	int size;
	node **tab;
	queue *Q;
	queue *T;
	char *kolorki;
	int * wczesniejszy;
	int *odleglosc;
	bool *visited;
	void add(node*&H, int vx, int wy);
	void dodawanko(edge*&, int x);
	bool isEmpty(queue *Q, queue *T);
	int top(queue*Q, queue*T);
	void dequeue(queue*&Q,queue*&T);
	void enqueue(queue*&Q,queue*&T, int x);
	void visit(int s);

};

graph::graph() {
	queue *Q = NULL;
	queue *T = NULL;
	kolorki = new char[size];
	wczesniejszy = new int[size];
	odleglosc = new int[size];
}


void graph::add(node*&H, int vx, int wy) {
	node *e = new node;
	e->next = NULL;
	e->vertex = vx;
	e->way = wy;
	node *p;
	p = H;
	if (p != NULL) {
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = e;
	}
	else
		H = e;
	}

void graph::ListaSasiedztwa() {
	int x;
	plik.open("graf.txt");
	plik >> size;
	tab = new node*[size];
	for (int i = 0; i < size; i++) {
		tab[i] = NULL;
	}
	for (int i = 0; i <size; i++) {
		for (int j = 0; j < size; j++) {
			plik >> x;
			if (x != 0) {
				add(tab[i], j, x);
			}
		}
	}
	for (int i = 0; i <size ; i++) {
		node* H = tab[i];
		cout << "  "<< i << ": ";
		while (H != NULL) {
			cout << H->vertex << "->";
			H = H->next;
		}
		cout << "NULL" << endl;
	}
	cout << endl;
}

void graph::dodawanko(edge*&H, int x) {
	edge* p = new edge;
	p->val = x;
	p->next = H;
	H = p;
}

void graph::visit(int p) {
	kolorki[p] = 'B';
	node *a = tab[p];
	while (a != NULL) {
		if (kolorki[a->vertex] != 'B') {
			wczesniejszy[a->vertex] = p;
			odleglosc[a->vertex] = odleglosc[p] + a->way;
			visit(a->vertex);
		}
		a = a->next;
	}
}


void graph::glab(int s) {
	/*enum kolor{
		biały, czarny
	};
	kolor* kolorki = new kolor[size];*/
	for (int i = 0; i < size; i++) {			
		kolorki[i] = 'W';
		wczesniejszy[i] = -1;
		odleglosc[i] = 0;
	}
	visit(s);
	for (int j = 0; j < size; j++) {
		if (kolorki[j] == 'W')
			visit(j);
	}
}

void graph::dequeue(queue *&Q, queue*&T) {
	if (Q != NULL) {
		queue *p = Q;
		Q = Q->next;
		delete p;
		if (Q == NULL) {
			T = NULL;
		}
	}
}

void graph::enqueue(queue*&Q, queue*&T, int x) {
	queue *p = new queue;
	p->val = x;
	p->next = NULL;
	if (Q == NULL) {
		Q = p;
	}
	else {
		T->next = p;
	}
	T = p;
}

bool graph::isEmpty(queue *Q, queue *T) {
	if (Q == NULL)
		return 1;
	else
		return 0;
}


int graph::top(queue*Q,queue*T){
	if (Q != NULL) {
		return Q->val;
	}
}

void graph::wszerz(int s) {
	enum kolorki{
		bialy,szary,czarny
	};
	kolorki* kolor = new kolorki[size];
	edge* zm = NULL;
	for (int i = 0; i < size; i++){
		kolor[i] = bialy;
	}
		kolor[s] = szary;
		int dystans = 0;
		dodawanko(zm, s);
		enqueue(Q, T, s);
		while (isEmpty(Q,T)==0){
			s = top(Q,T);
			kolor[s] = czarny;
			dequeue(Q, T);
			while (tab[s]!=NULL && tab[s]->next!=NULL){
				int u = tab[s+1]->vertex;
				if (kolor[u] == bialy){
					kolor[u] = szary;
					dystans= dystans+tab[u]->way;
					dodawanko(zm, u);
					enqueue(Q, T, u);
				}
				tab[s] = tab[s]->next;
			}
		}
	}

void graph::Sortowanko(node *&H, int vertex, int way){
	if (H != NULL){
		node* p = H;
		if (H->way > way) {
			add(H, vertex, way);
		}
		else {
			while (p->next && p->next->way < way) {
				p = p->next;
			}
			add(p->next, vertex, way);
		}
	}
	else {
		add(H, vertex, way);
	}
}

int main() {
	
	
	graph graf;
	graf.ListaSasiedztwa();
	graf.wszerz(1); 
	graf.glab(2);
	

	system("pause");
	return 0;
}