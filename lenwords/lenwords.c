#include <helpers.h>
#include <stdio.h>

int main() {
	char buf[4096];
	ssize_t cur_read;
	char convert[20];
	int offset = 0;
	while((cur_read = read_until(STDIN_FILENO, buf + offset, 4096, ' ')) > 0) {
		int r = cur_read;
		if(buf[cur_read - 1] == ' ') {
			r--;
			offset = 0;
		} else {
			offset += cur_read;
		}

		sprintf(convert, "%d\n", r);
		write_(STDOUT_FILENO, convert, 20);
	}
	return 0;
}