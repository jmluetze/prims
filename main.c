/* 
 * By Jonathan Luetze
 *
 * Main file for the implementation of Prims Algorithm
 *
 * Main process:
 * 1. A dynamically-fillable array is used to store adjacent vertices
 * 2. Vertices are moved from array to binomial heap
 * 3. Prims algorithm is executed
 * 4. Once finished, a Breadth-First-Search is performed
 *
 * Below are the prototypes of the functions, divided by categories
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "string.h"
#include "binheap.h"

int size = 0, infinity = 0, VertexCount = 0;

/* BFS Methods */

void BFS2          (int **matrix, binheap *b, vertexX *root);
void * setQElement (struct vertexX *a);
void printBFSArray (array *vertexXArray);

/* Binheap Methods */

vertexX * prims    (int **matrix, binheap *b);
binheap * fillTree (int **matrix, vertexX *root);

/* Matrix Methods */

int ** initMatrix (const char *file);
int ** fillMatrix (const char *file, int **matrix);
vertexX *setRoot  (int ** matrix);

int main(int argc,char **argv)
{
    char *file;
    if (!argv[1]) {exit(0);}
    else          {file = argv[1];}
    
    int ** matrix = initMatrix(file); vertexX *root = newVertexX(-1);
    
    matrix = fillMatrix(file,matrix);
    
    root = setRoot(matrix);
    
    binheap *b = fillTree(matrix,root); root = b->vertices[root->name];
    
    while(b->size > 0)
    {
        vertexX *nextRoot = prims(matrix, b);
                
        BFS2(matrix,b,root);
        
        root = nextRoot;
    }
    argc = 0;
    return argc;
}

vertexX *setRoot(int ** matrix)
{
    int i = 0,j = 0;struct vertexX *root = newVertexX(size+1);
    for (i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            if (matrix[i][j] != infinity)
            {
                if(j < i && j < root->name) {root->name = j;}
                else if(i < j && i < root->name) {root->name = i;}
            }
        }
    }
    return root;
}

int ** initMatrix (const char *file)
{
    int i = 0, j = 0, ** matrix,count = 0;
    FILE *fp = fopen(file, "r");
    while (!feof(fp))
    {
        const char *a = readToken(fp);
        if(a != NULL && strcmp(a,";") != 0)
        {
            
            if(count < 2 && atoi(a) > size) {size = atoi(a);}
            count++;
            
            if(atoi(a) > infinity) {infinity = atoi(a) + 1;}
        }
        else {count = 0;}
    }fclose(fp);
    
    size = size+1;
    
    matrix = malloc(sizeof(int *) * size);
    int *tmp =malloc(size *size * sizeof(int));
    for(i = 0; i < size; i++) {matrix[i] = &tmp[i*size];}
    
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            matrix[i][j] = infinity;
        }
    }
    return matrix;
}

int ** fillMatrix(const char *file, int **matrix)
{
    int x = 0,count = 0,weight = 0, i = 0, j = 0;
    
    FILE *fp = fopen(file, "r");
    
    while (!feof(fp))
    {
        const char *a = readToken(fp);
        if(a != NULL)
        {
            if(*a ==';') //end of declaration, add weight to matrix
            {
                if(matrix[i][j] == infinity)
                {
                    if(weight == 1) {matrix[i][j] = x; matrix[j][i] = x;}
                    else            {matrix[i][j] = 1; matrix[j][i] = 1;}
                }
                count = 0; weight = 0;
            }
            else
            {
                x = atoi(a);
                     if (count == 0) {j = x;}
                else if (count == 1) {i = x;}
                else if (count == 2) {count = 0; weight = 1;}
                count++;
            }
        }
    }fclose(fp);
    return matrix;
}

