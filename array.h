/* public interface for the array class, by John C. Lusth
 *
 * see array.c for a description
 *
 */

typedef struct array
{
    void **store;               // array where the data is kept
    int size;                   // current count of items in the array
    int capacity;               // how many items the array can hold
    int (*cmp)(void *,void *);  // a comparator for sorting
} array;

extern array *newArray(int (*)(void *,void *));
extern void addArray(array *,void *);
extern void sortArray(array *);
extern void freeArray(array *);