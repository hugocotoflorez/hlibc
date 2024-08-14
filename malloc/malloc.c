#include "malloc.h"
#include "../string/string.h" // memmove
#include <sys/mman.h>         // mmap, munmap

// global reference to free list (sorted linked list started at head)
node_t *head = NULL;


void
__alloc_destroy()
{
    munmap(head, SIZE);
    head = NULL;
}

__attribute__((constructor)) static void // call function before main
__init__()
{
    // avoid multiple initializations
    if (head == NULL)
    {
        // mmap() return a block of free space
        head =
        mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

        head->size = SIZE - sizeof(node_t);
        head->next = NULL;
    }
}

void
free(void *ptr)
{
    header_t *hptr;     // header of ptr
    node_t   *prev;     // previous free-node
    node_t   *new_node; // new node to add

    if (ptr == NULL)
        return;

    hptr = ptr - sizeof(header_t);

    // check if hptr is valid
    if (hptr->magic != MAGIC)
        return;

    // unset header as valid
    hptr->magic = 0;

    // new node to add
    new_node       = (node_t *) hptr;
    new_node->size = hptr->size + sizeof(header_t) - sizeof(node_t);

    // get prev node
    prev = head;
    while (prev->next != NULL && prev->next < new_node)
        prev = prev->next;

    // insert new node into list
    new_node->next = prev->next;
    prev->next     = new_node;

    // join with next node if also free
    if ((char *) new_node + sizeof(node_t) + new_node->size ==
        (char *) new_node->next)
    {
        new_node->size += new_node->next->size + sizeof(node_t);
        new_node->next = new_node->next->next;
    }

    // join with previous node if also free
    if ((char *) prev + sizeof(node_t) + prev->size == (char *) new_node)
    {
        prev->size += new_node->size + sizeof(node_t);
        prev->next = new_node->next;
    }

    // if any memory is used, return it to os
    if (prev->size == SIZE - sizeof(node_t))
    {
        __alloc_destroy();
    }
}

void *
malloc(int size)
{
    node_t *temp      = head;
    void   *ptr       = NULL;
    int     best_size = SIZE;

    // check if it is initialized
    if (head == NULL)
        __init__();

    // check if size is valid
    if (size <= 0)
        return NULL;

    // if size is smaller than headers diff new header dont have enought space at free
    if (size < sizeof(node_t) - sizeof(header_t))
    {
        size = sizeof(node_t) - sizeof(header_t);
    }

    // best fit algorithm (smallest free space greater or equal than size)
    // done in a linear way, end in O(n) algorithm
    do
    {
        if (temp->size >= size && best_size > temp->size)
        {
            best_size = temp->size;
            ptr = (void *) temp; // ptr is the list entry that best fit
        }
        temp = temp->next;

    } while (temp != NULL);

    // if pointer fits in memory
    if (ptr != NULL)
    {
        // update free list
        ((node_t *) ptr)->size -= size + sizeof(header_t);
        // move pointer to last free 'size' bytes in free space
        ptr = (char *) ptr + best_size - size + sizeof(node_t);
        // add header to allocated memory
        *((header_t *) ptr - 1) = (header_t){ .size = size, .magic = MAGIC };
    }
    // return ptr or NULL if cant allocate that memory ammount
    return ptr;
}


void *
realloc_after(void *ptr, int size, header_t *hptr)
{
    void     *next        = (char *) ptr + hptr->size;
    header_t *hnext       = next;
    node_t   *nnext       = next;
    int       needed_size = size - hptr->size;
    node_t   *prev;

    if (hnext->magic == MAGIC) // next block is used
        return NULL;

    // create next node
    if (nnext->size > needed_size)
    {
        *(node_t *) (next + needed_size) = (node_t){
            .size = nnext->size - needed_size,
            .next = nnext->next,
        };

        hptr->size += needed_size;

        // get prev node
        prev = head;
        while (prev->next != NULL && (void *) prev->next < ptr)
            prev = prev->next;
        prev->next = next + needed_size;

        return ptr;
    }
    else
        return NULL;
}

void *
realloc_before(void *ptr, int size, header_t *hptr)
{
    node_t *prev;

    // get prev node
    prev = head;
    while (prev->next != NULL && (void *) prev->next < ptr)
        prev = prev->next;

    // check if previous free block is just before current block
    if ((char *) prev + prev->size == (char *) hptr)
    {
        prev->size -= size - hptr->size;
        *(header_t *) ((char *) hptr - (size - hptr->size)) = (header_t){
            .size  = size,
            .magic = MAGIC,
        };
        memmove((char *) hptr - (size - hptr->size) + sizeof(header_t), ptr, size);
    }

    return NULL;
}

void *
realloc(void *ptr, int size)
{
    void     *newptr = NULL;
    header_t *hptr;

    if (head == NULL) // check if it is initialized
        __init__();

    if (ptr == NULL) // allow use rehalloc as mhalloc
        return malloc(size);

    hptr = ptr - sizeof(header_t); // get header

    if (hptr->size >= size) // if size is invalid return NULL
        return NULL;

    // try to allocate just after
    if ((newptr = realloc_after(ptr, size, hptr)) != NULL)
        return newptr;

    // try to allocate just before
    if ((newptr = realloc_before(ptr, size, hptr)) != NULL)
        return newptr;


    // default rehalloc
    // allocate new block and move data, then free current block
    if ((newptr = malloc(size)) == NULL) // check for out-of-memmory error
        return NULL;

    memmove(newptr, ptr, hptr->size); // move data
    free(ptr);

    return newptr;
}