vertexX * prims(int **matrix, binheap *b)
{
    int i = 0,flag = 1; vertexX *nextRoot = newVertexX(-1);
    while(b->size != 0)
    {
        node *n = extractBinHeap(b);
        vertexX *u = (vertexX*)n->data;
        
        if(u->key == infinity)
        {
            if(flag == 1)
            {
                b->vertices[u->name] = addVerticesToRootlist(b,u,0);
                nextRoot = b->vertices[u->name]; flag = 0;
            }
            else {b->vertices[u->name] = addVerticesToRootlist(b,u,infinity);}
            
            break;
        }
        
        for(i = 0; i < size; i++)
        {
            if(matrix[u->name][i] != infinity)
            {
                if(matrix[u->name][i] < b->vertices[i]->key && b->vertices[i]->flag != 1)
                {
                    b->vertices[i] = updateValueKey(b->vertices[i],
                                                    matrix[u->name][i],b,
                                                    b->vertices[u->name]);
                    b->vertices[u->name]->flag = 1;
                }
            }
        }
    }
    return nextRoot;
}

binheap * fillTree(int **matrix, vertexX *root)
{
    int i = 0, j = 0, k = 0; vertexX *xX;
    binheap *b = newBinHeap(vertexXComparator);
    
    b->vertices = malloc(sizeof(vertexX) * size + 1);
    for (k = 0; k < size; k++) {b->vertices[k] = NULL;}
    
    for(j = 0; j < size; j++)
    {
        for(i = 0; i < size; i++)
        {
            if(matrix[i][j] != infinity)
            {
                if(b->vertices[j] == NULL)
                {
                    xX = newVertexX(j); VertexCount++;
                    if(root->name == j)
                        {b->vertices[j] = addVerticesToRootlist(b,xX,0);}
                    else
                        {b->vertices[j] = addVerticesToRootlist(b,xX,infinity);}
                }
                if(b->vertices[i] == NULL)
                {
                    xX = newVertexX(i); VertexCount++;
                    if(root->name == i)
                        {b->vertices[i] = addVerticesToRootlist(b,xX,0);}
                    else
                        {b->vertices[i] = addVerticesToRootlist(b,xX,infinity);}
                }
            }
        }
    } return b;
}

void BFS2(int **matrix, binheap *b, vertexX *root)
{
    int i, totalWeight = 0, distance = 0, a = 0; struct DLL *d = newDLL();
    vertexX *tempVertex = NULL, *OneVertex = NULL;
    array printEdgeArray = *newArray(vertexXNameComparator);
    
    for (i = 0; i < size; ++i)
    {
        tempVertex = b->vertices[i];
        if(tempVertex != NULL)
        {
            tempVertex->color = 'w';
            tempVertex->distance = distance;
        }
    }
    root = b->vertices[root->name];
    root->color = 'g';
    root->predecessor = 0;
    printf("%d : %d;",root->distance,root->name);
    
    insertQ(d,setQElement(NULL)); insertQ(d,setQElement(root));

    while(d->size != 1)
    {
        node *n = Delete(d); tempVertex = n->data;
        
        if(tempVertex == NULL)
        {
            if(a!= 0) {printf("\n%d : ",a);}a++;
            sortArray(&printEdgeArray); printBFSArray(&printEdgeArray);
            printEdgeArray = *newArray(vertexXNameComparator);
            
            insertQ(d,setQElement(NULL));continue;
        }
        
        for(i = 0; i < size; i++)
        {
            if(matrix[tempVertex->name][i] != infinity
               && b->vertices[i]->predecessor == tempVertex->name)
            {
                OneVertex = b->vertices[i];
                if(OneVertex->color == 'w')
                {
                    OneVertex->color = 'g';
                    totalWeight += OneVertex->key;
                    addArray(&printEdgeArray, OneVertex);
                    if(OneVertex->predecessor != -1)
                        {insertQ(d,setQElement(OneVertex));}
                }
            }
        }if(tempVertex->name != root->name)
            {b->vertices[OneVertex->predecessor]->color = 'b';}
    } printf("\nweight: %d\n", totalWeight);
}

void * setQElement(struct vertexX *a)
{
    node *b = malloc(sizeof(node));
    b->data = a;
    return b;
}

void printBFSArray(array *vertexXArray)
{
    int i;
    for (i = 0; i < vertexXArray->size; ++i)
    {
        vertexX *OneVertex = vertexXArray->store[i];
        printf("%d(%d)%d",OneVertex->name,OneVertex->predecessor,OneVertex->key);
        if(i < vertexXArray->size-1) {printf(", ");}
        else if (i == vertexXArray->size-1) {printf(";");}
    }
}
