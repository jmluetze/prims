/*
 * Binomial heap implementation by Jonathan Luetze
 *
 *    methods: newBinHeap, creates an empty Binomial Heap with initializations
 *           : decreaseKeyBinHeap, updates value of node and bubbles up value
 *           : extractBinHeap, extracts the minimum value of the heap
 *
 *           : bubbleUp, swaps node values as necessary
 *           : insertBinHeap, receives a value and inserts it as a node into the tree
 *           : Unionb, merges the rootlists from two heaps together
 *
 *           : consolidate, mpving of all subheaps from the root into an array, merge if necessary,
 *             and move back into root list
 *           : updateConsolidationArray, merges the rootlists from two heaps together
 *           : combine, merges subheaps according to degree of root
 *
 *           : setParent, sets the parent node
 *           : addVerticesToRootlist, adds a vertex to the root list
 *           : updateValueKey, updates values
 */

#include "binheap.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

binheap * newBinHeap(int(*c)(void *, void *))
{
    binheap *b = malloc(sizeof(binheap)+1);
    b->c = c;
    b->rootlist = newDLL();
    b->extrememin = NULL;
    b->size = 0;
    b->vertices = NULL;
    return b;
}

node * decreaseKeyBinHeap(binheap *b, node *n, void *nv)
{
    vertexX *v = (vertexX*)nv;  node *a = b->extrememin;
    n->data = v;
    n = bubbleUp(b,n);
    
    if(b->c(a->data,v) > 0) {b->extrememin = n;}
    
    return n;
}

node * extractBinHeap(binheap *b)
{
    node *y = b->extrememin;
    DeleteNode(b->rootlist,y);
    setParent(y->children);
    merge(b->rootlist,y->children);
    if(b->size > 1) {consolidate(b);}
    
    b->size--;
    return y;
}

node * bubbleUp(binheap *b, node *n)
{
    if(n == n->parent)                     {return n;}
    else if(b->c(n->data, n->parent->data) > 0) {return n;}
    else
    {
        vertexX *a = n->data;
        a->owner = n->parent;
        a = n->parent->data;
        a->owner = n;
        
        vertexX *temp = n->data;
        n->data = n->parent->data;
        n->parent->data = temp;
        
        return bubbleUp(b,n->parent);
    }
}


node * insertBinHeap(binheap *b,void *v)
{
    node *n = (node *)malloc(sizeof(node) +2);
    n->data = v;
    n->parent = n;
    n->children = newDLL();
    
    insert(b->rootlist,n);
    b->size++;
    
    consolidate(b);
    
    return n;
}

void Unionb(binheap *b, binheap *donor)
{
    merge(b->rootlist, donor->rootlist);
    b->size = b->rootlist->size + donor->rootlist->size;
    donor->rootlist = newDLL();
    donor->size = 0;
    donor->extrememin = NULL;
    consolidate(b);
}

void consolidate(binheap *b)
{
    int i = 0;
    
    node ** D;
    int Dsize = log2(b->size)+1;
    D = malloc(sizeof(node *) * (Dsize + 2));
   
    for(i = 0; i < Dsize; ++i) {D[i] = NULL;}
    
    while (b->rootlist->size != 0)
    {
        struct node *spot = b->rootlist->front;
        DeleteNode(b->rootlist,spot);
        
        updateConsolidationArray(b,D,spot);
    }
    
    b->extrememin = NULL;
    for (i = 0; i < Dsize; ++i)
    {
        if (D[i] != NULL)
        {
            insert(b->rootlist,D[i]); node *temp = b->extrememin;
            if(b->extrememin == NULL || b->c(D[i]->data,temp->data) < 0)
            {
                b->extrememin = D[i];
            }
        }
    }
}

void updateConsolidationArray(binheap *b, node ** D,struct node *spot)
{
    int degree = spot->children->size;

    while (D[degree] != NULL)
    {
        spot = combine(b,spot,D[degree]);
        D[degree] = NULL;
        degree++;
    }
    D[degree] = spot;
}

struct node * combine(binheap *b, struct node *x, struct node *y)
{
    if (b->c(x->data,y->data) < 0)
    {
        insert(x->children,y);
        y->parent = x;
        return x;
    }
    else
    {
        insert(y->children,x);
        x->parent = y;
        return y;
    }
}

struct DLL * setParent(struct DLL *dll)
{
    node *temp = dll->front;
    while (temp != NULL && temp->data != NULL)
    {
        temp->parent = temp;
        temp = temp->next;
    }
    return dll;
}

vertexX * addVerticesToRootlist(binheap *b, void *a, int infinity)
{
    vertexX *v = (vertexX*)a;
    v->key = infinity;
    v->owner = insertBinHeap(b,v);
    return v;
}

vertexX * updateValueKey(vertexX *v, int weight, binheap *b, vertexX *u)
{
    if(u->predecessor != v->name)
    {
        v->predecessor = u->name;
        v->key = weight;
    }
    
    if(v->flag != 1) {decreaseKeyBinHeap(b,v->owner, v);}
    return v;
}
