
if [[ ! -e "${TEST_DIR}/inputs/test-fs" ]]; then
    echo "Extracting test file system..."
    tar -C "${TEST_DIR}/inputs" -xf "${TEST_DIR}/inputs/test-fs.tar.gz"
fi

touch -a -d '1 June 2014' "${TEST_DIR}/inputs/test-fs/etc/pacman.d/gnupg/pubring.gpg"
touch -a -d '27 November 1986'  "${TEST_DIR}/inputs/test-fs/etc/passwd"
touch -a -d '24 September 1957' "${TEST_DIR}/inputs/test-fs/etc/motd"
touch -a -d '24 September 1957' "${TEST_DIR}/inputs/test-fs/etc/arch-release"

