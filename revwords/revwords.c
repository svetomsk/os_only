#include <helpers.h>
#include <stdio.h>
#include <errno.h>

void print_error() {
	printf("Error happend: %i", errno);
	_exit(1);
}

char * revbuffer(char * buf, ssize_t length) {
	size_t i = 0;
	while(i <= length/2) {
		char tmp = buf[i];
		buf[i] = buf[length - i];
		buf[length - i] = tmp;
		i++;
	}
	return buf;
}

int main() {
	ssize_t cur_read;
	char buf[4096];
	while((cur_read = read_until(STDIN_FILENO, buf, 10, ' ') > 0) {
		cur_read = read_until(STDIN_FILENO, buf, 10, ' ');
	 	ssize_t written = write_(STDOUT_FILENO, revbuffer(buf, cur_read - 1), cur_read);
	 	if(written == -1) {
	 		print_error();
	 	}
	}
	if(cur_read == -1) {
		print_error();
	}
	return 0;
}