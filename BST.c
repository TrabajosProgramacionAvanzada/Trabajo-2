#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodeBTS {
  double valor;
  struct nodeBTS *izquerda, *derecha;
} nodeBTS;

// Funci�n que inicializa un nodo BST
nodeBTS *newNodeBTS(double item) {
  nodeBTS *temp = (nodeBTS *)malloc(sizeof(nodeBTS));
  temp->valor = item;
  temp->izquerda = temp->derecha = NULL;
  return temp;
}

//Funci�n para imprimir en pantalla el �rbol binario
void inorder(nodeBTS *root) {
  if (root != NULL) {
    inorder(root->izquerda);
    printf("%le ", root->valor);
    inorder(root->derecha);
  }
}

//Funci�n que inserta nodo en el �rbol binario
nodeBTS *insert(nodeBTS *nodeBTS, double valor) {
  if (nodeBTS == NULL)//Caso base, si no hay ra�z
    return newNodeBTS(valor);
  if (valor < nodeBTS->valor)//De lo contrario seguir la recurrci�n hacia la izquerda si el valor a ingresar es menor al de la ra�z
    nodeBTS->izquerda = insert(nodeBTS->izquerda, valor);
  else//De lo contrario se contin�a hacia la derecha
    nodeBTS->derecha = insert(nodeBTS->derecha, valor);
  return nodeBTS;
}

//Funci�n que devuelve el valor m�nimo del �rbol
nodeBTS *minValueNodeBTS(nodeBTS *nodeBTS) {
  nodeBTS *current = nodeBTS;
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


int main() {
  nodeBTS *root = NULL;
  int i = 0;
  root = insert(root, 50);
  root = insert(root, 30);
  root = insert(root, 20);
  root = insert(root, 40);
  root = insert(root, 70);
  root = insert(root, 60);
  root = insert(root, 80);

  printf("Inorder: \n");
  inorder(root);
  scanf("%d", &i);
  printf("\nEliminar %d\n",i);
  root = deleteNodeBTS(root, i);
  printf("Inorder con %d eliminado \n", i);
  inorder(root);

  scanf("%d", &i);
  printf("\nEliminar %d\n",i);
  root = deleteNodeBTS(root, i);
  printf("Inorder con %d eliminado \n", i);
  inorder(root);

  scanf("%d", &i);
  printf("\nEliminar %d\n",i);
  root = deleteNodeBTS(root, i);
  printf("Inorder con %d eliminado \n", i);
  inorder(root);

  scanf("%d", &i);
  return 0;
}
