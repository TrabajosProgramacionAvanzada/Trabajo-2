#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 //----------------------------------------------------------------------------------------------------------------//
 //----------------------------------------------------------------------------------------------------------------//
/*Merge Sort para ordenar listas de gran tamalo
Variables ocupadas NodeM, que contiene valor, repeticion y siguiente de la lista
*/


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

//Funcion para imprimir en pantalla

void displayM(nodeM* head){
  int i = 1;
  while (head != NULL) { 
    printf("%le - %d \n", head->valor, i);
    head = head->siguiente;
    i++;
  }
  return;
} 

//funcion para eliminar espacio de memoria

nodeM* eliminarListaM(nodeM* head){
  nodeM* aux = head;
  while(head){
    head = head->siguiente;
    free(aux);
    aux = head;
  }
  return head;
}

//valor de corte de la lista, para poder dividir lista en mitades

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

//Funcion para recorrer la lista

nodeM* recorrerLista(nodeM* head){
	nodeM* aux = head;
	while(head && aux->siguiente){
		aux = aux->siguiente;
	}
	return aux;
}

//Funcion que ordena las mitades de la listas que se obtiene  de una lista grande

nodeM* merge_sorted(nodeM* A, nodeM* B){
	nodeM* auxA = A;
	nodeM* auxB = B;
	nodeM* head = NULL;
	nodeM* aux = NULL;
	nodeM* elim = NULL;
	if(A && B){//Si hay ambas listas para ordenar
		while(auxA && auxB){
			//printf("\nwhile\n");
            //si lista A es menor a B    
			if(auxA->valor < auxB->valor){
			//printf("\n<\n");
				if(!head){
                    //Si, no hay cabeza en la lista se actualiza la cabeza y se avanza al siguiente
					head = aux = auxA;
					auxA = auxA->siguiente;
					aux->siguiente = NULL;
				}
				else{
                    //sino, se avanza por la lista A y se actualiaza la variable auxiliar 
					aux->siguiente = auxA;
					auxA = auxA->siguiente;
					aux = aux->siguiente;
				}
            //si el valor de la primera lista es mayor que el segundo   
			}else if(auxA->valor > auxB->valor){
			//printf("\n>\n");
                //Si, no hay cabeza se actualiza esta con el valor de la lista B y se avanza con Z
				if(!head){
					head = aux = auxB;
					auxB = auxB->siguiente;
					aux->siguiente = NULL;
				}
				else{
                    //sino, se avanza en la lista B y se actualizan los valores auxiliares
					aux->siguiente = auxB;
					auxB = auxB->siguiente;
					aux = aux->siguiente;
				}
			}else{
			//printf("\n=\n");
                //Si, no existe cabeza, entonces se avanza con A y el siguiente, también con la lista B
				if(!head){
					head = aux = auxA;
					auxA = auxA->siguiente;
					elim = auxB;
					elim->siguiente = NULL;
					auxB = auxB->siguiente;
					aux->siguiente = NULL;
				}
				else{
                    //sino se avanza con las dos listas y se actualiza un contador que se va guardando en cada lista, si los valores son iguales
					aux->siguiente = auxA;
					auxA = auxA->siguiente;
					elim = auxB;
					auxB = auxB->siguiente;
					aux = aux->siguiente;
					aux->repeticion++;
				}
                //liberar memoria
				free(elim);
			}
		}
        //Si existe solo A desde un principio
		if(auxA){
			//printf("\nqueda A\n");
            //si existe el auxiliar y la cabeza, se actualiza en valor auxiliar por la cabeza 
			if(aux && head)
				aux->siguiente = auxA;
            //Sino se actualiza la cabeza con la lista A    
			else
				head = auxA;
        //Tambien se considera lo mismo para la lista en B        
		}else if(auxB){
			//printf("\nqueda B\n");
			if(aux && head)
				aux->siguiente = auxB;
			else
				head = auxB;
		}
    //si existe solo A, se retorna A    
	}else if (A){
			//printf("\nB NULL\n");
		return A;
    //Sino se retorna B    
	}else{
			//printf("\nA NULL\n");
		return B;
		}
    //se retorna la cabeza actualizada

	return head;
}

//Funcion Merge Sort

nodeM* mergeSort(nodeM* head){
    //se divide la lista
	nodeM* mitad = splitM(head);;//caso base es el penúltimo
	nodeM* aux1 = NULL;
	nodeM* aux2 = NULL;
	nodeM *sorted = NULL;
    //si existen ambas
	if(head && mitad){
        //se realiza la recursion para las mitades
		aux1 = mergeSort(mitad);
		aux2 = mergeSort(head);
        //Se dividen y ordenan las dos listas
		sorted = merge_sorted(aux1, aux2);
		return sorted;	
	}else if(head)
		return head;
	else
		return mitad;
	return NULL;
}



//--------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------//

/*
QuickSort, que contiene una estructura con el valor, la repetición y las conexiones
que hay en el anterios y el siguiente de la lista enlazada.

*/


//Estructura de la lista doblemente enlazada
typedef struct NodeDH{
  double valor;
  unsigned long long int repeticiones;
  struct NodeDH* siguiente;
  struct NodeDH* anterior;
} nodeDH;

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

//Función que inserta un valor al inicio una lista como una pila
node* instertND(node* head, double n){
  node* new = initNodeD(new);
  new->valor = n;
  node* aux = head;
  new->siguiente = head;
  if(head != NULL)
    head->anterior = new;
  return new;
}

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

//Función que inserta un valor al inicio una lista
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

