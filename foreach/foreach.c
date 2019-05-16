#include <helpers.h>
#include <bufio.h>
#include <stdio.h>

int main(int argc, char ** argv) {
	
	char * re_argv[argc + 2];
	for(int i = 1; i < argc; i++) {
		re_argv[i - 1] = argv[i];
	}

	int cur_read;
	char buffer[4096];
	struct buf_t* buf = buf_new(4096);
	while((cur_read = buf_getline(STDIN_FILENO, buf, buffer))) {
		if(cur_read % 2 == 0) {
			re_argv[argc] = buffer;
			re_argv[argc + 1] = NULL;
			int spawn_result = spawn(re_argv[0], re_argv);
			if(spawn_result == 0) {
				buffer[cur_read] = '\n';
				write_(STDOUT_FILENO, buffer, cur_read + 1);
			}
		}
	}
	if(cur_read == -1) {
		printf("Error happend: %i", errno);
	}
	buf_free(buf);

	return 0;
}