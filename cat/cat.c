#include <errno.h>
#include <stdio.h>
#include <helpers.h>

int main() {
	char buffer[BUFSIZ];
	ssize_t current_read;

	do {
		current_read = read_(STDIN_FILENO, buffer, BUFSIZ);

		ssize_t w = write_(STDOUT_FILENO, buffer, current_read);

		if(w == -1 || current_read > w) {
			printf("Error %s", strerror(errno));
		}		
	} while(current_read == sizeof(buffer));

	return 0;
}