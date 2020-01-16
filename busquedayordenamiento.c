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

typedef struct nodeAVL {
  double valor;
  struct nodeAVL *izquerda;
  struct nodeAVL *derecha;
  int altura;
  long long int repeticiones;
} nodeAVL;


//Estructura del heap
typedef struct NodeHeap{
  double valor; //Clave del nodo
  unsigned long long int repeticiones; //Veces que se repite la clave
  int bal; //Balance
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
  root = nodo;
  return root;
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
  }
  return root;
}


//Función que intercambia dos valores
void swap(double *A, double *B){ 
    double aux = *A; 
    *A = *B; 
    *B = aux; 
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

heap* eliminarNHeap(heap* root, node** head){
  if(root->izquerda == NULL || root->derecha == NULL){
    if(root->izquerda == NULL && root->derecha == NULL){
      *head = instertND(*head, root->valor);
      free(root);
    }
    if(root->izquerda){
      swap(&root->valor, &root->izquerda->valor);
      root->izquerda = eliminarNHeap(root->izquerda, head);
    }
    if(root->derecha){
      swap(&root->valor, &root->derecha->valor);
      root->derecha = eliminarNHeap(root->derecha, head);
    }
    return root;
  }else{
    if(root->derecha->bal - root->izquerda->bal <= 0){
      swap(&root->derecha->valor, &root->valor);
      root->derecha=eliminarNHeap(root->derecha, head);
      root->izquerda=monticular(root->izquerda);
    }else{
      swap(&root->izquerda->valor, &root->valor);
      root->izquerda=eliminarNHeap(root->izquerda, head);
      root->derecha=monticular(root->derecha);
    }
    if(root->izquerda==NULL && root->derecha!=NULL){
      if(root->valor<root->derecha->valor){
	swap(&root->derecha->valor, &root->valor);
      }
    }else if(root->izquerda!=NULL && root->derecha==NULL){
      if(root->valor<root->izquerda->valor){
	swap(&root->izquerda->valor, &root->valor);
      }
    }else{
      if(root->valor <= root->derecha->valor && root->izquerda->valor <= root->derecha->valor){
	swap(&root->derecha->valor, &root->valor);
      }else if(root->valor <= root->izquerda->valor && root->derecha->valor <= root->izquerda->valor){
	swap(&root->izquerda->valor, &root->valor);
      }
    }
  }
  return root;
}

heap* ordenarHeap(heap* root,node** head){
  while(root){
    root = eliminarNHeap(root, head);
  }
  return NULL;
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
node *merge(node *A, node *B){ 
  node* head = NULL;
  node* aux = NULL;
  node* aux2 = NULL;
  while(A && B){//Mientras existan ambas listas
    if(head){//Si existe la cabeza de la lista ya ordenada
      if(A->valor <= B->valor){//Si el valor de A es menor o igual al de B
	if(A->valor == B->valor){//En específico, si es igual
	  aux2 = B;//Se copia B para ser eliminado
	  B = B->siguiente;//Se avanza en B
	  free(aux2);//Se elimina
	  aux2 = A->siguiente;//Se copia el siguiente de A
	  A->siguiente = NULL;//Se corta de la lista
	  aux->siguiente = A;//Se conecta con el final de la lista
	  A->anterior = aux;//Se conecta el final de la lista con A
	  A->repeticiones++;//Se incrementa el contador de repeticiones
	  aux = A;//se avanza en la lista ordenada
	  A = aux2;//Se avanza en A
	}else{//De lo contrario, es menor
	  aux2 = A->siguiente;//copia siguiente
	  A->siguiente = NULL;//corta A
	  if (aux2)//Si existe el siguiente
	    aux2->anterior = NULL;//Se corta la lista de A
	  aux->siguiente = A;//enlaza con A
	  A->anterior = aux;//enlaza con lista
	  aux = A;//Se avanza en lista ordenada
	  A = aux2;//Se avanza en A
	}
      }else{//Análogamente en B se pasa a la lista ordenada y avanza
	aux2 = B->siguiente;
	B->siguiente = NULL;
	if (aux2)//Si existe el siguiente
	  aux2->anterior = NULL;//Se corta la lista de B
	aux->siguiente = B;
	B->anterior = aux;
	aux = B;
	B = aux2;
      }
    }else{//De lo contrario es la primera iteración
      if(A->valor <= B->valor){//Se realiza todo casi igual
	if(A->valor == B->valor){
	  aux2 = B;
	  B = B->siguiente;
	  free(aux2);
	  head = aux = A;//A excepción de que se iguala la cabeza y el auxiliar para recorrer la nueva lista ordenada a A
	  aux2 = A->siguiente;
	  A->siguiente = NULL;
	  if (aux2)
	    aux2->anterior = NULL;
	  A->repeticiones++;
	  A = aux2;
	}else{
	  head = aux = A;
	  aux2 = A->siguiente;
	  if (aux2)
	    aux2->anterior = NULL;
	  A = aux2;
	}
      }else{
	head = aux = B;
	aux2 = B->siguiente;
	B->siguiente = NULL;
	if (aux2)
	  aux2->anterior = NULL;
	B = B->siguiente;
      }
    }
  }
  if(A){
    if(head){
      aux->siguiente = A;
      A->anterior = aux;
    }else{
      return A;
    }
  }else if(B){
    if(head){
      aux->siguiente = B;
      B->anterior = aux;
    }else{
      return B;
    }
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



//Función que ordena por mezcla una lista
node *mergeSort(node *head){ 
  node* segundo = NULL; 
  if (!head || !head->siguiente){ 
    return head; 
  }else{
    segundo = split(head); 
    head = mergeSort(head);// Recurrencia para las mitades izquerda y derecha
    segundo = mergeSort(segundo); 
  }
  return merge(head,segundo); // Mezcla las dos mitades ya ordenadas
} 

// Función que retorna la altura de un árbol
int altura(nodeAVL *N) {
  if (N == NULL)
    return 0;
  return N->altura;
}

// Función que retorna el mayor entre dos double
double max(double a, double b) { return (a > b) ? a : b; }

// Función que inicializa un nuevo nodo AVL
nodeAVL *newnodeAVL(double valor) {
  nodeAVL *node = (nodeAVL *)malloc(sizeof(nodeAVL));
  node->valor = valor;
  node->izquerda = NULL;
  node->derecha = NULL;
  node->altura = 1;
  node->repeticiones = 0;
  return (node);
}

//Función que ejecuta una rotación hacia la derecha en AVL
nodeAVL *derechaRotate(nodeAVL *y) {
  nodeAVL *x = y->izquerda;
  nodeAVL *T2 = x->derecha;
  x->derecha = y;//Rotación
  y->izquerda = T2;
  y->altura = max(altura(y->izquerda), altura(y->derecha)) + 1;//Actualiza las alturas
  x->altura = max(altura(x->izquerda), altura(x->derecha)) + 1;
  return x;
}

//Función que ejecuta una rotación hacia la izquerda en AVL
nodeAVL *izquerdaRotate(nodeAVL *x) {
  nodeAVL *y = x->derecha;
  nodeAVL *T2 = y->izquerda;
  y->izquerda = x;//Rotación izquerda
  x->derecha = T2;
  x->altura = max(altura(x->izquerda), altura(x->derecha)) + 1;//Actualiza las alturas
  y->altura = max(altura(y->izquerda), altura(y->derecha)) + 1;
  return y;
}

// Función que retorna el balance de la raíz
int getBalance(nodeAVL *N) {
  if (N == NULL)
    return 0;
  return altura(N->izquerda) - altura(N->derecha);
}

nodeAVL *insert(nodeAVL *nodeAVL, double valor) {
  double balance = 0;
  if (nodeAVL == NULL)//Si no hay nodo
    return (newnodeAVL(valor));//Se inserta el nuevo nodo
  if (valor < nodeAVL->valor)//Si el valor es menor que el de la raíz
    nodeAVL->izquerda = insert(nodeAVL->izquerda, valor);//Se continúa insertando recursivamente hacia la izquerda
  else if (valor > nodeAVL->valor)//de lo contrario, si es mayor
    nodeAVL->derecha = insert(nodeAVL->derecha, valor);//Se actúa reciprocamente hacia la derecha
  else{ //Si son iguales
    nodeAVL->repeticiones++;//Se incrementa el contador de sus repeticiones (servirá al buscar el nodo más repetido en O(n) )
    return nodeAVL;
  }
  nodeAVL->altura = 1 + max(altura(nodeAVL->izquerda), altura(nodeAVL->derecha));//Se actualiza la altira después de la insersión
  balance = getBalance(nodeAVL);//Pide el balance para resolver según cuatro casos
  if (balance > 1 && valor < nodeAVL->izquerda->valor)//Caso izquerda izquerda
    return derechaRotate(nodeAVL);
  if (balance < -1 && valor > nodeAVL->derecha->valor)//Caso derecha derecha
    return izquerdaRotate(nodeAVL);
  if (balance > 1 && valor > nodeAVL->izquerda->valor) {//Caso izquerda derecha
    nodeAVL->izquerda = izquerdaRotate(nodeAVL->izquerda);
    return derechaRotate(nodeAVL);
  }
  if (balance < -1 && valor < nodeAVL->derecha->valor) {//Caso derecha izquerda
    nodeAVL->derecha = derechaRotate(nodeAVL->derecha);
    return izquerdaRotate(nodeAVL);
  }
  return nodeAVL;
}

//Función que retorna el valor mínimo del árbol
nodeAVL *minValuenodeAVL(nodeAVL *node) {
  nodeAVL* aux = node;
  while (aux->izquerda != NULL) //Hasta que no haya un nodo menor a la raíz
    aux = aux->izquerda;//Se avanza
  return aux;
}

// Función que elimina un valor de un AVL
nodeAVL *deletenodeAVL(nodeAVL *root, double valor) {
  nodeAVL *temp = NULL;
  nodeAVL *temp2 = NULL;
  int balance = 0;
  if (root == NULL)//Si la cabeza está vacía (caso báse)
    return root;
  if (valor < root->valor)//Si el valor a eliminar es menor al de la raíz
    root->izquerda = deletenodeAVL(root->izquerda, valor);//Se continúa buscando por la izquerda
  else if (valor > root->valor)//De lo contrario, si es mayor
    root->derecha = deletenodeAVL(root->derecha, valor);//Se continúa por la derecha
  else {//De lo contrario se encontró el nodo a eliminar
    if ((root->izquerda == NULL) || (root->derecha == NULL)) {//Caso si sólo tiene un hijo
      temp = root->izquerda ? root->izquerda : root->derecha;
      if (temp == NULL) {//Caso sin hijos
        temp = root;
        root = NULL;
      } else  //Caso con un hijo 
        *root = *temp;
      free(temp);
    } else {//Caso con dos hijos
      temp = minValuenodeAVL(root->derecha);//Se busca el elemento menor de la parte meyor
      root->valor = temp->valor;//Copia ese valor en la raíz
      root->derecha = deletenodeAVL(root->derecha, temp->valor);//Elimina el valor previamente copiado de las hojas menores de la derecha
    }
  }
  if (root == NULL)//Si está vacío retorna
    return root;
  root->altura = 1 + max(altura(root->izquerda), altura(root->derecha));//Actualiza la altura del nodo
  balance = getBalance(root);//Pide el balance del nodo y realiza uno de los 4 casos al igual que la incesrsión 
  if (balance > 1 && getBalance(root->izquerda) >= 0)// izquerda izquerda
    return derechaRotate(root);
  if (balance > 1 && getBalance(root->izquerda) < 0) {// izquerda derecha
    root->izquerda = izquerdaRotate(root->izquerda);
    return derechaRotate(root);
  }
  if (balance < -1 && getBalance(root->derecha) <= 0)// derecha derecha
    return izquerdaRotate(root);
  if (balance < -1 && getBalance(root->derecha) > 0) {// derecha izquerda
    root->derecha = derechaRotate(root->derecha);
    return izquerdaRotate(root);
  }

  return root;
}

//Función que imprime en pantalla el árbol en inorder
void inOrder(nodeAVL *root) {
  if (root != NULL) {
    inOrder(root->izquerda);
    printf("%le \n", root->valor);
    inOrder(root->derecha); 
  }
}  

int main(){	
	double time1 = 0.0;
	double time2 = 0.0;
	double numero;
	char c = '\0';
	nodeAVL* root = NULL;
	node* aux = NULL;
	FILE* documento;
	time1 = clock();
	documento=fopen("ArchivoC.tex", "r");
	while(fscanf(documento, "%le", &numero)){
	  root = insert(root, numero);
	}
	fclose(documento);
	time1 = (clock() - time1) / CLOCKS_PER_SEC;
	printf("lectura de archivo: %.4lf \n", time1);
	//printf("merge sort: %.4lf \n", time2);
	//scanf("%c", c);
	//inOrder(root);
	//root = eliminarLista(root);
	//aux = eliminarLista(aux);
	return 0;
}
