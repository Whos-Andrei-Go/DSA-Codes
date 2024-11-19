#include <stdio.h>
#include <stdlib.h>
#define MAX 20

typedef enum {
    NO_PARENT = -1,
    EMPTY = -2
} ParentStatus;

typedef struct {
    int data;
    int parent;
} Node;

typedef Node Tree[MAX];

int parent(Tree t, int nodeNdx){
    return (t != NULL ? t[nodeNdx].parent : -1);
}

int leftMostChild(Tree t, int parent){
    //Scuffed but okay
    int x;

    for (x = 0; x < MAX && t[x].parent != parent; x++){}

    return (x == MAX ? -1 : x);
}

int rightSibling(Tree t, int nodeNdx){
     //Scuffed but okay
     
    int nodeParent = t[nodeNdx].parent;
    int x;

    for (x = nodeNdx + 1; x < MAX && t[x].parent != nodeParent; x++){}

    return (x == MAX ? -1 : x);

}

int label(Tree t, int nodeNdx){
    return (t != NULL ? t[nodeNdx].data : -1);
}

int root(Tree t){
    int x;

    if (t != NULL){
        for(x = 0; x < MAX && t[x].parent != - 1; x++){}
    }
    
    //Returns -1 if root is not found... somehow
    return (t == NULL || x == MAX ? -1 : x);
}

void initialize(Tree t){
    int x;

    for(x = 0; x < MAX; x++){
        t[x].data = EMPTY;
    }
}

void populateTree(Tree t){
    int x;
    int values[MAX] = {-1, 0, 3, 0, 3, 0, 1, 1, 5, 5, -2, 7, 7, 9, 9, -2, -2, -2, -2, -2};

    for(x = 0; x < MAX; x++){
        t[x].data = x;
        t[x].parent = values[x];
    }
}

void makeNull(Tree t){
    int x;

    for(x = 0; x < MAX; x++){
        t[x].data = EMPTY;
    }
}

void printTreeRootToNode(Tree t, int nodeNdx){
    if (nodeNdx != NO_PARENT && t[nodeNdx].parent != EMPTY){
        printTreeRootToNode(t, t[nodeNdx].parent);
        printf((t[nodeNdx].parent == -1 ? "%d" : " -> %d"), nodeNdx);
    }  
}

void preorder(Tree t, int nodeNdx){
    printf("%d ", t[nodeNdx].data);

    int child;

    for(child = leftMostChild(t, nodeNdx); child != NO_PARENT && child != EMPTY; child = rightSibling(t, child)){
        preorder(t, child);
    }
}

void inorder(Tree t, int nodeNdx) {
    if (nodeNdx != NO_PARENT && nodeNdx != EMPTY){
        int child = leftMostChild(t, nodeNdx);

        if (child != NO_PARENT && child != EMPTY) {
            inorder(t, child);
        }

        printf("%d ", t[nodeNdx].data);

        if (child != NO_PARENT && child != EMPTY) {
            for(child = rightSibling(t, child); child != NO_PARENT && child != EMPTY; child = rightSibling(t, child)){
                inorder(t, child);
            }
        }
    }
   
}

void postorder(Tree t, int nodeNdx) {
    int child;

    for(child = leftMostChild(t, nodeNdx); child != NO_PARENT && child != EMPTY; child = rightSibling(t, child)){
        postorder(t, child);
    }

    printf("%d ", t[nodeNdx].data);
}

int main(){
    Tree daTree;

    populateTree(daTree);

    //Preorder
    int travNode = 0;
    printf("Printing from node %d PRE ORDER: ", travNode);
    preorder(daTree, travNode);
    printf("\n");

    //Inorder
    printf("Printing from node %d IN ORDER: ", travNode);
    inorder(daTree, travNode);
    printf("\n");

    printf("Printing from node %d POST ORDER: ", travNode);
    postorder(daTree, travNode);
    printf("\n");
    

    return 0;
}