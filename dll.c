/*
 * Doubly-Linked List and Queue with Node structure implementation by Jonathan Luetze
 *
 *    methods: newDLL, creates an empty Doubly-Linked List with initializations
 *           : insert, inserts a node into the doubly-linked list
 *           : insertQ, inserts a node into the queue
 *
 *           : *merge, merges two Doubly-Linked Lists
 *           : Delete, deletes a node from the queue
 *           : DeleteNode, deletes a node from the Doubly-Linked List
 */


#include "dll.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

struct DLL* newDLL(void)
{
    struct DLL* temp = (struct DLL*)malloc(sizeof(struct DLL) +2);
    
    temp->size = 0;
    temp->front = temp->rear = NULL;
    return temp;
}

void insert(struct DLL *dll, node *temp)
{
    dll->size += 1;
    temp->next = temp->prev = NULL;
    if ((dll->rear == NULL && dll->front == NULL) ||
        (dll->rear->data == NULL && dll->front->data == NULL))
            {dll->rear = dll->front = temp;}
    else
    {
        dll->front->prev = temp;
        temp->next = dll->front;
        dll->front = temp;
    }
}

void insertQ(struct DLL *dll, node *temp)
{
    dll->size += 1;
    temp->next = temp->prev = NULL;
    if (dll->size == 1) {dll->rear = dll->front = temp;}
    else
    {
        dll->front->prev = temp;
        temp->next = dll->front;
        dll->front = temp;
    }
}

struct DLL *merge(struct DLL *a, struct DLL *b)
{
    if(a->size > 0 && b->size > 0)
    {
        a->rear->next = b->front;
        b->front->prev = a->rear;
        a->rear = b->rear;
        a->size += b->size;
    }
    else if(a->size == 0 && b->size > 0)
    {
        a->front = b->front;
        a->rear = b->rear;
        a->size = b->size;
    }
    return a;
}

struct node * Delete(struct DLL *dll)
{
    struct node * temp; dll->size--;
    if (dll->front == dll->rear)
    {
        temp = dll->front;
        dll->front = dll->rear = NULL;
        return temp;
    }
    else
    {
        temp = dll->rear;
        dll->rear = dll->rear->prev;
        dll->rear->next = NULL;
        return temp;
    }
    return temp;
}

void DeleteNode(struct DLL *dll, struct node *temp)
{
    if (dll->front == dll->rear)
    {
        dll->front = dll->rear = NULL;
    }
    else
    {
             if(temp == dll->front) {dll->front = temp->next;}
        else if(temp == dll->rear)
        {
            dll->rear = temp->prev;
            temp->prev->next = NULL;
        }
        else
        {
            struct node *previousNode = temp->prev;
            previousNode->next = temp->next;
            temp->next->prev = previousNode;
        }
        temp->prev = temp->next = NULL;
    }
    dll->size--;
}
