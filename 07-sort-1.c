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

int comparator(const void *a, const void *b)
{
    /* The element storage in our list is an array of void pointers, or in other
     * words, a void **. The first pointer is the location within the element
     * storage, and the second pointer (2nd deref) is the pointer to the actual
     * data. */
    const int **ai = (const int **) a;
    const int **bi = (const int **) b;
    return **ai > **bi;
}

test_start("Tests the sort function");

subtest("Creates a list, sorts it, and verifies the output",
    int data[] = {
        99,
        45,
        21,
        0,
        3,
        42,
        108,
        9999,
        12,
        40,
        3,
        4,
        1,
        2,
        370281,
        7
    };

    int data_sorted[] = {
        0,
        1,
        2,
        3,
        3,
        4,
        7,
        12,
        21,
        40,
        42,
        45,
        99,
        108,
        9999,
        370281,
    };

    struct elist *list = elist_create(20);
    for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
        elist_add(list, &data[i]);
    }

    elist_sort(list, comparator);

    for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
        int *value = elist_get(list, i);
        test_assert(*value == data_sorted[i]);
        printf("%d == %d\n", *value, data_sorted[i]);
    }

);

test_end
