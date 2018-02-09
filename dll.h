/* public interface for the Doubly-Linked List and Queue class, by Jonathan Luetze
 *
 * see dll.c for a description
 *
 */

#ifndef dll_h
#define dll_h

#include "node.h"
#include <stdio.h>
#endif

struct DLL
{
    int size;
    struct node* front;
    struct node* rear;
};

/**** Create & Insert ****/

struct DLL* newDLL  (void);
void insert         (struct DLL *q, node *temp);

/**** Merge & Delete by Node ****/

struct DLL* merge   (struct DLL *a, struct DLL *b);
void DeleteNode     (struct DLL *dll, struct node *temp);

/**** Insert & Delete like a Queue ****/

void insertQ        (struct DLL *dll, node *temp);
struct node* Delete (struct DLL *q);
