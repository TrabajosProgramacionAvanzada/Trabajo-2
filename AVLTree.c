/*

			AVL TREE

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef unsigned long long int ull;

typedef struct Node{

	ull k=0; //Clave del nodo
	ull r=0; //Veces que se repite la clave
	int h=0;
	struct Node *left;
	struct Node *right;

} node;

node *insertR(node **raiz, ull key);
node *deleteR(node **raiz, ull key);
node *search(node **raiz, ull key);
node *sRD(node **raiz);
node *sRI(node **raiz);
int maxN(ull a, ull b);
int balance(node **raiz);
void search(node **raiz, ull key);


int balance(node **raiz){

	return *raiz==NULL ? 0 : *raiz->left->h - *raiz->right->h;

}

int maxN(ull a, ull b){

	return a<b ? b : a

}

node *sRD(node **raiz){

	node *left = *raiz->left;
	node *right = left->right;

	left->right = *raiz;
	*raiz->left = right:
	*raiz->h = maxN(*raiz->left->h, *raiz->right->h+1);
	*left->h = maxN(left->left->h, left->right->h+1);

	return left;
}

node *sRI(node **raiz){
	
	node *right = *raiz->right;
	node *left = right->left;

	right->left = *raiz;
	*raiz->right = left;

	*raiz->h = maxN(*raiz->left->h, *raiz->right->h+1);
	*right->h = maxN(right->left->h, right->right->h+1);

	return right;

}
node *insertR(node **raiz, ull key){

	if(*raiz==NULL){

		*raiz = malloc(sizeof(node));
		*raiz->k = key;
		*raiz->r = 1
		*raiz->h = 1;
		*raiz->left = NULL;
		*raiz->right = NULL;

		return *raiz;

	}else{
		if(*raiz->k > key){

			*raiz=insertR(&*raiz->left, key);
		
		}else if(*raiz->k < key){

			*raiz=insertR(&*raiz->right, key);
		
		}else if(*raiz->k == key){

			*raiz->r++

			return *raiz;
		
		}
	}

	*raiz->h = 1 + maxN(*raiz->left->h, *raiz->right->h);
	int fB = balance(&*raiz);

	if(fB > 1 && *raiz->left->k > key){
		
		return sRD(&*raiz);
	
	}
	if(fB < -1 && *raiz->right->k < key){
		
		return sRI(&*raiz);
	
	}
	if(fB > 1 && *raiz->right->k < key){
		
		*raiz->left = sRI(&*raiz->left);
		
		return sRD(&*raiz);
	
	}
	if(fB < -1 && raiz->right->k > key){
		
		*raiz->right = sRD(&*raiz->right);
		
		return sRD(&*raiz);
	
	}

	return *raiz;

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

node *deleteR(node **raiz, ull key){

	if(*raiz==NULL){
		
		return NULL;
	
	}else{

		if(*raiz->k > key){

			*raiz = deleteR(&*raiz->left, key);

		}else if(*raiz->k < key){

			*raiz = deleteR(&*raiz->right, key);

		}else{

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

	*raiz->h = 1 + maxN(*raiz->left->h, *raiz->right->h);
	int fB = balance(&*raiz);

	if(fB > 1 && *raiz->left->k > key){
		
		return sRD(&*raiz);
	
	}
	if(fB < -1 && *raiz->right->k < key){
		
		return sRI(&*raiz);
	
	}
	if(fB > 1 && *raiz->right->k < key){
		
		*raiz->left = sRI(&*raiz->left);
		
		return sRD(&*raiz);
	
	}
	if(fB < -1 && raiz->right->k > key){
		
		*raiz->right = sRD(&*raiz->right);
		
		return sRD(&*raiz);
	}
	return *raiz;

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