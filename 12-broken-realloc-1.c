#if 0
    source "${TEST_LIB}/crunner" -lelist
#endif

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <dlfcn.h>

#include "elist.h"

struct elist {
    size_t capacity;
    size_t size;
    size_t item_sz;
    void *element_storage;
};

void *realloc(void *ptr, size_t size)
{
    return NULL;
}

test_start("Tests functions when realloc() is broken");

subtest("The list will not be resizable, so go past its capacity. Will likely segfault if realloc errors are not handled correctly.",
{
    struct elist *list = malloc(sizeof(*list));
    list->element_storage = malloc(sizeof(int) * 5);
    list->capacity = 5;
    list->size = 0;
    list->item_sz = sizeof(int);

    for (int i = 0; i < 100; ++i) {
        elist_add(list, &i);
    }
});

test_end
