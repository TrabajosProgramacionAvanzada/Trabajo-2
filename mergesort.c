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
  while (rapido->siguiente && rapido->siguiente->siguiente){//Si existe el siguiente del rápido y el siguiente a éste 
    rapido = rapido->siguiente->siguiente;//Avanza dos con el rápido 
    lento = lento->siguiente; //Avanza uno con el lento
  } //A este punto el lento debe ir en la mitad mientras el otro al fin de la lista
  aux = lento->siguiente; //inicio de la segunda mitas
  lento->siguiente = NULL; //corte desde primera
  return aux; 
} 

node* recorrerLista(node* head){
	node* aux = head;
	while(head && aux->siguiente){
		aux = aux->siguiente;
	}
	return aux;
}


node* merge_sorted(node* A, node* B, node* head){
	node* auxA = A;
	node* auxB = B;
	node* aux = NULL;
	node* elim = NULL;
	aux = recorrerLista(head);
	if(A && B){//Si hay ambas listas para ordenar
		while(auxB && auxA){
			if(auxA->valor < auxB->valor){
				if(aux){
					aux->siguiente = auxA;
					auxA = auxA->siguiente;
					aux = aux->siguiente;
					aux->siguiente = NULL;
				}else{
					aux = head = auxA;
					auxA = auxA->siguiente;
					aux->siguiente = NULL;
				}
			}else if(auxA->valor < auxB->valor){
				if(aux){
					aux->siguiente = auxB;
					auxB = auxB->siguiente;
					aux = aux->siguiente;
					aux->siguiente = NULL;
				}else{
					aux = auxB;
					auxB = auxB->siguiente;
					aux->siguiente = NULL;
				}
			}else if(aux && auxA->valor == auxB->valor && auxB->valor != aux->valor){
				aux->siguiente = auxA;
				auxA = auxA->siguiente;
				aux = aux->siguiente;
				aux->siguiente = NULL;
				aux->repeticion++;
				elim = auxB;
				auxB = auxB->siguiente;
				free(elim);
			}else if(aux){
				aux->repeticion = aux->repeticion + 2;
				elim = auxA;
				auxA = auxA->siguiente;
				free(elim);
				elim = auxB;
				auxB = auxB->siguiente;
				free(elim);
			}else{
				aux = auxA;
				auxA = auxA->siguiente;
				elim = auxB;
				auxB = auxB->siguiente;
				free(elim);
				aux->siguiente = NULL;
				aux->repeticion++;
			}
		}
		if(auxA){
			aux->siguiente = auxA;
			auxA = auxA->siguiente;
			aux = aux->siguiente;
		}else if(auxB){
			aux->siguiente = auxB;
			auxB = auxB->siguiente;
			aux = aux->siguiente;
		}
	}
	if(A){
		if(aux)
			aux->siguiente = auxA;
		else
			head = auxA;
	}else if (B){
		if(aux)
			aux->siguiente = auxB;
		else
			head = auxB;
	}
	return head;
}



node* mergeSort(node* head, node *sorted){
	node* mitad = split(head);//caso base es el penúltimo
	node* aux1 = NULL;
	if(head){
		
	}
	return sorted;
}


int main(){	
	double time1 = 0.0;
	double time2 = 0.0;
	double numero;
	char c = '\0';
	node* head = NULL;
	node* result = NULL;
	//FILE* documento;
	//time1 = clock();
	// documento=fopen("ArchivoA.tex", "r");
	// while(1 == fscanf(documento, "%le", &numero)){
	//   head = instertND(head, numero);
	// }
	// fclose(documento);
	//time1 = (clock() - time1) / CLOCKS_PER_SEC;
	//printf("lectura de archivo: %.4lf \n", time1);
	head = instertND(head, 1);
	head = instertND(head, 10);
	head = instertND(head, 5);
	head = instertND(head, 8);
	head = instertND(head, 2);
	head = instertND(head, 4);
	head = instertND(head, 6);
	head = instertND(head, 3);
	head = instertND(head, 9);
	time1 = clock();
	result = mergeSort(head, result);
	time1 = (clock() - time1) / CLOCKS_PER_SEC;
	printf("merge sort: %.4lf \n", time1);
	getchar();
	display(head);
	head = eliminarLista(head);
	return 0;
}
