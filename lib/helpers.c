#include "helpers.h"

ssize_t read_(int fd, void *buf, size_t count) {
	size_t result = 0;
	ssize_t cur_read;

	while(count > 0 && (cur_read = read(fd, buf + result, count)) > 0) {
		result += cur_read;
		count -= cur_read;
	}

	if(!feof(STDIN_FILENO) && count > 0) {
		return -1;
	}

	return result;
}

ssize_t write_(int fd, void *buf, size_t count) {
	return 0;
}

int main() {
	char buf[5];
	ssize_t r = read_(STDIN_FILENO, buf, 0);
	printf("%d\n", r);
	write(STDOUT_FILENO, buf, 5);
	return 0;
}