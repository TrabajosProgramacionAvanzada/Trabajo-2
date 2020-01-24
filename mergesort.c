#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Estructura de la lista enlazada para mergesort
typedef struct NodeM{
  double valor;
  long long int repeticion;
  struct NodeM* siguiente;
} nodeM;

//Función que inicializa un nodo vacío
nodeM* initNodeM(nodeM *head){
  nodeM* nodo = malloc(sizeof(nodeM));
  nodo->valor = 0.0;
  nodo->repeticion = 0;
  nodo->siguiente = NULL;
  head = nodo;
  return head;
}

//Función que insera un valor al inicio una lista
nodeM* instertM(nodeM* head, double n){
  nodeM* new = initNodeM(new);
  new->valor = n;
  nodeM* aux = head;
  new->siguiente = head;
  return new;
}

void displayM(nodeM* head){
  int i = 1;
  while (head != NULL) { 
    printf("%le - %d \n", head->valor, i);
    head = head->siguiente;
    i++;
  }
  return;
} 

nodeM* eliminarListaM(nodeM* head){
  nodeM* aux = head;
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

nodeM *splitM(nodeM *head){ 
	nodeM *rapido = head,*lento = head; //rápido avanza dos por cada uno que avanza el lento
	nodeM *aux = NULL;//auxiliar
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

nodeM* recorrerLista(nodeM* head){
	nodeM* aux = head;
	while(head && aux->siguiente){
		aux = aux->siguiente;
	}
	return aux;
}


nodeM* merge_sorted(nodeM* A, nodeM* B){
	nodeM* auxA = A;
	nodeM* auxB = B;
	nodeM* head = NULL;
	nodeM* aux = NULL;
	nodeM* elim = NULL;
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



nodeM* mergeSort(nodeM* head){
	nodeM* mitad = splitM(head);;//caso base es el penúltimo
	nodeM* aux1 = NULL;
	nodeM* aux2 = NULL;
	nodeM *sorted = NULL;
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
	nodeM* head = NULL;
	nodeM* result = NULL;
	nodeM* aux = NULL;
	FILE* documento;
	time1 = clock();
	documento=fopen("ArchivoB.tex", "r");
	while(1 == fscanf(documento, "%le", &numero)){
	  head = instertM(head, numero);
	}
	fclose(documento);
	time1 = (clock() - time1) / CLOCKS_PER_SEC;
	printf("lectura de archivo: %.4lf \n", time1);
	time1 = clock();
	result = mergeSort(head);
	time1 = (clock() - time1) / CLOCKS_PER_SEC;
	printf("merge sort: %.4lf \n", time1);
	// getchar();
	// displayM(result);
	head = eliminarListaM(head);
	return 0;
}
