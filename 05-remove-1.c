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

test_start("Tests the remove function");

subtest("Creates a list, then removes elements from the front, back, and middle.",
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

    int *item = elist_get(list, 0);
    test_assert(*item == 99);
    test_printf("%d", *item);

    elist_remove(list, 0);
    item = elist_get(list, 0);
    test_assert(*item == 45);
    test_printf("%d", *item);
    puts("");

    /* Invalid item */
    puts("Removing invalid item");
    int status = elist_remove(list, 22);
    test_assert(status == -1);

    /* Last item */
    status = elist_remove(list, 14);
    test_assert(status == 0);
    item = elist_get(list, 13);
    test_printf("%d", *item);
    test_assert(*item == 370281);

    /* Remove second to last item */
    status = elist_remove(list, 12);
    test_assert(status == 0);
    item = elist_get(list, 12);
    test_printf("%d", *item);
    test_assert(*item == 370281);

    puts("\n");
    puts("Removing all elements by removing item 0 multiple times");
    for (int i = 0; i < 12; ++i) {
        int status = elist_remove(list, 0);
        test_assert(status == 0);
    }

    printf("List size: %zu\n", elist_size(list));
    test_assert(elist_size(list) == 1);

    status = elist_remove(list, 0);
    test_assert(status == 0);

    /* List should now be empty */
    status = elist_remove(list, 0);
    test_assert(status == -1);
);

test_end
