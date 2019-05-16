#include <helpers.h>
#include <stdio.h>
#include <errno.h>

void print_error() {
	printf("Error happend: %i", errno);
	_exit(1);
}

int main() {
	char buf[4096];
	ssize_t cur_read;
	char convert[20];
	int written = 0;
	while(1) {
		cur_read = read_until(STDIN_FILENO, buf, 4096, ' ');
		if(cur_read == -1) {
			print_error();
		}
		if(cur_read > 0) {
			int r = cur_read;
			if(buf[cur_read - 1] == ' ')
				r--;
			written = sprintf(convert, "%d\n", r);
			ssize_t result = write_(STDOUT_FILENO, convert, written);
			if(result == -1) {
				print_error();
			}
		} else {
			break;
		}
	}
	return 0;
}