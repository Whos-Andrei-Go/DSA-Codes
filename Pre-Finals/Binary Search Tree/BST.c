#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} *Tree;

void initTree(Tree *t){
    *t = NULL;
}

void insertTree(Tree *t, int data) {
	Tree temp = (Tree)malloc(sizeof(struct node));

	if(temp != NULL) {
		temp->data = data;
		temp->left = NULL;
		temp->right = NULL;

		Tree *trav;

		for (trav = t; *trav != NULL && (*trav)->data != data; trav = (data < (*trav) -> data ? &(*trav) -> left : &(*trav) -> right)){}

        if(*trav == NULL) {
            *trav = temp;
        }
	}
}

void populateTree(Tree *T, int arr[], int size) {
	for (int i = 0; i < size; i++) {
		insertTree(T, arr[i]);
	}
}

bool member(Tree t, int num){
    Tree trav;

    for(trav = t; trav != NULL && trav -> data != num; trav = (num < trav -> data ? trav -> left : trav -> right)){}

    return (trav != NULL ? true : false);
}

void deleteWithOneChild(Tree *t) {
    Tree temp = *t;
    *t = (*t)->left != NULL ? (*t)->left : (*t)->right;
    free(temp);
}

void deleteElem(Tree *t, int num) {
    Tree* trav;

    for(trav = t; *trav != NULL && (*trav) -> data != num;){
        if (num < (*trav) -> data){
            trav = &(*trav)->left;
        }else{
            trav = &(*trav)->right;
        }
    }

    //ELEMENT FOUND
    if (*trav != NULL){
        Tree *scsor = trav;

        if ((*trav) -> right != NULL){
            scsor = &(*trav) -> right;
        }
       
        if (*scsor != NULL){
            while((*scsor)->left != NULL) {
                scsor = &(*scsor)->left;
            }

            (*trav) -> data = (*scsor) -> data; 
        }
       
        deleteWithOneChild(scsor);
    }
}

void preorder(Tree t){
    if (t != NULL) {
        printf("%d ", t->data);
		preorder(t -> left);
		preorder(t -> right);
	}
    else {
        printf("_ ");
    }
}

int main(){
    Tree t;
    int arr[] = {10, 5, 7, 14, 12, 18, 15, 11};
	int arrSize = sizeof(arr) / sizeof(arr[0]);

    initTree(&t);
    populateTree(&t, arr, arrSize);

    //IS MEMBER?
    int mNum = 15;
    printf("Number %d %s part of the tree\n", mNum, member(t, mNum) ? "IS" : "IS NOT");

    //DISPLAY
    preorder(t);

    //DELETING
    int dNum = 10;
    printf("\nAfter deleting %d: \n", dNum);
    deleteElem(&t, dNum);
    preorder(t);

    return 0;
}