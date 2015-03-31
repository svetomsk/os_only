#include <bufio.h>
#include <stdlib.h>
#include <stdio.h>
#include <helpers.h>

int main() {
	struct buf_t * current = buf_new(4096);
	ssize_t read = buf_fill(STDIN_FILENO, current, buf_capacity(current));
	char buf[20];
	if(read == -1) {
		int put = sprintf(buf, "Error happend in reading: %u\n", errno);
		write_(STDOUT_FILENO, buf, put);
	}
	ssize_t writen = buf_flush(STDOUT_FILENO, current, buf_size(current));
	if(writen == -1) {
		int put = sprintf(buf, "Error happend in writing: %u\n", errno);
		write_(STDOUT_FILENO, buf, put);
	}
	return 0;
}