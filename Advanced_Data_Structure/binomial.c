#include <stdio.h>
#include <stdlib.h>
#include<limits.h>

//Stucture for binomial heap
typedef struct Binomial
{
    int key;
    int degree;
    struct Binomial* parent;
    struct Binomial* sibling;
    struct Binomial* child;
}bino;

// create a new node
bino* createNode(int key)
{
    bino* newnode = (struct Binomial* )malloc(sizeof(struct Binomial));
    newnode->key = key;
    newnode->degree = 0;
    newnode->parent = newnode->sibling = newnode->child = NULL;
}

//merge root list
bino* mergerootlist(bino* h1, bino* h2)
{
    // if one of the heap is empty return another one
    if(!h1) return h2;
    if(!h2) return h1;

    bino* head = NULL;   // head of merged list
    bino** pos = &head;  // Pointer to the current position in merged list

    // if both are valid traverse the heap to merge
    while(h1 && h2)
    {
        // choose the node with smaller degree and advance the pointer 
        if(h1->degree <= h2->degree){
            *pos = h1;
            h1 = h1->sibling;
        }
        else{
            *pos = h2;
            h2 = h2->sibling;
        }
        pos = &((*pos)->sibling);  // move pos to next pointer in merged list
    }
    //attach the remaining node from whichever list is not yet exhausted
    *pos = h1 ? h1:h2;
    return head;         // return head of merged list
}

//Link two binomial tree of same degree
void linktree(bino* y, bino* z)
{
    // if(y->key < z->key)
    // {
    //     y->parent = z;
    //     y->sibling = z->child;
    //     z->child = y;
    //     z->degree++;
    // }
    // else{
    //     z->parent = y;
    //     z->sibling = y->child;
    //     y->child = z;
    //     y->degree++;
    // }
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}

// Union oStart combining the root lists of both heaps in increasing order of their degrees.
/*
Start combining the root lists of both heaps in increasing order of their degrees.
Compare the degrees of the roots and link the trees with smaller degrees first.
After combining, check for trees of the same degree, if two trees of the same degree are found, link them to form a 
single tree of the next higher degree.
Continue this process until no two trees of the same degree remain.f two heap
*/
bino* Union(bino* h1, bino* h2)
{
    bino* newhead = mergerootlist(h1,h2);
    if(!newhead) return NULL;

    bino* prev = NULL;
    bino* curr = newhead;
    bino* next = curr->sibling;

    // traverse the merged list
    while(next)
    {
        // if degree are different or next-next has same degree as curr
        // skip linking 
        if((curr->degree != next->degree) || (next->sibling && next->sibling->degree == curr->degree)){
            prev = curr;
            curr = next;
        }
        else{
            // degree are same and curr.key <= next.key. make next to child of curr
            if(curr->key <= next->key)
            {
                curr->sibling = next->sibling;
                linktree(next,curr);
            }
            else{ // degree are same and curr.key > next.key make curr to child of next
                if(!prev) 
                    newhead = next;             // update head if curr was root
                else 
                    prev->sibling = next;      // remove curr from root list
                linktree(curr,next);
                curr = next;
            }
        }
        next = curr->sibling;
    }
    return newhead;
}

// Insert new element in binomial heap
/*
Create a new binomial heap with the new node.
Merge the new binomial heap with the existing heap by merging them based on their degrees.. 
Ensure there is at most one tree of each degree by combining trees of the same degree to maintain Binomial Heap properties.
*/

bino* insert(bino* heap, int key)
{
    bino* node = createNode(key);
    return Union(heap, node); 
}

// print the heap
void printheap(bino* heap)
{
    while(heap)
    {
        printf("B%d:\n", heap->degree);
        printf("Root: %d\n",heap->key);
        bino* child = heap->child;
        printf("Children ");
        while(child){
            printf("%d ",child->key);
            child = child->sibling;
        }
        printf("\n");
        heap = heap->sibling;
    }
}

int main()
{
    bino* heap = NULL;
    heap = insert(heap,10);
    heap = insert(heap,5);
    heap = insert(heap,15);
    heap = insert(heap,20);
    heap = insert(heap,30);

    printf("Heap after insertion:\n");
    printheap(heap);
    printf("````````````````````````````````````````````````\n");
    bino* min = findmin(heap);
    printf("Minimum key: %d\n",min->key);
    printf("````````````````````````````````````````````````\n");
    bino* extracted = extractmin(&heap);
    printf("Extracted min: %d\n",extracted->key);
    printf("````````````````````````````````````````````````\n");
    printf("New merge heap is:\n");
    printheap(heap);
    printf("````````````````````````````````````````````````\n");
}
