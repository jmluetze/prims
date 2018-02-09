#include "array.h"
#include "dll.h"

typedef struct vertexX
{
    int distance;
    int name;
    int key;
    int flag;
    void *owner;
    int predecessor;
    char color;
}vertexX;

vertexX * newVertexX(int v);

int vertexXComparator     (void *o1,void *o2); // compares Vertecies by name;
int vertexXNameComparator (void *o1,void *o2);
