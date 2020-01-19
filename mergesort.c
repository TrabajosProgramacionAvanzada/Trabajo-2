#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Estructura de la lista enlazada
typedef struct NodeD{
  double valor;
  long long int repeticion;
  struct NodeD* siguiente;
} node;

//Función que inicializa un nodo vacío
node* initNodeD(node *head){
  node* nodo = malloc(sizeof(node));
  nodo->valor = 0.0;
  nodo->repeticion = 0;
  nodo->siguiente = NULL;
  head = nodo;
  return head;
}

//Función que insera un valor al inicio una lista
node* instertND(node* head, double n){
  node* new = initNodeD(new);
  new->valor = n;
  node* aux = head;
  new->siguiente = head;
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
	if(head){
		while (rapido->siguiente && rapido->siguiente->siguiente){//Si existe el siguiente del rápido y el siguiente a éste 
		rapido = rapido->siguiente->siguiente;//Avanza dos con el rápido 
		lento = lento->siguiente; //Avanza uno con el lento
	} //A este punto el lento debe ir en la mitad mientras el otro al fin de la lista
	aux = lento->siguiente; //inicio de la segunda mitas
	lento->siguiente = NULL; //corte desde primera
  	}	
  	return aux; 
} 

node* recorrerLista(node* head){
	node* aux = head;
	while(head && aux->siguiente){
		aux = aux->siguiente;
	}
	return aux;
}


node* merge_sorted(node* A, node* B){
	node* auxA = A;
	node* auxB = B;
	node* head = NULL;
	node* aux = NULL;
	node* elim = NULL;
	if(A && B){//Si hay ambas listas para ordenar
		while(auxA && auxB){
			//printf("\nwhile\n");
			if(auxA->valor < auxB->valor){
			//printf("\n<\n");
				if(!head){
					head = aux = auxA;
					auxA = auxA->siguiente;
					aux->siguiente = NULL;
				}
				else{
					aux->siguiente = auxA;
					auxA = auxA->siguiente;
					aux = aux->siguiente;
				}
			}else if(auxA->valor > auxB->valor){
			//printf("\n>\n");
				if(!head){
					head = aux = auxB;
					auxB = auxB->siguiente;
					aux->siguiente = NULL;
				}
				else{
					aux->siguiente = auxB;
					auxB = auxB->siguiente;
					aux = aux->siguiente;
				}
			}else{
			//printf("\n=\n");
				if(!head){
					head = aux = auxA;
					auxA = auxA->siguiente;
					elim = auxB;
					elim->siguiente = NULL;
					auxB = auxB->siguiente;
					aux->siguiente = NULL;
				}
				else{
					aux->siguiente = auxA;
					auxA = auxA->siguiente;
					elim = auxB;
					auxB = auxB->siguiente;
					aux = aux->siguiente;
					aux->repeticion++;
				}
				free(elim);
			}
		}
		if(auxA){
			//printf("\nqueda A\n");
			if(aux && head)
				aux->siguiente = auxA;
			else
				head = auxA;
		}else if(auxB){
			//printf("\nqueda B\n");
			if(aux && head)
				aux->siguiente = auxB;
			else
				head = auxB;
		}
	}else if (A){
			//printf("\nB NULL\n");
		return A;
	}else{
			//printf("\nA NULL\n");
		return B;
		}
	return head;
}



node* mergeSort(node* head){
	node* mitad = split(head);;//caso base es el penúltimo
	node* aux1 = NULL;
	node* aux2 = NULL;
	node *sorted = NULL;
	if(head && mitad){
		aux1 = mergeSort(mitad);
		aux2 = mergeSort(head);
		sorted = merge_sorted(aux1, aux2);
		return sorted;	
	}else if(head)
		return head;
	else
		return mitad;
	return NULL;
}


int main(){	
	double time1 = 0.0;
	double time2 = 0.0;
	double numero;
	char c = '\0';
	node* head = NULL;
	node* result = NULL;
	node* aux = NULL;
	FILE* documento;
	time1 = clock();
	documento=fopen("ArchivoA.tex", "r");
	while(1 == fscanf(documento, "%le", &numero)){
	  head = instertND(head, numero);
	}
	fclose(documento);
	time1 = (clock() - time1) / CLOCKS_PER_SEC;
	printf("lectura de archivo: %.4lf \n", time1);
	time1 = clock();
	result = mergeSort(head);
	time1 = (clock() - time1) / CLOCKS_PER_SEC;
	printf("merge sort: %.4lf \n", time1);
	// getchar();
	// display(result);
	head = eliminarLista(head);
	return 0;
}
