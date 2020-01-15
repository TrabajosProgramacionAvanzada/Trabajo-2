/*

			BINARY SEARCH TREE

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long long int ull;

typedef struct Node{

	ull k=0; //Clave del nodo
	ull r=0; //Veces que se repite la clave
	struct Node *left;
	struct Node *right;

} node;

void insert(node **raiz, ull key);
void delete(node **raiz, ull key);
void swap(node **raiz, node **aux);
void search(node **raiz, ull key);

void insert(node **raiz, ull key){
	if(*raiz==NULL){
		*raiz = malloc(sizeof(node));
		*raiz->k = key;
		*raiz->left = NULL;
		*raiz->right = NULL;
	}else{
		if(*raiz->k > key){
			insert(&*raiz->left, key);
		}
		if(*raiz->k < key){
			insert(&*raiz->right, key);
		}
		if(*raiz->k == key){
			*raiz->r++;
		}
	}
}

void delete(node **raiz, ull key){
	if(*raiz == NULL){
		return;
	}else{
		if(*raiz->k > key){
			delete(&*raiz->left, key);
		}
		if(*raiz->k < key){
			delete(&*raiz->right, key);
		}
		if(*raiz->k == key){
			if(*raiz->r >= 2){
				*raiz->r--;
			}else{
				*raiz->r--;
				node aux = *raiz;
				if(*raiz->left == NULL){
					*raiz = *raiz->right;
				}else if(*raiz->right == NULL){
					*raiz = *raiz->left;
				}else{
					swap(&*raiz->left, &aux);
				}
				free(aux);
			}
		}
	}
}

void swap(node **raiz, node **aux){
	if(*raiz-right == NULL){
		*aux->k = *raiz->k;
		*aux = *raiz;
		*a = *raiz->left;
	}else{
		swap(&*raiz->right, *aux);
	}
}

void search(node **raiz, ull key){
	if(*raiz == NULL){
		return;
	}else{
		if(*raiz->k > key){
			search(&*raiz->left, key);
		}
		if(*raiz-> k < key){
			search(&*raiz->right, key);
		}
		if(*raiz->k == key){
			return;
		}
	}
}