#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct NodeD{
  double valor;
  unsigned long long int repeticiones;
  struct NodeD* siguiente;
  struct NodeD* anterior;
} node;

node* initNodeD(node *head){
  node* nodo = malloc(sizeof(node));
  nodo->valor = 0.0;
  nodo->repeticiones = 0;
  nodo->siguiente = NULL;
  nodo->anterior = NULL;
  head = nodo;
  return head;
}

typedef struct ListD{
  node* head;
  unsigned long long int cantidad;
}list;

list initListD(list lista){
  lista.cantidad = 0;
  lista.head = NULL;
}


node* instertND(node* head, double n){
  node* new = initNodeD(new);
  new->valor = n;
  node* aux = head;
  new->siguiente = head;
  return new;
}

list instertL(list lista, double n){
  lista.head = instertND(lista.head, n);
  lista.cantidad++;
  return lista;
}

int main(){	
	double longitud;
	double aux = 0;
	node* auxN = initNodeD(auxN);
	node* aux2 = NULL;
	FILE* documento;
	int i=1;
	documento=fopen("ArchivoA.tex", "r");
	while(1 == fscanf(documento, "%le", &longitud)){
	  //printf("%le - %d\n", longitud, i);
	  auxN = instertND(auxN, longitud);
	  //printf("%le - %d\n", auxN->valor, i);
	  i++;
	  fscanf(documento, "%le", &longitud);
	}
	fclose(documento);
	aux2 = auxN;
	printf("le");
	printf("%le", aux2->valor);
	i = 1;
	while(aux2 != NULL){
	  printf("%le - %d\n", aux2->valor, i);
	  aux2 = aux2->siguiente;
	  i++;
	}
	return 0;
}
