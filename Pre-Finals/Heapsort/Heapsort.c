#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
    int elements[MAX];
    int lastNdx;
}HeapList;

void minHeapify(HeapList *hl, int parent){
    int min = parent;
    int LC = 2 * parent + 1;
    int RC = LC + 1;

    if (LC <= hl -> lastNdx && hl -> elements[LC] <= hl -> elements[min]){
        min = LC;
    }

    if (RC <= hl -> lastNdx && hl -> elements[RC] <= hl -> elements[min]){
        min = RC;
    }

    if (min != parent){
        int temp = hl -> elements[min];
        hl -> elements[min] = hl -> elements[parent];
        hl -> elements[parent] = temp;

        minHeapify(hl, min);
    }
}

void maxHeapify(HeapList *hl, int parent){
    int max = parent;
    int LC = 2 * parent + 1;
    int RC = LC + 1;

    if (LC <= hl -> lastNdx && hl -> elements[LC] >= hl -> elements[max]){
        max = LC;
    }

    if (RC <= hl -> lastNdx && hl -> elements[RC] >= hl -> elements[max]){
        max = RC;
    }

    if (max != parent){
        int temp = hl -> elements[max];
        hl -> elements[max] = hl -> elements[parent];
        hl -> elements[parent] = temp;

        maxHeapify(hl, max);
    }
}

void heapSortMin(HeapList *hl){
    for (int x = ((hl -> lastNdx - 1) / 2); x >= 0; x--){
        minHeapify(hl, x);
    }
}

void heapSortMax(HeapList *hl){
    for (int x = ((hl -> lastNdx - 1) / 2); x >= 0; x--){
        maxHeapify(hl, x);
    }
}

int deleteMin(HeapList *hl){
    int min = hl -> elements[0];

    hl -> elements[0] = hl -> elements[hl -> lastNdx];
    (hl -> lastNdx)--;

    minHeapify(hl, 0);
}

int deleteMax(HeapList *hl){
    int max = hl -> elements[0];

    hl -> elements[0] = hl -> elements[hl -> lastNdx];
    (hl -> lastNdx)--;

    maxHeapify(hl, 0);
}

void display(HeapList hl) {
    for(int x = 0; x <= hl.lastNdx; x++) {
        printf("%d ", hl.elements[x]);
    }
    printf("\n");
}

int main(){
    HeapList hl;
    int arr[] = {3, 2, 6, 5, 9, 11, 7, 1, 8, 10};

    for (int x = 0; x < MAX; x++){
        hl.elements[x] = arr[x];
    }

    hl.lastNdx = 9;
   
    /*//MIN HEAP

    //Heap Sort
    printf("Heap Sort MIN: \n");
    heapSortMin(&hl);
    display(hl);

    //DELETE MIN;
    printf("Heap after DELETE MIN: \n");
    deleteMin(&hl);
    display(hl);

    */

    //MAX HEAP

    //Heap Sort
    printf("Heap Sort MAX: \n");
    heapSortMax(&hl);
    display(hl);

    //DELETE MAX;
    printf("Heap after DELETE MAX: \n");
    deleteMax(&hl);
    display(hl);
  
    return 0;
}