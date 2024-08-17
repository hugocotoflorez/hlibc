#ifndef _HALLOCATOR
#define _HALLOCATOR

#include "../stddef/stddef.h" // size_t

/*
 * Memory management library
 * Something as in stdlib
 *
 * Author: Hugo Coto Florez
 *
 * Inspiration: ostep book
 */

/* Info for code readers
 *
 * Name conventions:
 * - ptr: (void*) no relevant info
 * - hptr: (header_t*) current block header
 * - pptr: (page_t*) current page header
 *
 * I hope code is as readable as possible. Any doubt
 * about what is happening can be asked directly to
 * myself (contact info in github profile) or oppening
 * an issue.
 *
 * Althought gcc let do arithmetic over void*, as C standard
 * said that void pointer arithmetic has undefined behaviour
 * I cast to char* all this cases.
 *
 * I appreciate any contribution, from finding a new bug
 * to implementing a new feature. Thanks for your time.
 */

/* Info about low level mechanisms
 *
 * Page:
 * Pages are raw chunks of data recived thow a mmap() call.
 * It contains a page header (page_t) at the LSB byte.
 * Remaining block space can be one of the following entries.
 *
 * Node:
 * A node (node_t) is the structure that store info
 * about a free block. It is placed just before the
 * free block.
 *
 * Header:
 * A header (header_t) that contains info about reserved memory.
 * After the header start an used block.
 *
 * Free block.
 * Data or nothing that is not allocated neither used
 * by any header. Just before this block there are a
 * node (node_t).
 *
 * Used block.
 * Data that where allocated. Just before this block
 * there are a header (header_t).
 */


/* total chunk size */
#define SIZE 4096
/* Magic number. To check integrity */
#define MAGIC 0x777

typedef struct __page_t page_t;
typedef struct __node_t node_t;

/* Above each free block a node_t node is placed. */
struct __node_t
{
    size_t  size; // free block size in bytes (without node_t size)
    node_t *next; // next free node in the same page, or NULL if last
    node_t *prev; // previous free node in the same page, or NULL if first
    page_t *page; // page header of page that nide is in
};

/* First data of each page. */
struct __page_t
{
    size_t   size;           // page size (with page header)
    page_t  *next;           // next page
    page_t  *prev;           // prev page
    unsigned page_id;        // page number
    unsigned max_free_block; // max free block in bytes
    unsigned min_free_block; // min free block in bytes
};

#define PAGE_REAL_SIZE(pptr) ((pptr)->size - sizeof(page_t))

/* Header above used memory */
typedef struct
{
    size_t   size;
    unsigned magic;
} header_t;

/* Free space after changing headers, from header_t to node_t */
#define REAL_FREE_SPACE(hptr) \
    ((hptr)->size - sizeof(header_t) + sizeof(node_t))

/* Alloc SIZE bytes
 * Return: pointer to new allocated block
 * Errors: return NULL
 */
void *malloc(size_t size);

/* Alloc SIZE bytes and move data from ptr to a new block.
 * PTR would be free.
 * Return: pointer to new allocated block.
 * Error: previous pointer is not free and return NULL
 */
void *realloc(void *ptr, size_t size);

/* Free memory pointed by ptr
 * Error: If cant be free do nothing
 */
void free(void *ptr);

#endif // !_HALLOCATOR
