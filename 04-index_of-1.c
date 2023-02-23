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
    size_t capacity; /*!< Storage space allocated for list items */
    size_t size;     /*!< The actual number of items in the list */
    void **element_storage;
};

test_start("Tests the index_of search function");

subtest("Locating elements from a test array",
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

    struct elist *list = elist_create(20);
    for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
        elist_add(list, &data[i]);
    }

    int item = 7;
    test_printf("%d", item);
    test_assert(elist_index_of(list, &item, sizeof(int)) == 15);
    puts("");

    item = 3;
    test_printf("%d", item);
    test_assert(elist_index_of(list, &item, sizeof(int)) == 4);
    puts("");

    item = 99;
    test_printf("%d", item);
    test_assert(elist_index_of(list, &item, sizeof(int)) == 0);
    puts("");

    item = 45;
    test_printf("%d", item);
    test_assert(elist_index_of(list, &item, sizeof(int)) == 1);
    puts("");

    item = 110;
    test_printf("%d", item);
    test_assert(elist_index_of(list, &item, sizeof(int)) == -1);
    puts("");

    item = 1000000;
    test_printf("%d", item);
    test_assert(elist_index_of(list, &item, sizeof(int)) == -1);
    puts("");
 );

test_end