//funcion que elimina lista con el fin de liberar memoria mediante un free
nodeDH* eliminarListaDH(nodeDH* head){
  nodeDH* aux = head;
  while(head){
    head = head->siguiente;
    free(aux);
    aux = head;
  }
  return head;
}

//Función que intercambia dos valores
void swap(double *A, double *B){ 
    double aux = *A; 
    *A = *B; 
    *B = aux; 
}

//funcion que muestra en pantalla mediante un ciclo

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

//Funcion QuickSort generazlizado con el paso inductivo

void QuickSort(node *head){ 
    node *aux = lastND(head);//encuentra el último nodo 
    quickSortI(head, aux); //llama a la función recurrsiva de Quick Sort
    return;
}

//Eliminar lista y Dividirla en dos


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

//-----------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------//

/*
AVL en su estrutura de datos contiene los valores a operar, la altura y la repetición de estos numers
a su vez contiene los valores que existen por la izquierda y la derecha.
*/

// Estructura para el nodo del AVL
typedef struct nodeAVL {
  double valor;
  struct nodeAVL *izquerda;
  struct nodeAVL *derecha;
  int altura;
  long long int repeticiones;
} nodeAVL;

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
nodeAVL *minValuenodeAVL(nodeAVL *nodeAVL) {
  nodeAVL *current = nodeAVL;
  while (current->izquerda != NULL) //Hasta que no haya un nodo menor a la raíz
    current = current->izquerda;//Se avanza
  return current;
}

// Función que elimina un valor de un AVL
nodeAVL *deletenodeAVL(nodeAVL *root, double valo) {
  nodeAVL *temp = NULL;
  nodeAVL *temp = NULL;
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
    printf("%d ", root->valor);
    inOrder(root->derecha); 
  }
}

//----------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------//

/*
HeapSort o Monticulo, donde existen dos estructuras definidas, una es para el arbol, donde tiene 
el fin de monticular y organizar en una lista

Para Arbol: Valor, Repeticion y direcciones (izquierda y Derecha)
Para la lista enlazada: Valor, Repeticion y direcciones (siguiente y anterior)

*/

//Estructura del heap tipo arbol
typedef struct NodeHeap{
  double valor; //Clave del nodo
  unsigned long long int repeticiones; //Veces que se repite la clave
  int bal; //Balance
  struct NodeHeap *izquerda;
  struct NodeHeap *derecha;
} heap;


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

//Función que inserta un valor al inicio una lista
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

//Funcion que elimina lista den que se van guardando los valores del arbol
nodeDH* eliminarListaDH(nodeDH* head){
  nodeDH* aux = head;
  while(head){
    head = head->siguiente;
    free(aux);
    aux = head;
  }
  return head;
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

//Insertar valores ordenados en el arbol

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

//Funcion para pasos inductivos de monticular

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

//funcion Monticulo para incertar en la lista, cada vez que se vaya eliminado un valor
nodeHeap* to_heap(nodeHeap* root){
  if(!root)
    return root;
  else 
    return to_heap_1(root);
}


// Función que elimina un valor de un AVL, y guarda en el inicio de una lista de arreglo el arbol
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

//----------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------//

/*

Trabajo de operaciones que obtendremos de las listas

*/

//Funciones para AVL de maximos, minimos y medidas de estadistica

//valor maximo
nodeAVL *maxvalorAVL(nodeAVL *nodeAVL){

    if(nodeAVL==NULL){
        return (nodeAVL-> valor);

    }

    double res = nodeAVL -> valor;
    double izqres = maxvalorAVL(nodeAVL -> izquerda);
    double derres = maxvalorAVL(nodeAVL -> derecha);
    if(izqres > res){
        res = izqres;
    }
    if(derres > res){
        res = derres;
    }
    return res;

}

//Valor minimo 

void minvalorAVL(nodeAVL *nodeAVL){

    nodeAVL *aux=NULL;
    aux=minValuenodeAVL(nodeAVL);
    return aux;
}

//cuartiles

void cuartiles(nodeAVL *nodeAVL, double cuartilesdato[4]){
    int i=0;
    if(nodeAVL==NULL){
        printf("No hay sufiecnetes datos")
    }
    else{
        if(nodeAVL -> altura == 4){
            cuartiles[i]=nodeAVL ->valor;
        }
        else
            cuartiles(nodeAVL ->izquerda, cuartilesdato[i+1]);
        cuartiles(nodeAVL -> derecha, cuartiles[i+1]);    
    }
}


// Funciones para listas de maximos, minimos y medidas de estadisitica



int main(){

  double time1 = 0.0;
	double time2 = 0.0;
	double numero;

	char c = '\0';

	nodeM* head1 = NULL;
  nodeDH* head2 = NULL;
  nodeAVL* nodeAVL = NULL;
  NodeHeap = NULL;
  int opcion;

	FILE* documento;

  //Menu dentro del intmain


  do{
    
    switch (opcion)
    {
    case 1:
      printf(" ORDENAR UTILIZANDO MERGE SORT");
      printf("\n");
      documento=fopen("ArchivoA.tex", "r");
	    while(1 == fscanf(documento, "%le", &numero)){
	        head1 = instertM(head1, numero);
      }
      fclose(documento);
      mergeSort(head1);
      head1=eliminarListaM(head1);
      break;

    case 2:
      printf(" ORDENAR UTILIZANDO QUICKSORT ");
      printf("\n");
      documento=fopen("ArchivoA.tex", "r");
	    while(1 == fscanf(documento, "%le", &numero)){
	        head2 = instertND(head2, numero);
      }
      fclose(documento);

      break;

    
    default:
      break;
    }

  }while(opcion!=5);


	
  return 0;
  
}