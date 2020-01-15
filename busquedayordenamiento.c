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

node* instertND(node* head, double n){
  node* new = initNodeD(new);
  new->valor = n;
  node* aux = head;
  new->siguiente = head;
  return new;
}

int main(){	
	double numero;
	node* head = initNodeD(head);
	node* aux = NULL;
	FILE* documento;
	int i=1;
	documento=fopen("ArchivoA.tex", "r");
	while(1 == fscanf(documento, "%le", &numero)){
	  head = instertND(head, numero);
	  i++;
	}
	fclose(documento);
	scanf("%d", &i);
	i = 0;
	aux = head;
	while(aux != NULL){
	  printf("%le - %d\n", aux->valor, i);
	  aux = aux->siguiente;
	  i++;
	}
	return 0;
}
