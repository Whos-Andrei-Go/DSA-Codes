#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct node{
    int data;
    struct node *link;
}*List;

typedef struct{
    List nodes[MAX];
    int root;
}Tree;

void initialize(Tree *t){
    int x;

    for(x = 0; x < MAX; x++){
        t -> nodes[x] = NULL;
    }

    t -> root = -1;
}

List createList(int num) {
    List l = (List) malloc (sizeof(struct node));
    l -> data = num;
    l -> link = NULL;

    return l;
}

void addChildrenToNode(Tree *t, int nodeNdx, int num){
    List l = createList(num);

    List *trav;

    for(trav = &(t -> nodes[nodeNdx]); *trav != NULL; trav = &((*trav) -> link)){}
    *trav = l;
}

int parent(Tree t, int num){
    List trav;
    int daParent = -1;

    for(int x = 0; x < MAX && daParent == -1; x++){
        for(trav = t.nodes[x]; trav != NULL && trav -> data != num; trav = trav -> link){}

        if (trav != NULL){
            daParent = x;
        }
    }
    
    return daParent;
}

int leftMostChild(Tree t, int parent){
    return (t.nodes[parent] -> data);
}

int rightSibling(Tree t, int num){
    List trav;
    int daSibling = -1;

    for(int x = 0; x < MAX && daSibling == -1; x++){
        for(trav = t.nodes[x]; trav != NULL && trav -> data != num; trav = trav -> link){}

        if (trav != NULL){
            daSibling = ((trav -> link) -> data);
        }
    }
    
    return daSibling;
}

int root(Tree t){
    return t.root;
}

int label(Tree t, int nodeNdx){
    //What is this actually supposed to return? The first child?
    return nodeNdx;
}

void printNodeAndChildren(Tree t, int nodeNdx){
    printf("Parent is: %d\n", nodeNdx);
    printf("Children of node %d are: ", nodeNdx);

    List trav;

    for(trav = t.nodes[nodeNdx]; trav != NULL; trav = trav -> link){
        printf("%d ", trav -> data);
    }

    printf("\n");
}


int main(){
    Tree daTree;

    initialize(&daTree);

    //Adding children to node 0
    addChildrenToNode(&daTree, 0, 1);
    addChildrenToNode(&daTree, 0, 3);
    addChildrenToNode(&daTree, 0, 5);

    //Print root
    daTree.root = 6; //I'mma just set it too.
    printf("Root of tree is: %d\n", root(daTree));

    //Finding label
    int lNode = 2;
    printf("Label of node %d is: %d\n", lNode, label(daTree, lNode));

    //Finding leftmost child
    int lmNode = 0;
    printf("Leftmost child of node %d is: %d\n", lmNode, leftMostChild(daTree, lmNode));

    //Finding right sibling
    int rNode = 1;
    printf("Right sibling of node %d is: %d\n", rNode, rightSibling(daTree, rNode));

    //Finding parent of node
    int fpNode = 5;
    printf("Parent of node %d is: %d\n", fpNode, parent(daTree, fpNode));
    
    //Prints a node and its children
    int pNode = 0;
    printNodeAndChildren(daTree, pNode);

    return 0;
}