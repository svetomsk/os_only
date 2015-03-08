#include "helpers.h"

ssize_t read_(int fd, void *buf, size_t count) {
	char *buffer = buf;
	int c;
	int i = 0;
	while((c = getchar()) != '\n' && i < count) {
		buffer[i] = c;
		i++;
	}
	return i;
}

ssize_t write_(int fd, void *buf, size_t count) {
	const char *buffer = buf;
	int i = 0;
	while(i < count) {
		putchar(buffer[i++]);
	}
	return i;
}

int main() {
	char buf[1];
	read_(STDIN_FILENO, buf, 2);
	write_(STDOUT_FILENO, buf, 2);
	return 0;
}