#include "helpers.h"

ssize_t read_(int fd, void *buf, size_t count) {
	char *buffer = buf;
	int c;
	int i = 0;
	while((c = getchar()) != '\n' && i < count) {
		buffer[i] = c;
	}
	return i;
}

ssize_t write_(int fd, void *buf, size_t count) {
	return 0;
}

int main() {
	return 0;
}