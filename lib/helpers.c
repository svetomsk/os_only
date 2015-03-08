#include "helpers.h"

ssize_t read_(int fd, void *buf, size_t count) {
	/* EBADF error */
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

	/* Handling error from getchar(). errno set by getchar() */
	if(ferror(stdin)) {
		return -1;
	}

	return i;
}

ssize_t write_(int fd, void *buf, size_t count) {
	/* EBADF error */
	if(fd != STDOUT_FILENO) {
		errno = EBADF;
		return -1;
	}

	const char *buffer = buf;
	ssize_t i = 0;

	while(i < count) {
		putchar(buffer[i++]);
	}

	/* Handling error from putchar(). errno set by putchar() */
	if(ferror(stdout)) {
		return -1;
	}

	return i;
}

int main() {
	char buf[3];
	int r = read_(STDIN_FILENO, buf, 3);
	if(r == -1)
		printf("%d",strerror(errno));

	int w = write_(STDOUT_FILENO, buf, 3);
	if(w == -1)
		printf("%d",strerror(errno));
	return 0;
}