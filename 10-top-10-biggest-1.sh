source "${TEST_LIB}/funcs.bash"

run_timeout=10

reference_output=$(cd "${TEST_DIR}/inputs/test-fs"; \
    ${TEST_DIR}/scripts/das ./bin | tail -n 10)

test_start "Checks the output against the test bin directory, limited to 10 lines sorted by size"

program_output=$(cd "${TEST_DIR}/inputs/test-fs"; ${TEST_DIR}/../da -s -l 10 ./bin)

compare_outputs

test_end
