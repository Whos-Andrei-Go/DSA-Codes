#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct{
    int data[MAX];
    int lastNdx;
} Tree;

void initTree(Tree *t);
void populateTree(Tree *t, int arr[], int size);
void insertTree(Tree *t, int data);
int deleteMin(Tree *t);
void displayTree(Tree t);

int main(){
   Tree T;
	int arr[] = {4, 2, 5, 2, 1};
	int size = sizeof(arr) / sizeof(arr[0]);

    initTree(&T);
	populateTree(&T, arr, size);

    printf("Elements in order: ");
    displayTree(T);

    return 0;
}

void initTree(Tree *t){
    t -> lastNdx = -1;
}

void populateTree(Tree *t, int arr[], int size){
    int x;

    for(x = 0; x < size; x++){
        insertTree(t, arr[x]);
    }
}

void insertTree(Tree *t, int data){
    if (t -> lastNdx + 1 < MAX){
        int child = ++(t -> lastNdx);
        int parent = (child - 1) / 2;

        while (child > 0 && t -> data[parent] > data){
            t -> data[child] = t -> data[parent];
          
            child = parent;
            parent = (child - 1) / 2;  
        }

        t->data[child] = data;
    }
}

int deleteMin(Tree *t) {
    int retVal = -1;

    if (t -> lastNdx >= 0){
        retVal = t -> data[0];
        int repNum = t -> data[(t -> lastNdx)--];
        
        int parent = 0;
        int LC = 2 * parent + 1;
        int RC = LC + 1; 
        
        int child = (t -> data[LC] > t -> data[RC] ? RC : LC);

        while (child <= (t -> lastNdx) && t -> data[child] < repNum){
            t -> data[parent] = t -> data[child];
          
            parent = child;
            LC = 2 * parent + 1;
            RC = LC + 1; 

            if (RC <= (t -> lastNdx)){
                child = (t -> data[LC] > t -> data[RC] ? RC : LC);
            }
            else{
                child = LC;
            }
        }

        t -> data[parent] = repNum;
    }


    return retVal;
}

void displayTree(Tree T) {
    int temp;
    while((temp = deleteMin(&T)) != -1) {
        printf("%d ", temp);
    }
}