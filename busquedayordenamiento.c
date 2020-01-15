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

//Estructura del heap
typedef struct NodeHeap{
  double valor=0; //Clave del nodo
  unsigned long long int repeticiones=0; //Veces que se repite la clave
  int bal=0; //Balance
  struct NodeHeap *izquerda;
  struct NodeHeap *derecha;
} heap;

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

//Función que inicializa un heap vacío
heap* initHeap(heap *root){
  heap* nodo = malloc(sizeof(heap));
  nodo->valor = 0.0;
  nodo->repeticiones = 0;
  nodo->izquerda = NULL;
  nodo->derecha = NULL;
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

heap* insertHeap(heap* root, double n){
  heap* new = initHeap(new);
  if(root == NULL){
    return new;
  }else{
    if(root->izquerda->bal - root->derecha->bal <= 0){
      root->izquerda = insertHeap(root->izquerda, n);
      if(root->derecha)
	root->bal = root->derecha->bal - root->izquerda->bal + 1;
    }else{
      root->derecha = insertHeap(root->derecha, n);
      if(root->izquerda)
	root->bal = root->derecha->bal - root->izquerda->bal + 1;
    }
    else{
      root->bal = -1;
    }
  }
  return root;
}

heap* monticular(heap* root){
  if (root->izquerda && root->derecha){
    monticular(root->izquerda);
    monticular(root->derecha);
    if(root->izquerda->valor >= root->valor && root->derecha->valor <= root->izquerda->valor){
      swap(&root->valor, &root->izquerda->valor);
    }
    if(root->derecha->valor >= root->valor && root->izquerda->valor <= root->derecha->valor){
      swap(&root->valor, &root->derecha->valor);
    }
  }else{
    if(root->izquerda){
      if(root->izquerda->valor > root->valor)
	swap(&root->izquerda->valor, &root->valor);
      if(root->derecha->valor > root->valor)
	swap(&root->derecha->valor, &root->valor);
    }
  }
  return root;
}

heap* elimiarNHeap(heap* root, node** head){
  
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

//Función que devuelve el último valor de una lista enlazada
node *lastND(node *head) 
{ 
    while (head && head->siguiente) 
        head = head->siguiente; 
    return head; 
}

//Función que intercambia dos valores
void swap(double *A, double *B){ 
    double aux = *A; 
    *A = *B; 
    *B = aux; 
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
node *merge(node *first, node *second){ 
  node* head = NULL;
  node* aux = NULL;
  while(first && second){
    if (head)
      display(head);
    if(first->valor <= second->valor){
      if(aux){
	aux->siguiente = first;
	aux = aux->siguiente;
      }else{
	aux = first;
	head = aux;
      }
      first = first->siguiente;
      first->anterior = NULL;
      aux->siguiente = NULL;
      if(aux->valor == second->valor){
	aux->repeticiones++;
	second = second->siguiente;
      }
    }else{
      if(aux){
	aux->siguiente = second;
	aux = aux->siguiente;
      }else{
	aux = second;
	head = aux;
      }
      second = second->siguiente;
      second->anterior = NULL;
      aux->siguiente = NULL;
    } 
  }
  if(first){
    aux->siguiente = first;
    first->anterior = aux;
  }else{
    aux->siguiente = second;
    second->anterior = aux;
  }
  return head;
}

node *split(node *head){ 
  node *fast = head,*slow = head; //rápido avanza dos por cada uno que avanza el lento
  node *temp = NULL;//auxiliar
  while (fast->siguiente && fast->siguiente->siguiente){//Si existe el siguiente del rápido y el siguiente a éste 
    fast = fast->siguiente->siguiente;//Avanza dos con el rápido 
    slow = slow->siguiente; //Avanza uno con el lento
  } //A este punto el lento debe ir en la mitad mientras el otro al fin de la lista
  temp = slow->siguiente; //inicio de la segunda mitas
  slow->siguiente = NULL; //corte desde primera
  temp->anterior = NULL; //corte desde segunda
  return temp; 
} 



//Función que ordena por mezcla una lista
node *mergeSort(node *head){ 
  node* segundo = NULL; 
  if (!head || !head->siguiente) 
    return head; 
  segundo = split(head); 
  head = mergeSort(head);// Recurrencia para las mitades izquerda y derecha
  segundo = mergeSort(segundo); 
  return merge(head,segundo); // Mezcla las dos mitades ya ordenadas
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
	documento=fopen("ArchivoC.tex", "r");
	while(1 == fscanf(documento, "%le", &numero)){
	  head = instertND(head, numero);
	}
	fclose(documento);
	time1 = (clock() - time1) / CLOCKS_PER_SEC;
	printf("lectura de archivo: %.4lf \n", time1);
	time2 = clock();
	QuickSort(head);
	time2 = (clock() - time2) / CLOCKS_PER_SEC;
	printf("quick sort: %.4lf \n", time2);
	display(head);
	head = eliminarLista(head);
	return 0;
}
