#if 0
    source "${TEST_LIB}/crunner" -lelist
#endif

#include <stddef.h>
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

test_start("Tests creating and destroying lists. Note that these tests depend on size() and capacity() being implemented.");

subtest("Creating and destroying lists",
{
    struct elist *list = elist_create(0);
    test_assert(list != NULL);
    elist_destroy(list);

    list = elist_create(999);
    test_assert(list != NULL);
    elist_destroy(list);
});

subtest("Checking list size and capacity",
{
    struct elist *list = elist_create(0);
    test_assert(elist_size(list) == 0);
    test_assert(elist_capacity(list) == 10);
    elist_destroy(list);

    list = elist_create(999);
    test_assert(elist_size(list) == 0);
    test_assert(elist_capacity(list) == 999);
    elist_destroy(list);
});

test_end
