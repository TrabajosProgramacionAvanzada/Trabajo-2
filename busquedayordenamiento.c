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

//Función que intercambia dos valores en una lista
void swap( double* a, double* b ){
  double t = *a;
  *a = *b;
  *b = t;
} 

//Función que devuelve el último valor de una lista enlazada
node *lastND(node *head) 
{ 
    while (head && head->siguiente) 
        head = head->siguiente; 
    return head; 
}

/* Considerando el último elemento como pivote, se posicionan los elementos menores de un lado del pivote y los mayores al otro */
node* partition(node *l, node *h){ 
  double x = h->valor; //selecciona a h como pivote 
  node *i = l->anterior; //Centinela
  node *j = NULL;
  for (j = l; j != h; j = j->siguiente){ //recorremos la lista con j 
    if (j->valor <= x){ //si el valor actual es menor o igual al pivote
      i = (i == NULL) ? l : i->siguiente;//avanza 
      swap(&(i->valor), &(j->valor)); //intercambia los valores entre el valor límite de i con el actual
    } 
  } 
  if(i == NULL){//Si no existe i
    i = l;//Se le asigna el elemento límite (en éste caso el primer elemento)
  }else{
    i = i->siguiente;//De lo contrario pasa al siguiente
  }
  swap(&(i->valor), &(h->valor)); //intercambia valores entre el valor límite con el pivote
  return i; 
} 

//Paso inductivo de Quick Sort
void quickSortI(node* lista, node *pivote){ 
  if (pivote != NULL && lista != pivote && lista != pivote->siguiente){//Si existe el pivote y es diferente al pivote y es diferente al que le sigue al pivote
    node *p = partition(lista, pivote); //Se realiza la partición en torno al pivote
    quickSortI(lista, p->anterior);//Se ordena parcialmente un lado 
    quickSortI(p->siguiente, pivote); //ahora el otro
  }
  return;
} 

void QuickSort(node *head){ 
    node *aux = lastND(head);//encuentra el último nodo 
    quickSortI(head, aux); //llama a la función recurrsiva de Quick Sort
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

//Función que mezcla dos listas ordenadas
node *merge(node *first, node *second) 
{ 
    // If first linked list is empty 
    if (!first) 
        return second; 
  
    // If second linked list is empty 
    if (!second) 
        return first; 
  
    // Pick the smaller value 
    if (first->valor < second->valor) 
    { 
        first->siguiente = merge(first->siguiente,second); 
        first->siguiente->anterior = first; 
        first->anterior = NULL; 
        return first; 
    } 
    else
    { 
        second->siguiente = merge(first,second->siguiente); 
        second->siguiente->anterior = second; 
        second->anterior = NULL; 
        return second; 
    } 
}    

node* Split(node* head){ 
  node* aux = NULL;
  node* lento = head;//Avanza de a un nodo 
  node* rapido = head; //Avanza de a dos nodos
  while (rapido->siguiente != NULL && rapido->siguiente->siguiente != NULL){//avanza dos para rápido y uno de lento hasta que el rápido haya llegado al final, y por tanto el lento se posicione en la mitad 
    rapido = rapido->siguiente->siguiente; 
    lento = lento->siguiente; 
  } //lento ya está en la mitad a cortar
  aux = lento->siguiente;
  lento->siguiente = NULL;
  return aux;//devuelve el inicio de la segunda mitad
}



//Función que ordena por mezcla una lista
node *MergeSort(node *head){  
  if (!head || !head->siguiente)//Caso base si no existe la lista o tiene un sólo elemento  
    return head;  
  node *segundo = Split(head);  
  head = MergeSort(head);//Sigue ordenando las mitades recurrsivamente  
  segundo = MergeSort(segundo);    
  return merge(head, segundo);//mezcla las dos listas  
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

int main(){	
	double time1 = 0.0;
	double time2 = 0.0;
	double numero;
	char c = '\0';
	node* head = initNodeD(head);
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
	time2 = clock();
	head = MergeSort(head);
	time2 = (clock() - time2) / CLOCKS_PER_SEC;
	printf("merge sort: %.4lf \n", time2);
	//display(head);
	head = eliminarLista(head);
	return 0;
}
