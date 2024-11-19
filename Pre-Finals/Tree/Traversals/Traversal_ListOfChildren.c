//THIS WAS DONE USING LIST OF CHILDREN BECAUSE IT WAS EASIER THAT WAY

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

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

void preorder(Tree t, int nodeNdx){
    printf("%d ", nodeNdx);

    if (t.nodes[nodeNdx] != NULL){
        List trav;

        for(trav = t.nodes[nodeNdx]; trav != NULL; trav = trav -> link){
            preorder(t, trav -> data);
        }
    }
}

void inorder(Tree t, int nodeNdx) {
    if (nodeNdx >= 0){
        List trav = t.nodes[nodeNdx];

        if (trav != NULL) {
            inorder(t, trav -> data);
        }

        printf("%d ", nodeNdx);

        if (trav != NULL) {
            for(trav = trav -> link; trav != NULL; trav = trav -> link){
                 inorder(t, trav->data);
            }   
        }
    }
}


void postorder(Tree t, int nodeNdx){
    if (t.nodes[nodeNdx] != NULL){
        List trav;

        for(trav = t.nodes[nodeNdx]; trav != NULL; trav = trav -> link){
            postorder(t, trav -> data);
        }
    }
    
    printf("%d ", nodeNdx);
}


int main(){
    Tree daTree;

    initialize(&daTree);

    //Adding children
    addChildrenToNode(&daTree, 0, 1);
    addChildrenToNode(&daTree, 0, 3);
    addChildrenToNode(&daTree, 0, 5);

    addChildrenToNode(&daTree, 1, 6);
    addChildrenToNode(&daTree, 1, 7);

    addChildrenToNode(&daTree, 3, 2);
    addChildrenToNode(&daTree, 3, 4);

    addChildrenToNode(&daTree, 5, 8);
    addChildrenToNode(&daTree, 5, 9);

    addChildrenToNode(&daTree, 7, 11);
    addChildrenToNode(&daTree, 7, 12);

    addChildrenToNode(&daTree, 9, 13);
    addChildrenToNode(&daTree, 9, 14);

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