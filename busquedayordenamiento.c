#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct NodeD{
  double valor;
  unsigned long long int repeticiones;
  struct NodeD* siguiente;
  struct NodeD* anterior;
};

struct NodeD initNodeD(struct NodeD nodo){
  nodo.valor = 0.0;
  nodo.repeticiones = 0;
  nodo->siguiente = NULL;
  nodo->anterior = NULL;
}

struct ListD{
  struct NodeD* head;
  struct NodeD* mid;
  unsigned long long int cantidad;
};

struct ListD initListD(struct ListD lista){
  lista.cantidad = 0;
  lista->head = initNodeD(lista->head);
  lista->mid = head;
}


struct NodeD* instertND(struct  NodeD* head, double n){
  struct NodeD* new = initNodeD(new);
  struct NodeD* aux = head;
  if(head == NULL){
    new.valor = n;
    return new;
  }
  else{
    if(n < head.valor){
      new.valor = n;
      new->siguiente = head;
      head->anterior = new;
    }else{
      if(head.valor == n){
	head.repeticiones++;
	return head;
      }
      while(aux->siguiente != NULL && n > aux->siguiente.valor){
	aux = aux->siguiente;
      }
      if(aux->siguiente.valor == n){
	aux->siguiente.repeticiones++;
      }else{
	new->siguiente = aux->siguiente;
	aux->siguiente->anterior = new;
	aux->siguiente = new;
	new->anterior = aux;
      }
    }
  }
  return head;
}

struct ListD* instertL(struct  ListD* lista, double n){
  lista->head = initNodeD(lista->head, n);
  lista.cantidad++;
  if(lista.cantidad%2 == 0 && lista.cantidad >= 4){
    lista->mid = list->mid->siguiente;
  }
  return lista;
}

int main(){	
	double longitud;
	double aux = 0;
	FILE* documento;
	int i=1;
	documento=fopen("ArchivoA.tex", "r");
	fscanf(documento, "%le", &longitud);
	while(longitud != aux){
	  printf("%le - %d\n", longitud, i);
	  i++;
	  aux = longitud;
	  fscanf(documento, "%le", &longitud);
	}

	fclose(documento);

	return 0;
}
