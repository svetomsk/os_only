#include <helpers.h>
#include <stdio.h>

int main() {
	char buf[4096];
	ssize_t cur_read;
	char convert[20];
	while((cur_read = read_until(STDIN_FILENO, buf, 4096, ' ')) > 0) {
		int r = cur_read;
		if(cur_read == 1 && buf[0] == ' ') {
			sprintf(convert, " \n");
		} else {
			if(buf[cur_read - 1] == ' ')
				r--;
			sprintf(convert, "%d\n", r);
		}
		write_(STDOUT_FILENO, convert, 20);
	}
	return 0;
}