#include <stdio.h>
#include <stdlib.h>
#define MAX 10

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

int leftMostChild(Tree t, int nodeNdx){
    int x;

    for (x = 0; x < MAX && t[x].parent != nodeNdx; x++){}

    return (x == MAX ? -1 : x);
}

int rightSibling(Tree t, int nodeNdx){
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
    int values[MAX] = {7, 6, -1, -2, 9, 2, 7, 2, -1, 5};

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

int main(){
    Tree daTree;

    populateTree(daTree);

    printf("Root of tree is %d\n", root(daTree));
    printf("Parent of node %d is %d\n", 5, parent(daTree, 5));

    int rootToNum = 4;
    printf("Printing from root to node %d: ", rootToNum);
    printTreeRootToNode(daTree, rootToNum);
    printf("\n");

    //Finding leftmost child
    int lmNode = 2;
    printf("Leftmost child of node %d is: %d\n", lmNode, leftMostChild(daTree, lmNode));

    //Finding right sibling
    int rNode = 5;
    printf("Right sibling of node %d is: %d\n", rNode, rightSibling(daTree, rNode));
    

    return 0;
}