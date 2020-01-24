
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

//FunciÃ³n que inicializa un nodo vacÃ­o
nodeM* initNodeM(nodeM *head){
  nodeM* nodo = malloc(sizeof(nodeM));
  nodo->valor = 0.0;
  nodo->repeticion = 0;
  nodo->siguiente = NULL;
  head = nodo;
  return head;
}

//FunciÃ³n que insera un valor al inicio una lista
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
	nodeM *rapido = head,*lento = head; //rÃ¡pido avanza dos por cada uno que avanza el lento
	nodeM *aux = NULL;//auxiliar
	if(head){
		while (rapido->siguiente && rapido->siguiente->siguiente){//Si existe el siguiente del rÃ¡pido y el siguiente a Ã©ste 
		rapido = rapido->siguiente->siguiente;//Avanza dos con el rÃ¡pido 
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
                //Si, no existe cabeza, entonces se avanza con A y el siguiente, tambiÃ©n con la lista B
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
	nodeM* mitad = splitM(head);;//caso base es el penÃºltimo
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
QuickSort, que contiene una estructura con el valor, la repeticiÃ³n y las conexiones
que hay en el anterios y el siguiente de la lista enlazada.
*/


//Estructura de la lista doblemente enlazada
typedef struct NodeDH{
  double valor;
  unsigned long long int repeticiones;
  struct NodeDH* siguiente;
  struct NodeDH* anterior;
} nodeDH;

//FunciÃ³n que inicializa un nodo vacÃ­o
nodeDH* initNodeD(nodeDH *head){
  nodeDH* nodo = malloc(sizeof(nodeDH));
  nodo->valor = 0.0;
  nodo->repeticiones = 0;
  nodo->siguiente = NULL;
  nodo->anterior = NULL;
  head = nodo;
  return head;
}

//FunciÃ³n que inserta un valor al inicio una lista como una pila
nodeDH* instertND(nodeDH* head, double n){
  nodeDH* new = initNodeD(new);
  new->valor = n;
  nodeDH* aux = head;
  new->siguiente = head;
  if(head != NULL)
    head->anterior = new;
  return new;
}

//FunciÃ³n que inicializa un nodo vacÃ­o
nodeDH* initNodeDH(nodeDH *head){
  nodeDH* nodo = malloc(sizeof(nodeDH));
  nodo->valor = 0.0;
  nodo->repeticiones = 0;
  nodo->siguiente = NULL;
  nodo->anterior = NULL;
  head = nodo;
  return head;
}

//FunciÃ³n que inserta un valor al inicio una lista
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

//FunciÃ³n que intercambia dos valores
void swap(double *A, double *B){ 
    double aux = *A; 
    *A = *B; 
    *B = aux; 
}

//funcion que muestra en pantalla mediante un ciclo

void display(nodeDH* head){
  int i = 1;
  while (head != NULL) { 
    printf("%le - %d \n", head->valor, i);
    head = head->siguiente;
    i++;
  }
  return;
} 

//FunciÃ³n que devuelve el Ãºltimo valor de una lista enlazada
nodeDH *lastND(nodeDH *head) 
{ 
    while (head && head->siguiente) 
        head = head->siguiente; 
    return head; 
}
 

/* Considerando el Ãºltimo elemento como pivote, se posicionan los elementos menores de un lado del pivote y los mayores al otro */
nodeDH* partition(nodeDH *l, nodeDH *h){ 
  double x = h->valor; //selecciona a h como pivote 
  nodeDH *i = l->anterior; //Centinela
  nodeDH *j = NULL;
  for (j = l; j != h; j = j->siguiente){ //recorremos la lista con j 
    if (j->valor <= x){ //si el valor actual es menor o igual al pivote
      i = (i == NULL) ? l : i->siguiente;//avanza 
      swap(&(i->valor), &(j->valor)); //intercambia los valores entre el valor lÃ­mite de i con el actual
    } 
  } 
  if(i == NULL){//Si no existe i
    i = l;//Se le asigna el elemento lÃ­mite (en Ã©ste caso el primer elemento)
  }else{
    i = i->siguiente;//De lo contrario pasa al siguiente
  }
  swap(&(i->valor), &(h->valor)); //intercambia valores entre el valor lÃ­mite con el pivote
  return i; 
} 

//Paso inductivo de Quick Sort
void quickSortI(nodeDH* lista, nodeDH *pivote){ 
  if (pivote != NULL && lista != pivote && lista != pivote->siguiente){//Si existe el pivote y es diferente al pivote y es diferente al que le sigue al pivote
    nodeDH *p = partition(lista, pivote); //Se realiza la particiÃ³n en torno al pivote
    quickSortI(lista, p->anterior);//Se ordena parcialmente un lado 
    quickSortI(p->siguiente, pivote); //ahora el otro
  }
  return;
} 

//Funcion QuickSort generazlizado con el paso inductivo

void QuickSort(nodeDH *head){ 
    nodeDH *aux = lastND(head);//encuentra el Ãºltimo nodo 
    quickSortI(head, aux); //llama a la funciÃ³n recurrsiva de Quick Sort
    return;
}

nodeDH *split(nodeDH *head){ 
  nodeDH *rapido = head,*lento = head; //rÃ¡pido avanza dos por cada uno que avanza el lento
  nodeDH *aux = NULL;//auxiliar
  while (rapido->siguiente && rapido->siguiente->siguiente){//Si existe el siguiente del rÃ¡pido y el siguiente a Ã©ste 
    rapido = rapido->siguiente->siguiente;//Avanza dos con el rÃ¡pido 
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
AVL en su estrutura de datos contiene los valores a operar, la altura y la repeticiÃ³n de estos numers
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

// FunciÃ³n que retorna la altura de un Ã¡rbol
int altura(nodeAVL *N) {
  if (N == NULL)
    return 0;
  return N->altura;
}

// FunciÃ³n que retorna el mayor entre dos double
double max(double a, double b) { return (a > b) ? a : b; }

// FunciÃ³n que inicializa un nuevo nodo AVL
nodeAVL *newnodeAVL(double valor) {
  nodeAVL *node = (nodeAVL *)malloc(sizeof(nodeAVL));
  node->valor = valor;
  node->izquerda = NULL;
  node->derecha = NULL;
  node->altura = 1;
  node->repeticiones = 0;
  return (node);
}

//FunciÃ³n que ejecuta una rotaciÃ³n hacia la derecha en AVL
nodeAVL *derechaRotate(nodeAVL *y) {
  nodeAVL *x = y->izquerda;
  nodeAVL *T2 = x->derecha;
  x->derecha = y;//RotaciÃ³n
  y->izquerda = T2;
  y->altura = max(altura(y->izquerda), altura(y->derecha)) + 1;//Actualiza las alturas
  x->altura = max(altura(x->izquerda), altura(x->derecha)) + 1;
  return x;
}

//FunciÃ³n que ejecuta una rotaciÃ³n hacia la izquerda en AVL
nodeAVL *izquerdaRotate(nodeAVL *x) {
  nodeAVL *y = x->derecha;
  nodeAVL *T2 = y->izquerda;
  y->izquerda = x;//RotaciÃ³n izquerda
  x->derecha = T2;
  x->altura = max(altura(x->izquerda), altura(x->derecha)) + 1;//Actualiza las alturas
  y->altura = max(altura(y->izquerda), altura(y->derecha)) + 1;
  return y;
}

// FunciÃ³n que retorna el balance de la raÃ­z
int getBalance(nodeAVL *N) {
  if (N == NULL)
    return 0;
  return altura(N->izquerda) - altura(N->derecha);
}

nodeAVL *insert(nodeAVL *nodeAVL, double valor) {
  double balance = 0;
  if (nodeAVL == NULL)//Si no hay nodo
    return (newnodeAVL(valor));//Se inserta el nuevo nodo
  if (valor < nodeAVL->valor)//Si el valor es menor que el de la raÃ­z
    nodeAVL->izquerda = insert(nodeAVL->izquerda, valor);//Se continÃºa insertando recursivamente hacia la izquerda
  else if (valor > nodeAVL->valor)//de lo contrario, si es mayor
    nodeAVL->derecha = insert(nodeAVL->derecha, valor);//Se actÃºa reciprocamente hacia la derecha
  else{ //Si son iguales
    nodeAVL->repeticiones++;//Se incrementa el contador de sus repeticiones (servirÃ¡ al buscar el nodo mÃ¡s repetido en O(n) )
    return nodeAVL;
  }
  nodeAVL->altura = 1 + max(altura(nodeAVL->izquerda), altura(nodeAVL->derecha));//Se actualiza la altira despuÃ©s de la insersiÃ³n
  balance = getBalance(nodeAVL);//Pide el balance para resolver segÃºn cuatro casos
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

//FunciÃ³n que retorna el valor mÃ­nimo del Ã¡rbol
nodeAVL *minValuenodeAVL(nodeAVL *root) {
  nodeAVL* current = root;
  while (current->izquerda != NULL) //Hasta que no haya un nodo menor a la raÃ­z
    current = current->izquerda;//Se avanza
  return current;
}

// FunciÃ³n que elimina un valor de un AVL
nodeAVL *deletenodeAVL(nodeAVL *root, double valor) {
  nodeAVL *temp = NULL;;
  int balance = 0;
  if (root == NULL)//Si la cabeza estÃ¡ vacÃ­a (caso bÃ¡se)
    return root;
  if (valor < root->valor)//Si el valor a eliminar es menor al de la raÃ­z
    root->izquerda = deletenodeAVL(root->izquerda, valor);//Se continÃºa buscando por la izquerda
  else if (valor > root->valor)//De lo contrario, si es mayor
    root->derecha = deletenodeAVL(root->derecha, valor);//Se continÃºa por la derecha
  else {//De lo contrario se encontrÃ³ el nodo a eliminar
    if ((root->izquerda == NULL) || (root->derecha == NULL)) {//Caso si sÃ³lo tiene un hijo
      temp = root->izquerda ? root->izquerda : root->derecha;
      if (temp == NULL) {//Caso sin hijos
        temp = root;
        root = NULL;
      } else  //Caso con un hijo 
        *root = *temp;
      free(temp);
    } else {//Caso con dos hijos
      temp = minValuenodeAVL(root->derecha);//Se busca el elemento menor de la parte meyor
      root->valor = temp->valor;//Copia ese valor en la raÃ­z
      root->derecha = deletenodeAVL(root->derecha, temp->valor);//Elimina el valor previamente copiado de las hojas menores de la derecha
    }
  }
  if (root == NULL)//Si estÃ¡ vacÃ­o retorna
    return root;
  root->altura = 1 + max(altura(root->izquerda), altura(root->derecha));//Actualiza la altura del nodo
  balance = getBalance(root);//Pide el balance del nodo y realiza uno de los 4 casos al igual que la incesrsiÃ³n 
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

//FunciÃ³n que imprime en pantalla el Ã¡rbol en inorder
void inOrder(nodeAVL *root) {
  if (root != NULL) {
    inOrder(root->izquerda);
    printf("%le ", root->valor);
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
  int altura; //Balance
  struct NodeHeap *izquerda;
  struct NodeHeap *derecha;
} nodeHeap;


// FunciÃ³n que inicializa un nuevo nodo AVL
nodeHeap *newnodeHeap(double valor) {
  nodeHeap *nodo = (nodeHeap *)malloc(sizeof(nodeHeap));
  nodo->valor = valor;
  nodo->izquerda = NULL;
  nodo->derecha = NULL;
  nodo->altura = 1;
  nodo->repeticiones = 0;
  return (nodo);
}

// FunciÃ³n que retorna el balance de la raÃ­z
int getBalanceHeap(nodeHeap *N) {
  if (N == NULL)
    return 0;
  return getBalanceHeap(N->izquerda) - getBalanceHeap(N->derecha);
}

//Funci´´on que indica cuál número es mayor
int max_comp(double a, double b){
  return (a < b) ? -1 : (a == b) ? 0 : 1; 
}

//Insertar valores ordenados en el arbol

nodeHeap *insertHeap(nodeHeap *nodo, double valor) {
  int balance = 0;
  balance = getBalanceHeap(nodo);//Pide el balance para resolver segÃºn tres casos
  if (nodo == NULL)//Si no hay nodo
    return (newnodeHeap(valor));//Se inserta el nuevo nodo
  if (balance <= 0)//Si el valor es menor que el de la raÃ­z
    nodo->izquerda = insertHeap(nodo->izquerda, valor);//Se continÃºa insertando recursivamente hacia la izquerda
  else  //de lo contrario, si es mayor
    nodo->derecha = insertHeap(nodo->derecha, valor);//Se actÃºa reciprocamente hacia la derecha
  nodo->altura = 1 + max(getBalanceHeap(nodo->izquerda), getBalanceHeap(nodo->derecha));//Se actualiza la altira despuÃ©s de la insersiÃ³n
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


// FunciÃ³n que elimina un valor de un AVL, y guarda en el inicio de una lista de arreglo el arbol
nodeHeap *deletenodeHeap(nodeHeap *root, nodeDH* head[1]) {
   int balance = 0;
  balance = getBalanceHeap(root);//Pide el balance para resolver segÃºn tres casos
  if (root->izquerda == NULL && root->derecha == NULL){//Si no hay nodos siguientes
    head[0] = instertNDH(head[0], root->valor);
    free(root);
    return NULL;//Se inserta el nuevo nodo
  }else if (balance <= 0){//Si el valor es menor que el de la raÃ­z
    if(root->derecha){
      swap(&root->valor, &root->derecha->valor);
      root->derecha = deletenodeHeap(root->derecha, head);//Se continÃºa insertando recursivamente hacia la izquerda
      root->izquerda = to_heap(root->izquerda);
      root = to_heap_1(root);
    }else{
      swap(&root->valor, &root->izquerda->valor);
      root->izquerda = deletenodeHeap(root->izquerda, head);//Se continÃºa insertando recursivamente hacia la izquerda
      root->derecha = to_heap(root->derecha);
      root = to_heap_1(root);
    }
  }else{  //de lo contrario, si es mayorif(root->derecha){
    if(root->derecha){
      swap(&root->valor, &root->derecha->valor);
      root->derecha = deletenodeHeap(root->derecha, head);//Se continÃºa insertando recursivamente hacia la izquerda
      root->izquerda = to_heap(root->izquerda);
      root = to_heap_1(root);
    }else{
      swap(&root->valor, &root->izquerda->valor);
      root->izquerda = deletenodeHeap(root->izquerda, head);//Se continÃºa insertando recursivamente hacia la izquerda
      root->derecha = to_heap(root->derecha);
      root = to_heap_1(root);
    }
  }
  root->altura = 1 + max(getBalanceHeap(root->izquerda), getBalanceHeap(root->derecha));//Se actualiza la altira despuÃ©s de la insersiÃ³n
  return root;
}

//----------------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------//

/*

Trabajo de operaciones que obtendremos de las listas

*/

//Funciones para AVL de maximos, minimos y medidas de estadistica

//valor maximo
double maxvalorAVL(nodeAVL *node){

    if(node==NULL){
        return 0;

    }

    double res = node -> valor;
    double izqres = maxvalorAVL(node -> izquerda);
    double derres = maxvalorAVL(node -> derecha);
    if(izqres > res){
        res = izqres;
    }
    if(derres > res){
        res = derres;
    }
    return res;

}

//Valor minimo 

void minvalorAVL(nodeAVL* node){

    nodeAVL *aux=NULL;
    aux=minValuenodeAVL(node);
    printf(" EL VALOR MINIMO: %le\n",aux->valor);

}

//cuartiles

void cuartiles(nodeAVL* nodeAVL){

  printf(" Primer Cuartil: %le\n",nodeAVL->izquerda->valor);
  printf(" Segundo Cuartil: %le\n",nodeAVL->valor);
  printf(" Tercer Cuartil: %le\n",nodeAVL->derecha->valor);  
   
}

nodeAVL* repeticion(nodeAVL* node){

  nodeAVL *aux1;
  nodeAVL *aux2;
  if(node){
    if(node->izquerda)
      aux1 = repeticion(node->izquerda);  
    if(node ->derecha){
      aux2 = repeticion(node->derecha);
      if(aux1 && aux1->repeticiones < aux2->repeticiones){
        aux1=aux2;
      }
      else if(aux1 != NULL){
        aux1=aux2;
      }

    }
    if(aux1->repeticiones > node->repeticiones){
      return node;
    }
  }
  return aux1;
}

//repeticion de lista DH, lista doblemente enlazada

nodeDH* repeticionDH(nodeDH *head1){
  nodeDH* max = head1;
  nodeDH* aux1 = head1;
  while(aux1){
    if(aux1 && aux1->repeticiones < max->repeticiones){

      max=aux1;

    }
    aux1 = aux1->siguiente;
  }
  return max;
}

//repeticion de lista M, no es doblemente enlazada

nodeM* repeticionM(nodeM *head1){
  nodeM* max = head1;
  nodeM* aux1 = head1;
  while(aux1){
    if(aux1 && aux1->repeticion < max->repeticion){

      max=aux1;

    }
    aux1 = aux1->siguiente;
  }
  return max;
}

// Funciones Listas

void estadisticasDD(nodeDH* head){
  nodeDH* aux1 = head;
  nodeDH* aux2 = head;
  nodeDH* aux3 = head;
  nodeDH* aux4 = head;
  while (aux4 && aux4->siguiente && aux4->siguiente->siguiente && aux4->siguiente->siguiente->siguiente && aux4->siguiente->siguiente->siguiente->siguiente)
  {
    aux1 = aux1->siguiente;
    aux2 = aux2->siguiente->siguiente;
    aux3 = aux3->siguiente->siguiente->siguiente;
    aux4 = aux4->siguiente->siguiente->siguiente->siguiente;
  }
  printf("El primer cuartil es: %le\n", aux1->valor);
  printf("La media y segundo cuartil es: %le\n", aux2->valor);
  printf("El tercer cuartil es: %le\n", aux3->valor);
  return;
}

void mediaMerge(nodeM* head){
  nodeM* aux = splitM(head);
  printf("La media es: %le\n", aux->valor);
}

void cuartilesMerge(nodeM* head){
  nodeM* aux1 = splitM(head);
  nodeM* aux2 = splitM(aux1);
  nodeM* aux = aux1->siguiente;
  aux1->siguiente = NULL;
  nodeM* aux3 = splitM(head);
  aux1->siguiente = aux;
  printf("El primer cuartil es: %le", aux3->valor);
  printf("El segundo cuartil es: %le", aux1->valor);
  printf("El tercer cuartil es: %le", aux2->valor);
  
}

// Funciones para listas de maximos, minimos y medidas de estadisitica



int main(){

  double time1 = 0.0;
	double time2 = 0.0;
	double numero;

	char c = '\0';

	nodeM* head1 = NULL;
	nodeDH* head3 = NULL;
  nodeDH* head2[1] = {NULL};
  nodeDH* auxDH = NULL;
  nodeAVL* auxAVL = NULL;
  nodeAVL* node = NULL;
  nodeM* aux = NULL;
  nodeHeap* heap = NULL;

  int opcion;

	FILE* documento;

  //Menu dentro del intmain


  do{
    printf("\nMenu:\n\n1- Ordenar con Merge Sort\n \n2- Ordenar con AVL\n \n 3- Ordenar con Quick Sort\n \n 4- Ordenar con Heap Sort\n \n5- Salir\n\n elija opcion: ");
    scanf("%d", &opcion);
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
      time1=clock();
      head1 = mergeSort(head1);
      time1= (time1 - clock())/CLOCKS_PER_SEC;
      printf("Tiempo merge sort: %lf\n", time1);
      cuartilesMerge(head1);
      mediaMerge(head1); 
      aux = repeticionM(head1);
      printf("La moda es: %le\n", aux->valor);
      aux = eliminarListaM(aux);
      head1 = eliminarListaM(head1);
      
      break;

    case 2:
      printf(" ORDENAR UTILIZANDO AVL ");
      printf("\n");
      time1 = clock();
      documento=fopen("ArchivoA.tex", "r");
	    while(1 == fscanf(documento, "%le", &numero)){
	        node = insert(node, numero);
      }
      fclose(documento);
      time1 = (time1 - clock())/ CLOCKS_PER_SEC;
      printf("Tiempo insercion AVL: %lf\n", time1);
      auxAVL=repeticion(node);
      printf("La moda es: %le\n", auxAVL->valor);
      while(node){
        node = deletenodeAVL(node, node->valor);
      }
      

      break;

    case 3:
    // Te dejare ql quicksort, porque no se si usar nodeD o nodeDH xdxdxdxd
      printf(" ORDENAR UTILIZANDO QUICKSORT ");
      printf("\n");
      documento=fopen("ArchivoA.tex", "r");
	    while(1 == fscanf(documento, "%le", &numero)){
	        head3 = instertND(head3, numero);
      }
      fclose(documento);
      time1=clock();
      QuickSort(head3);
      time1=(time1 - clock())/CLOCKS_PER_SEC;
      printf("Tiempo Quick Sort: %lf\n", time1);
      estadisticasDD(head3);
      auxDH = repeticionDH(head3);
      printf("La moda es: %le\n", auxDH->valor);
      head3=eliminarListaDH(head3);
      break;
    case 4:
      printf(" ORDENAR UTILIZANDO HEAPSORT ");
      printf("\n");

      documento=fopen("ArchivoA.tex", "r");
	    while(1 == fscanf(documento, "%le", &numero)){
	        heap = insertHeap(heap, numero);
      }
      fclose(documento);
      time2=clock();
      while(heap){
        heap = deletenodeHeap(heap,&head2[0]);
      }
      time2=(time2 - clock()/CLOCKS_PER_SEC);
      printf("Tiempo Heap sort: %lf/n", time1);
      estadisticasDD(head2[0]);
      auxDH = repeticionDH(auxDH);
      printf("La moda es: %le\n", auxDH->valor);
      head2[0] = eliminarListaDH(head2[0]);
      
      break;      

    
    default:
      break;
    }

  }while(opcion!=5);


	
  return 0;
  
}
