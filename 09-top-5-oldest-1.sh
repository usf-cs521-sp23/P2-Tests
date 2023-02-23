source "${TEST_LIB}/funcs.bash"

run_timeout=10

reference_output=$(cd "${TEST_DIR}/inputs/test-fs"; \
    ${TEST_DIR}/scripts/das ./etc age | tail -n 5)

test_start "Checks the output against the test etc directory, limited to 3 lines sorted by oldest"

program_output=$(cd "${TEST_DIR}/inputs/test-fs"; ${TEST_DIR}/../da -a -l 5 ./etc)

compare_outputs

test_end
