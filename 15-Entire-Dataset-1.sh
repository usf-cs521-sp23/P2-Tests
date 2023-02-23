source "${TEST_LIB}/funcs.bash"

run_timeout=10

reference_output=$(cd "${TEST_DIR}/inputs/test-fs"; \
    ${TEST_DIR}/scripts/das ./)

test_start "Checks the output against the entire test dataset"

program_output=$(cd "${TEST_DIR}/inputs/test-fs"; ${TEST_DIR}/../da -s .)

compare_outputs

test_end
