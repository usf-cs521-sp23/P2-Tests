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

void *malloc(size_t size)
{
    return NULL;
}

void *calloc(size_t nmemb, size_t size)
{
    return NULL;
}

test_start("Tests functions when malloc()/calloc() is broken");

subtest("elist_create",
{
    struct elist *list = elist_create(55);
    test_assert(list == NULL);
});

test_end
