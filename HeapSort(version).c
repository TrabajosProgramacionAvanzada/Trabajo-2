#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estructura para el nodo del AVL
typedef struct nodeHeap {
  double valor;
  struct nodeHeap *izquerda;
  struct nodeHeap *derecha;
  int altura;
  long long int repeticiones;
} nodeHeap;

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
  if(head && head->valor == n){
    head->repeticiones++;
    return head;
  }
  node* new = initNodeD(new);
  new->valor = n;
  node* aux = head;
  new->siguiente = head;
  if(head != NULL)
    head->anterior = new;
  return new;
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

// Función que retorna la altura de un árbol
int altura(nodeHeap *N) {
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

// Función que retorna el mayor entre dos double o 0 si son iguales
double max(double a, double b) {   return (a > b) ? a : b; }

int max_comp(double a, double b){
  return (a < b) ? -1 : (a == b) ? 0 : 1; 
}

// Función que inicializa un nuevo nodo AVL
nodeHeap *newnodeHeap(double valor) {
  nodeHeap *node = (nodeHeap *)malloc(sizeof(nodeHeap));
  node->valor = valor;
  node->izquerda = NULL;
  node->derecha = NULL;
  node->altura = 1;
  node->repeticiones = 0;
  return (node);
}


// Función que retorna el balance de la raíz
int getBalance(nodeHeap *N) {
  if (N == NULL)
    return 0;
  return altura(N->izquerda) - altura(N->derecha);
}

nodeHeap *insertHeap(nodeHeap *node, double valor) {
  int balance = 0;
  balance = getBalance(node);//Pide el balance para resolver según tres casos
  if (node == NULL)//Si no hay nodo
    return (newnodeHeap(valor));//Se inserta el nuevo nodo
  if (balance <= 0)//Si el valor es menor que el de la raíz
    node->izquerda = insertHeap(node->izquerda, valor);//Se continúa insertando recursivamente hacia la izquerda
  else  //de lo contrario, si es mayor
    node->derecha = insertHeap(node->derecha, valor);//Se actúa reciprocamente hacia la derecha
  node->altura = 1 + max(altura(node->izquerda), altura(node->derecha));//Se actualiza la altira después de la insersión
  return node;
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
nodeHeap *deletenodeHeap(nodeHeap *root, node* head[1]) {
   int balance = 0;
  balance = getBalance(root);//Pide el balance para resolver según tres casos
  if (root->izquerda == NULL && root->derecha == NULL){//Si no hay nodos siguientes
    head[0] = instertND(head[0], root->valor);
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
  root->altura = 1 + max(altura(root->izquerda), altura(root->derecha));//Se actualiza la altira después de la insersión
  return root;
}

//Función que imprime en pantalla el árbol en inorder
void inOrder(nodeHeap *root) {
  if (root != NULL) {
    inOrder(root->izquerda);
    printf("%le ", root->valor);
    inOrder(root->derecha); 
  }
}

int main() {
  nodeHeap *root = NULL;
  node* lista[1] = { NULL};
  node* aux = NULL;
  double time1 = 0.0;
  double numero = 0.0;
  int i = 1;
  FILE* documento;
	time1 = clock();
	documento=fopen("ArchivoA.tex", "r");
	while(1 == fscanf(documento, "%le", &numero)){
	  root = insertHeap(root, numero);
	  //printf("%le\n", numero);
	}
	fclose(documento);
	time1 = (clock() - time1) / CLOCKS_PER_SEC;
	printf("lectura de archivo: %.4lf \n", time1);
	time1 = clock();
	root = to_heap(root);
  while (root){
    root = deletenodeHeap(root, lista);
    //printf("ordenando... ultimo valor: %le\n", lista[0]->valor);
  }
  time1 = (clock() - time1) / CLOCKS_PER_SEC;
	printf("heap sort: %.4lf \n", time1);
  printf("Pulse cualquier tecla para continuar...\n");
  getchar();
  printf("\nlista ya ordenada: \n");
  aux = lista[0];
  while (aux){
    printf("%le - %d\n", aux->valor, i);
    aux = aux->siguiente;
    i++;
  }
  lista[0] = eliminarLista(lista[0]);
  return 0;
}
