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

// Estructura para el nodo del AVL
typedef struct nodeHeap {
  double valor;
  struct nodeHeap *izquerda;
  struct nodeHeap *derecha;
  int altura;
  long long int repeticiones;
} nodeHeap;

//Estructura de la lista enlazada
typedef struct NodeDH{
  double valor;
  unsigned long long int repeticiones;
  struct NodeDH* siguiente;
  struct NodeDH* anterior;
} nodeDH;

//Función que inicializa un nodo vacío
nodeDH* initNodeDH(nodeDH *head){
  nodeDH* nodo = malloc(sizeof(nodeDH));
  nodo->valor = 0.0;
  nodo->repeticiones = 0;
  nodo->siguiente = NULL;
  nodo->anterior = NULL;
  head = nodo;
  return head;
}

//Función que insera un valor al inicio una lista
nodeDH* instertNDH(nodeDH* head, double n){
  if(head && head->valor == n){
    head->repeticiones++;
    return head;
  }
  nodeDH* new = initNodeDH(new);
  new->valor = n;
  nodeDH* aux = head;
  new->siguiente = head;
  if(head != NULL)
    head->anterior = new;
  return new;
}

nodeDH* eliminarListaDH(nodeDH* head){
  nodeDH* aux = head;
  while(head){
    head = head->siguiente;
    free(aux);
    aux = head;
  }
  return head;
}

// Función que retorna la alturaHeap de un árbol
int alturaHeap(nodeHeap *N) {
  if (N == NULL)
    return 0;
  return N->altura;
}


//Función que intercambia dos valores
void swap(double *A, double *B){ 
    double aux = *A; 
    *A = *B; 
    *B = aux; 
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


// Función que retorna la altura de un árbol
int altura(nodeAVL *N) {
  if (N == NULL)
    return 0;
  return N->altura;
}

// Función que retorna el mayor entre dos double
double max(double a, double b) { return (a > b) ? a : b; }


int max_comp(double a, double b){
  return (a < b) ? -1 : (a == b) ? 0 : 1; 
}

// Función que inicializa un nuevo nodo AVL
nodeHeap *newnodeHeap(double valor) {
  nodeHeap *nodo = (nodeHeap *)malloc(sizeof(nodeHeap));
  nodo->valor = valor;
  nodo->izquerda = NULL;
  nodo->derecha = NULL;
  nodo->altura = 1;
  nodo->repeticiones = 0;
  return (nodo);
}


// Función que retorna el balance de la raíz
int getBalanceHeap(nodeHeap *N) {
  if (N == NULL)
    return 0;
  return alturaHeap(N->izquerda) - alturaHeap(N->derecha);
}

nodeHeap *insertHeap(nodeHeap *nodo, double valor) {
  int balance = 0;
  balance = getBalanceHeap(nodo);//Pide el balance para resolver según tres casos
  if (nodo == NULL)//Si no hay nodo
    return (newnodeHeap(valor));//Se inserta el nuevo nodo
  if (balance <= 0)//Si el valor es menor que el de la raíz
    nodo->izquerda = insertHeap(nodo->izquerda, valor);//Se continúa insertando recursivamente hacia la izquerda
  else  //de lo contrario, si es mayor
    nodo->derecha = insertHeap(nodo->derecha, valor);//Se actúa reciprocamente hacia la derecha
  nodo->altura = 1 + max(alturaHeap(nodo->izquerda), alturaHeap(nodo->derecha));//Se actualiza la altira después de la insersión
  return nodo;
}

nodeHeap* to_heap_1(nodeHeap* root){
  if(root->izquerda && root->derecha){
    if(max_comp(root->valor, root->derecha->valor) < 0 && max_comp(root->valor, root->izquerda->valor) < 0){
      if(max_comp(root->izquerda->valor, root->derecha->valor) <= 0)
        swap(&root->valor, &root->derecha->valor);
      else
        swap(&root->valor, &root->izquerda->valor);
    }else if(max_comp(root->valor, root->derecha->valor) < 0)
      swap(&root->valor, &root->derecha->valor);
    else 
      swap(&root->valor, &root->izquerda->valor);
  }else if (root->izquerda){
    if (max_comp(root->valor, root->izquerda->valor) < 0)
      swap(&root->valor, &root->izquerda->valor);
  }else if (root->derecha){
    if(max_comp(root->valor, root->derecha->valor) < 0)
      swap(&root->valor, &root->derecha->valor);
  }
  return root;
}

nodeHeap* to_heap(nodeHeap* root){
  if(!root)
    return root;
  else 
    return to_heap_1(root);
}


// Función que elimina un valor de un AVL
nodeHeap *deletenodeHeap(nodeHeap *root, nodeDH* head[1]) {
   int balance = 0;
  balance = getBalanceHeap(root);//Pide el balance para resolver según tres casos
  if (root->izquerda == NULL && root->derecha == NULL){//Si no hay nodos siguientes
    head[0] = instertNDH(head[0], root->valor);
    free(root);
    return NULL;//Se inserta el nuevo nodo
  }else if (balance <= 0){//Si el valor es menor que el de la raíz
    if(root->derecha){
      swap(&root->valor, &root->derecha->valor);
      root->derecha = deletenodeHeap(root->derecha, head);//Se continúa insertando recursivamente hacia la izquerda
      root->izquerda = to_heap(root->izquerda);
      root = to_heap_1(root);
    }else{
      swap(&root->valor, &root->izquerda->valor);
      root->izquerda = deletenodeHeap(root->izquerda, head);//Se continúa insertando recursivamente hacia la izquerda
      root->derecha = to_heap(root->derecha);
      root = to_heap_1(root);
    }
  }else{  //de lo contrario, si es mayorif(root->derecha){
    if(root->derecha){
      swap(&root->valor, &root->derecha->valor);
      root->derecha = deletenodeHeap(root->derecha, head);//Se continúa insertando recursivamente hacia la izquerda
      root->izquerda = to_heap(root->izquerda);
      root = to_heap_1(root);
    }else{
      swap(&root->valor, &root->izquerda->valor);
      root->izquerda = deletenodeHeap(root->izquerda, head);//Se continúa insertando recursivamente hacia la izquerda
      root->derecha = to_heap(root->derecha);
      root = to_heap_1(root);
    }
  }
  root->altura = 1 + max(alturaHeap(root->izquerda), alturaHeap(root->derecha));//Se actualiza la altira después de la insersión
  return root;
}


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
	nodeHeap* root = NULL;
	nodeDH* aux = NULL;
	node* aux1 = NULL;
	FILE* documento;
	time1 = clock();
	documento=fopen("ArchivoA.tex", "r");
	while(1 == fscanf(documento, "%le", &numero)){
	  root = insertHeap(root, numero);
	}
	fclose(documento);
	time1 = (clock() - time1) / CLOCKS_PER_SEC;
	printf("lectura de archivo: %.4lf \n", time1);
	time1 = clock();
	//aux1 = mergeSort(aux);
	time1 = (clock() - time1) / CLOCKS_PER_SEC;
	printf("merge sort: %.4lf \n", time1);
	//scanf("%c", c);
	//inOrder(root);
	//root = eliminarLista(root);
	//aux = eliminarLista(aux);
	return 0;
}
