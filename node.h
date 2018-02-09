//  node.h
//
//  Created by Jonathan Luetze

#ifndef node_h
#define node_h

#endif

typedef struct node
{
    struct node *parent, *next, *prev;
    void * data;
    struct DLL *children;
} node;
