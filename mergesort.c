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

int max_comp(double a, double b){
  return (a < b) ? -1 : (a == b) ? 0 : 1; 
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

node* merge_sorted(node* A, node* B){
	node* aux1 = NULL;
	node* aux2 = NULL;
	if(A->siguiente && B->siguiente){
		if(max_comp(A->valor, B->valor) < 0){
			aux1 = A->siguiente;
			A->siguiente = NULL;
			aux1->anterior = NULL;
			aux1 = merge_sorted(aux1, B);
			aux1->anterior = A;
			A->siguiente = aux1;
			aux1 = A;
		}else if(max_comp(A->valor, B->valor) > 0){
			aux1 = B->siguiente;
			B->siguiente = NULL;
			aux1->anterior = NULL;
			aux1 = merge_sorted(A, aux1);
			aux1->anterior = B;
			B->siguiente = aux1;
			aux1 = B;
		}else{
			aux2 = B->siguiente;
			aux2->anterior = NULL;
			free(B);
			aux1 = A->siguiente;
			A->siguiente = NULL;
			aux1->anterior = NULL;
			aux1 = merge_sorted(aux1, aux2);
			if(max_comp(aux1->valor, A->valor) != 0){
				aux1->anterior = A;
				A->siguiente = aux1;
				A->repeticiones++;
				aux1 = A;
			}else{
				aux1->repeticiones++;
				free(A);
			}
		}	
	}else if (A){
		return A;
	}else{
		return B;
	}
	return aux1;
}

node* mergeSort(node* head){
	node* mitad = NULL;//caso base es el penúltimo
	if(head && head->siguiente){
		mitad = split(head);
		if(mitad && mitad->siguiente)
			return merge_sorted(head, mitad);
		else if(head->siguiente){
			return merge_sorted(mergeSort(head),mitad);
		}else{
			return merge_sorted(head, mitad);
		}
	}else{
		return head;
	}
}

int main() {
	node* head = NULL;
	head = instertND(head, 1.673847436e+24);
	head = instertND(head, 1.673847436e-24);
	head = instertND(head, 1.673848436e+4);
	head = instertND(head, 1.673892436e+2);
	head = instertND(head, 5.673847436e+0);
	head = instertND(head, 1.673736436e+6);
	head = instertND(head, 11.673847436e+5);
	head = instertND(head, 10.673847436e-1);
	head = instertND(head, 8.8734847436e+9);
	head = instertND(head, 0.673847436e-4);
	head = instertND(head, 20.673847436e+10);
	head = instertND(head, 1.673847436e+24);
	head = instertND(head, 1.673847436e-24);
	head = instertND(head, 1.673848436e+4);
	head = instertND(head, 1.673892436e+2);
	head = instertND(head, 5.673847436e+0);
	head = instertND(head, 1.673736436e+6);
	head = instertND(head, 11.673847436e+5);
	head = instertND(head, 10.673847436e-1);
	head = instertND(head, 8.8734847436e+9);
	head = instertND(head, 0.673847436e-4);
	head = instertND(head, 20.673847436e+10);
	head = instertND(head, 1.673847436e+24);
	head = instertND(head, 1.673847436e-24);
	head = instertND(head, 1.673848436e+4);
	head = instertND(head, 1.673892436e+2);
	head = instertND(head, 5.673847436e+0);
	head = instertND(head, 1.673736436e+6);
	head = instertND(head, 11.673847436e+5);
	head = instertND(head, 10.673847436e-1);
	head = instertND(head, 8.8734847436e+9);
	head = instertND(head, 0.673847436e-4);
	head = instertND(head, 20.673847436e+10);
	head = instertND(head, 1.673847436e+24);
	head = instertND(head, 1.673847436e-24);
	head = instertND(head, 1.673848436e+4);
	head = instertND(head, 1.673892436e+2);
	head = instertND(head, 5.673847436e+0);
	head = instertND(head, 1.673736436e+6);
	head = instertND(head, 11.673847436e+5);
	head = instertND(head, 10.673847436e-1);
	head = instertND(head, 8.8734847436e+9);
	head = instertND(head, 0.673847436e-4);
	head = instertND(head, 20.673847436e+10);
	head = instertND(head, 1.673847436e+24);
	head = instertND(head, 1.673847436e-24);
	head = instertND(head, 1.673848436e+4);
	head = instertND(head, 1.673892436e+2);
	head = instertND(head, 5.673847436e+0);
	head = instertND(head, 1.673736436e+6);
	head = instertND(head, 11.673847436e+5);
	head = instertND(head, 10.673847436e-1);
	head = instertND(head, 8.8734847436e+9);
	head = instertND(head, 0.673847436e-4);
	head = instertND(head, 20.673847436e+10);
	head = instertND(head, 1.673847436e+24);
	head = instertND(head, 1.673847436e-24);
	head = instertND(head, 1.673848436e+4);
	head = instertND(head, 1.673892436e+2);
	head = instertND(head, 5.673847436e+0);
	head = instertND(head, 1.673736436e+6);
	head = instertND(head, 11.673847436e+5);
	head = instertND(head, 10.673847436e-1);
	head = instertND(head, 8.8734847436e+9);
	head = instertND(head, 0.673847436e-4);
	head = instertND(head, 20.673847436e+10);
	head = instertND(head, 1.673847436e+24);
	head = instertND(head, 1.673847436e-24);
	head = instertND(head, 1.673848436e+4);
	head = instertND(head, 1.673892436e+2);
	head = instertND(head, 5.673847436e+0);
	head = instertND(head, 1.673736436e+6);
	head = instertND(head, 11.673847436e+5);
	head = instertND(head, 10.673847436e-1);
	head = instertND(head, 8.8734847436e+9);
	head = instertND(head, 0.673847436e-4);
	head = instertND(head, 20.673847436e+10);
	head = mergeSort(head);
	display(head);
	head = eliminarLista(head);
	return 0;
}
