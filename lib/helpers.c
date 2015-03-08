#include "helpers.h"

ssize_t read_(int fd, void *buf, size_t count) {
	if(fd != STDIN_FILENO) {
		errno = EBADF;
		return -1;
	}

	char *buffer = buf;
	int c;
	ssize_t i = 0;
	while((c = getchar()) != EOF && i < count) {
		buffer[i] = c;
		i++;
	}

	return i;
}

ssize_t write_(int fd, void *buf, size_t count) {
	if(fd != STDOUT_FILENO) {
		errno = EBADF;
		return -1;
	}

	const char *buffer = buf;
	ssize_t i = 0;
	while(i < count) {
		putchar(buffer[i++]);
	}
	return i;
}

int main() {
	return 0;
}