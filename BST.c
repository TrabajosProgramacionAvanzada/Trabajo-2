#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodeBTS {
  double valor;
  long long int repeticiones;
  struct nodeBTS *izquerda, *derecha;
} nodeBTS;

// Funci�n que inicializa un nodo BST
nodeBTS *newNodeBTS(double item) {
  nodeBTS *temp = (nodeBTS *)malloc(sizeof(nodeBTS));
  temp->valor = item;
  temp->repeticiones = 0;
  temp->izquerda = temp->derecha = NULL;
  return temp;
}

//Funci�n para imprimir en pantalla el �rbol binario
void inorderBST(nodeBTS *root) {
  if (root != NULL) {
    inorder(root->izquerda);
    printf("%le ", root->valor);
    inorder(root->derecha);
  }
}

//Funci�n que inserta nodo en el �rbol binario
nodeBTS *insertBTS(nodeBTS *node, double valor) {
  if (node == NULL)//Caso base, si no hay ra�z
    return newNodeBTS(valor);
  if (valor < node->valor)//De lo contrario seguir la recurrci�n hacia la izquerda si el valor a ingresar es menor al de la ra�z
    node->izquerda = insertBTS(node->izquerda, valor);
  else if(valor > node->valor){//De lo contrario se contin�a hacia la derecha
    node->derecha = insertBTS(node->derecha, valor);
  }else{
    node->repeticiones++;
  }
  return node;
}

//Funci�n que devuelve el valor m�nimo del �rbol
nodeBTS *minValueNodeBTS(nodeBTS *node) {
  nodeBTS *current = node;
  while (current && current->izquerda != NULL)//Hasta que no est� en la hoja m�s a la izquerda
    current = current->izquerda;//Sigue a la izquerda
  return current;
}

//Funci�n que elimina un nodo del �rbol
nodeBTS *deleteNodeBTS(nodeBTS *root, double valor) {
  nodeBTS *temp = NULL;
  if (root == NULL)//Si no hay ra�z (caso base)
    return root;
  if (valor < root->valor)//Si el valor a eliminar est� a la izquerda
    root->izquerda = deleteNodeBTS(root->izquerda, valor);//cotiua hacia la izquerda
  else if (valor > root->valor)//De lo contrario, si es mayor
    root->derecha = deleteNodeBTS(root->derecha, valor);//Sigue hacia la derecha
  else {//De lo contrario se encontr� el nodo a eliminar
    if (root->izquerda == NULL) {//Caso sin hijos o uno de ambos
      temp = root->derecha;//Se guarda
      free(root);//Elimina directamente
      return temp;//Devuelve el valor copiado
    } else if (root->derecha == NULL) {//Caso rec�proco al anterior
      temp = root->izquerda;
      free(root);
      return temp;
    }//Caso con dos hijos
    temp = minValueNodeBTS(root->derecha);//Se busca el nodo menor de los mayores
    root->valor = temp->valor;//Se copia el valor a la ra�z
    root->derecha = deleteNodeBTS(root->derecha, temp->valor);//Se elimina la hoja copiada
  }
  return root;
}


int main(){	
	double time1 = 0.0;
	double time2 = 0.0;
	double numero;
	char c = '\0';
	nodeBTS* head = NULL;
	FILE* documento;
	time1 = clock();
	documento=fopen("ArchivoA.tex", "r");
	while(1 == fscanf(documento, "%le", &numero)){
	  head = insertBTS(head, numero);
	}
	fclose(documento);
	time1 = (clock() - time1) / CLOCKS_PER_SEC;
	printf("lectura de archivo: %.4lf \n", time1);
	time1 = clock();
	time1 = (clock() - time1) / CLOCKS_PER_SEC;
	printf("merge sort: %.4lf \n", time1);
	getchar();
  inorder(head);
  while (head){
   head = deleteNodeBTS(head, head->valor);
  }
	return 0;
}
