/*
 * Generic dynamic fillable array class, by John C. Lusth
 *
 *    methods: newArray, create an empty array
 *           : addArray, add an item to the array
 *           : sortArray, sort the items in the array
 *           : freeArray, dispose of the array when done
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "array.h"

static void Fatal(char *,...);
static void mergeSort(void **,int,int,void **,int (*)(void *,void *));

array *
newArray(int (*cmp)(void *,void *))
{
    array *a = malloc(sizeof(array));
    if (a == 0) Fatal("out of memory\n");
    a->cmp = cmp;
    a->size = 0;
    a->capacity = 10;
    a->store = malloc(sizeof(void *) * a->capacity);
    if (a->store == 0) Fatal("out of memory\n");
    return a;
}

void
addArray(array *a,void *v)
{
    if (a->size == a->capacity)
    {
        a->capacity *= 2;
        a->store = realloc(a->store,sizeof(void *)*a->capacity);
        if (a == 0) Fatal("out of memory\n");
    }
    a->store[a->size] = v;
    a->size += 1;
}

void
sortArray(array *a)
{
    void **aux = malloc(sizeof(void *) * a->size);
    if (aux == 0) Fatal("out of memory\n");
    mergeSort(a->store,0,a->size,aux,a->cmp);
    free(aux);
}

void
freeArray(array *a)
{
    //objects in the array are not freed
    free(a->store);
    free(a);
}

/**** private methods ****/

static void
mergeSort(void **arr,int lo,int hi,void **aux,int (*cmp)(void *,void *))
{
    if (lo + 1 >= hi) return;
    
    int mid = (lo + hi) / 2;
    
    mergeSort(arr,lo,mid,aux,cmp);
    mergeSort(arr,mid,hi,aux,cmp);
    
    int i = lo,j = mid,k = lo;
    while (i < mid && j < hi)
    {
        if (cmp(arr[i],arr[j]) < 0)
            aux[k++] = arr[i++];
        else
            aux[k++] = arr[j++];
    }
    while (i < mid)
        aux[k++] = arr[i++];
    while (j < hi)
        aux[k++] = arr[j++];
    
    for (i = lo; i < hi; ++i)
        arr[i] = aux[i];
}

static void
Fatal(char *fmt, ...)
{
    va_list ap;
    
    fprintf(stderr,"An error occured: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    
    exit(-1);
}
