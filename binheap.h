/* public interface for the binomial heap class, by Jonathan Luetze
 *
 * see binheap.c for a description
 *
 */

#include "vertex.h"

typedef struct binheap
{
    int size;
    int (*c)(void *,void *);
    struct DLL *rootlist;
    void *extrememin;
    vertexX **vertices;
} binheap;

/**** Create and Insert ****/

binheap * newBinHeap (int(*c)(void *, void *));
node* insertBinHeap  (binheap *b,void *v);
vertexX * addVerticesToRootlist(binheap *b, void *v, int infinity);

/**** Extract and Fixup ****/

node * extractBinHeap(binheap *b);
void Unionb          (binheap *b, binheap *donor);
void consolidate     (binheap *b);
struct node * combine(binheap *b, struct node *x, struct node *y);
void updateConsolidationArray(binheap *b, node ** D,struct node *spot);
struct DLL * setParent(struct DLL *dll);

/**** Bubble Up ****/

node * decreaseKeyBinHeap (binheap *b, node *n, void *nv);
node * bubbleUp           (binheap *b, node *n);
vertexX * updateValueKey  (vertexX *v, int weight, binheap *b, vertexX *u);
