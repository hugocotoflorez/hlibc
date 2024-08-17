#include "malloc.h"
#include "../string/string.h" // memmove
#include <sys/mman.h>         // mmap, munmap

/* See malloc.h for further information about
 * how this shit work and interface usage for
 * programmers.
 */

/* head is the first page.
 * If head is NULL there are no pages initialized
 */
static page_t *head = NULL;


/* Return a page to os. All its contents would be lost.
 * Have to be called once all page contents are free.
 * PAGE is deleted from pages list and head updated if needed.
 * PAGE is set to NULL on success.
 */
static void
page_destroy(page_t *__page)
{
}

/* Ask for a new page and update PAGE to the new reserved memory.
 * New chunk is formated with page and header, ready to use.
 * If PAGE is not NULL at function call, PAGE is returned without
 * any action or change.
 * If PAGE is NULL an still NULL at return, some error happened.
 */
static void *
page_create(page_t *__page)
{
    return NULL;
}

void
free(void *ptr)
{
}

void *
malloc(size_t size)
{
    return NULL;
}

void *
realloc(void *ptr, size_t size)
{
    return NULL;
}
