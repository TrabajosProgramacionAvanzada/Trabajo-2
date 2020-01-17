#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Estructura de la lista enlazada
typedef struct NodeD{
  double valor;
  unsigned long long int repeticiones;
  struct NodeD* siguiente;
  struct NodeD* anterior;
} node;

//Función que inicializa un nodo vacío
node* initNodeD(node *head){
  node* nodo = malloc(sizeof(node));
  nodo->valor = 0.0;
  nodo->repeticiones = 0;
  nodo->siguiente = NULL;
  nodo->anterior = NULL;
  head = nodo;
  return head;
}

//Función que insera un valor al inicio una lista
node* instertND(node* head, double n){
  node* new = initNodeD(new);
  new->valor = n;
  node* aux = head;
  new->siguiente = head;
  if(head != NULL)
    head->anterior = new;
  return new;
}

void display(node* head){
  int i = 1;
  while (head != NULL) { 
    printf("%le - %d \n", head->valor, i);
    head = head->siguiente;
    i++;
  }
  return;
} 

node* eliminarLista(node* head){
  node* aux = head;
  while(head){
    head = head->siguiente;
    free(aux);
    aux = head;
  }
  return head;
}

node *split(node *head){ 
  node *rapido = head,*lento = head; //rápido avanza dos por cada uno que avanza el lento
  node *aux = NULL;//auxiliar
  while (rapido->siguiente && rapido->siguiente->siguiente){//Si existe el siguiente del rápido y el siguiente a éste 
    rapido = rapido->siguiente->siguiente;//Avanza dos con el rápido 
    lento = lento->siguiente; //Avanza uno con el lento
  } //A este punto el lento debe ir en la mitad mientras el otro al fin de la lista
  aux = lento->siguiente; //inicio de la segunda mitas
  lento->siguiente = NULL; //corte desde primera
  aux->anterior = NULL; //corte desde segunda
  return aux; 
} 

