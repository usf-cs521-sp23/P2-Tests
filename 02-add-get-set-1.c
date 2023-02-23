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

int sum_elist(struct elist *list)
{
    int total = 0;
    for (int i = 0; i < elist_size(list); ++i) {
        int *num = elist_get(list, i);
        total += *num;
    }
    return total;
}

test_start("Tests adding and retrieving elements.");

subtest("Adding and retrieving a large amount of integers",
{
    struct elist *list = elist_create(10);
    test_assert(list != NULL);

    /* Add 100,000 elements. */
    for (int i = 0; i <= 100000; ++i) {
        /* Each element is an array of 5 ints.
         * The first 4 ints are random numbers, and
         * the last int contains the sum of the first
         * four numbers (allowing us to verify
         * correctness) */
        int *nums = malloc(sizeof(int) * 5);
        int total = 0;
        for (int j = 0; j < 4; ++j) {
            nums[j] = random() % 100;
            total += nums[j];
        }
        nums[4] = total;
        elist_add(list, nums);
    }

    for (int i = 0; i < 100000; ++i) {
        int *nums = elist_get(list, i);
        int total = 0;
        for (int j = 0; j < 4; ++j) {
            total += nums[j];
        }
        /* Sorry for spamming the output... */
        test_printf("%d\n", total);
        test_assert(total == nums[4]);
    }

    elist_destroy(list);
});

subtest("Testing set()",
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
        4040,
        4,
        1,
        2,
        370281,
        7
    };

    struct elist *list = elist_create(20);
    for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
        int *item = malloc(sizeof(int));
        *item = data[i];
        elist_add(list, item);
    }

    int total = sum_elist(list);
    test_printf("%d", total);
    test_assert(total == 384704);
    puts("");

    int *num1 = malloc(sizeof(int));
    *num1 = 0;
    elist_set(list, 14, num1);
    elist_set(list, 7, num1);
    total = sum_elist(list);
    test_printf("%d", total);
    test_assert(total == 4424);
    puts("");

    int *num2 = malloc(sizeof(int));
    *num2 = 10;
    elist_set(list, 10, num2);
    elist_set(list, 9, num2);
    total = sum_elist(list);
    test_printf("%d", total);
    test_assert(total == 364);
    puts("");

    /* Set everything to 'i' */
    for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
        int *item = malloc(sizeof(int));
        *item = i;
        elist_set(list, i, item);
    }
    total = sum_elist(list);
    test_printf("%d", total);
    test_assert(total == 120);
    puts("");

    /* Set everything to 0 */
    int *num3 = malloc(sizeof(int));
    *num3 = 0;
    for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
        elist_set(list, i, num3);
    }
    total = sum_elist(list);
    test_printf("%d", total);
    test_assert(total == 0);
    puts("");

    elist_destroy(list);
);

subtest("Testing invalid set()",
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
        4040,
        4,
        1,
        2,
        370281,
        7
    };

    struct elist *list = elist_create(20);
    for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
        int *item = malloc(sizeof(int));
        *item = data[i];
        elist_add(list, item);
    }

    int num = 10;
    test_assert(elist_set(list, 5, &num) == 0);
    test_assert(elist_set(list, 0, &num) == 0);
    test_assert(elist_set(list, 592, &num) == -1);
    test_assert(elist_set(list, 300, &num) == -1);
    test_assert(elist_set(list, 16, &num) == -1);
    test_assert(elist_set(list, 20, &num) == -1);

    elist_destroy(list);
);

test_end
