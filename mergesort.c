#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Estructurua de dato del node Linked list

typedef struct nodeP{

	double dato;
	struct nodeP* next;

}node;

//inicializacion de nodo
/*
node* initNodeP(node *head){
	node* nodo = malloc(sizeof(node));
	nodo->dato = 0.0;
	nodo->next = NULL;
	head = nodo;
	return head;
}
*/

//insertar elemento en principio de la lista

void push(node **head, long dato){

	node *nNode = (node *)malloc(sizeof(node));
	nNode -> dato = dato;
	nNode -> next =*head;
	*head = nNode;
	
}

// Funcion Display recursiva 

void display(node *head){
	node* aux = NULL;
	aux=head;
	while(aux){
		printf("%f", aux -> dato);
		aux = aux -> next;		
	}	
	
}


//Ordenar dos listas de manera creciente 
node* SortMerge(node* aux1, node* aux2){

	//caso base
	if(aux1 == NULL)
		return aux2;
	else if(aux2 == NULL)
			return aux1;

	node *resultado = NULL;

	if(aux1 -> dato <= aux2 -> dato){
		resultado = aux1;
		resultado ->next = SortMerge(aux1->next, aux2);
		printf("ENTRE\n");

	}
	else{
		resultado = aux2;
		resultado ->next = SortMerge(aux1, aux2 -> next);
	}
	return resultado;
}


//Dividir lista en dos sublistas
void splitlist(node* head, node** list1, node** list2){

	//si el largo es menor que dos, no se separa
	if(head==NULL || head->next==NULL){
		*list1 = head;
		*list2 = NULL;
		return;
	}

	node* aux1=NULL;
	node* aux2=NULL;

	aux1=head;
	aux2=head->next;

	while(aux2 != NULL){

		aux2 = aux2 -> next;
		if(aux2 != NULL){
			aux1 = aux1 -> next;
			aux2 = aux2 -> next;

		}
	}

	*list1 = head;
	*list2 = aux1 ->next;
	aux1 -> next = NULL;

}

//mergesort

void MergeSort(node** head){

	if(*head == NULL || (*head)->next == NULL)
		return;
	
	node* aux1=NULL;
	node* aux2=NULL;

	//dividir listas 
	splitlist(*head, &aux1, &aux2);

	//recursion entre las listas
	MergeSort(&aux1);
	MergeSort(&aux2);

	*head = SortMerge(aux1,aux2);
}


// funcion principal 
int main(){

	double time1 = 0.0;
	double time2 = 0.0;
	double largo;
	double numero;
	node* head = NULL;
	FILE* documento;
	largo=0;

	documento=fopen("ArchivoA.tex", "r");
	while(1==fscanf(documento, "%le", &numero)){
		push(&head, numero);
		largo++;
	}
	fclose(documento);
	//printf("%f",largo );

	MergeSort(&head);
	display(head);


	return 0;
}