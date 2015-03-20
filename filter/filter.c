#include <helpers.h>

void prepare_buffer(char * buf) {
	int i = 0;
	while(buf[i] != '\n') {
		i++;
	}
	buf[i] = 0;
}

int main(int argc, char ** argv) {
	char * re_argv[argc + 1];
	for(int i = 1; i < argc; i++) {
		re_argv[i - 1] = argv[i];
	}

	int cur_read;
	char buf[4096];
	while((cur_read = read_until(STDIN_FILENO, buf, 4096, '\n')) > 0) {	
		buf[cur_read] = 0;
		re_argv[argc - 1] = buf;
		re_argv[argc] = NULL;
		int spawn_result = spawn(re_argv[0], re_argv);
		if(spawn_result == 0) {
			buf[cur_read] = '\n';
			write(STDOUT_FILENO, buf, cur_read + 1);
		}

	}

	return 0;
}