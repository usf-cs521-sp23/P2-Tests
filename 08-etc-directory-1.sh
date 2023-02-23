source "${TEST_LIB}/funcs.bash"

run_timeout=10

reference_output=$(cd "${TEST_DIR}/inputs/test-fs"; ${TEST_DIR}/scripts/das ./etc)

test_start "Checks the output against the test etc directory"

program_output=$(cd "${TEST_DIR}/inputs/test-fs"; ${TEST_DIR}/../da ./etc)

compare_outputs

test_end
