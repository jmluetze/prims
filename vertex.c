/*
 * Vertex structure implementation by Jonathan Luetze
 *
 *    methods: newVertexX, creates an vertex with initializations
 *           : vertexXComparator, determines location of nodes in binomial heap
 *           : vertexXNameComparator, helper function for Breadth-First-Search algorithm
 */

#include "vertex.h"
#include <stdio.h>
#include <stdlib.h>

/******************* Creating New VertexX *******************/

vertexX * newVertexX(int v)
{
    vertexX *o = malloc(sizeof(vertexX) +1);
    o->name = v;
    o->key = 0; 
    o->owner = NULL;
    o->predecessor = -1;
    o->color = 'w';
    o->flag = 0;
    return o;
}

/******************* Comparator Method *******************/

int vertexXComparator(void *o1,void *o2)
{
    vertexX *a = (vertexX*)o1;
    vertexX *b = (vertexX*)o2;
        
    if(a->key - b->key == 0)
    {
        if(a->predecessor - b->predecessor == 0)
        {
            return a->name - b->name;
        }// break tie on predecessor, still tie, do name;
        else return a->predecessor - b->predecessor;
    }
    else {return a->key - b->key;}
}

int vertexXNameComparator(void *o1,void *o2)
{
    vertexX *a = (vertexX*)o1;
    vertexX *b = (vertexX*)o2;
    
    if(a->name - b->name == 0)
    {
        if(a->predecessor - b->predecessor == 0)
        {
            return a->key - b->key;
        }// break tie on predecessor, still tie, do name;
        else return a->predecessor - b->predecessor;
    }
    else {return a->name - b->name;}
}
