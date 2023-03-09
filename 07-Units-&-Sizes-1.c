#if 0
    source "${TEST_LIB}/crunner" -lda
#endif

#include <limits.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "util.h"

test_start("Tests human_readable_size and simple_time_format functions.");

subtest("Comparing output against known size values",
{
    char buf[128];
    human_readable_size(buf, 128, 0, 1);
    test_assert_str(buf, "==", "0.0 B", 128);
    test_printf("%s\n", buf);

    human_readable_size(buf, 128, 0, 0);
    test_assert_str(buf, "==", "0 B", 128);
    test_printf("%s\n", buf);

    human_readable_size(buf, 128, 1023, 1);
    test_assert_str(buf, "==", "1023.0 B", 128);
    test_printf("%s\n", buf);

    human_readable_size(buf, 128, 1024, 8);
    test_assert_str(buf, "==", "1.00000000 KiB", 128);
    test_printf("%s\n", buf);

    human_readable_size(buf, 128, 34359738367, 1);
    test_assert_str(buf, "==", "32.0 GiB", 128);
    test_printf("%s\n", buf);

    human_readable_size(buf, 128, 2844524, 1);
    test_assert_str(buf, "==", "2.7 MiB", 128);
    test_printf("%s\n", buf);

    human_readable_size(buf, 128, 129049729231119, 2);
    test_assert_str(buf, "==", "117.37 TiB", 128);
    test_printf("%s\n", buf);

    human_readable_size(buf, 128, 1290497239231119, 3);
    test_assert_str(buf, "==", "1.146 PiB", 128);
    test_printf("%s\n", buf);

    human_readable_size(buf, 128, 112030000000000000, 1);
    test_assert_str(buf, "==", "99.5 PiB", 128);
    test_printf("%s\n", buf);

});

subtest("Comparing output against known time values",
{
    char buf[128];
    simple_time_format(buf, 128, 0);
    test_assert_str(buf, "==", "Dec 31 1969", 128);
    test_printf("%s\n", buf);

    simple_time_format(buf, 128, 1646455768);
    test_assert_str(buf, "==", "Mar 04 2022", 128);
    test_printf("%s\n", buf);

    simple_time_format(buf, 128, 533472040);
    test_assert_str(buf, "==", "Nov 27 1986", 128);
    test_printf("%s\n", buf);

    simple_time_format(buf, 128, 9533472040);
    test_assert_str(buf, "==", "Feb 07 2272", 128);
    test_printf("%s\n", buf);

    simple_time_format(buf, 128, 936893349);
    test_assert_str(buf, "==", "Sep 09 1999", 128);
    test_printf("%s\n", buf);

    simple_time_format(buf, 128, 1122829270);
    test_assert_str(buf, "==", "Jul 31 2005", 128);
    test_printf("%s\n", buf);

});


test_end
