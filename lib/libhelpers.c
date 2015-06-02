#include "libhelpers.h"

struct execargs_t* execargs_new(size_t size, char * name, char * args []) {
	struct execargs_t* cur = malloc(sizeof(struct execargs_t*));
	cur->argv = size;
	cur->prog_name = name;
	cur->args = args;
	return cur;
}

void check(int result, char * message) {
	if(result == -1) {
		perror(message);
		exit(EXIT_FAILURE);
	}
}

// perform exec in child process
// and return pid of process to 
// be able to control it
int exec(struct execargs_t* args) {
    pid_t pid = fork();

    if(pid == 0) {
    	// child process
		int result = execvp(args->prog_name, args->args);
		check(result, "exec failed");
    }
    return pid;
}

int runpiped(struct execargs_t** programs, size_t n) {
	int pipefd[2];
	int result;
	int stdin_fd = dup(STDIN_FILENO);
	check(stdin_fd, "dup2 error");
	int stdout_fd = dup(STDOUT_FILENO);
	check(stdout_fd, "dup2 error");
	int children[n];

	for(int i = 0; i < n; i++) {
		if(i != n - 1) { // if not last program 
			result = pipe(pipefd); // create pipe
			check(result, "pipe failed");
			result = dup2(pipefd[1], STDOUT_FILENO); // redirect output stream to pipe write end
			check(result, "dup2 failed");
			result = close(pipefd[1]); // close pipe end and leave only STDOUT_FILENO = pipefd[1]
			check(result, "close failed");
		} else { // last program don't have to write in pipe
			result = dup2(stdout_fd, STDOUT_FILENO); // restore STDOUT_FILENO
			check(result, "dup2 failed");
		}

		children[i] = exec(programs[i]); // run program and save child pid
		if(children[i] == -1) { 
			perror("exec failed");
			// TODO: stop process
		}

		if(i != n - 1) { // if not last program
			result = dup2(pipefd[0], STDIN_FILENO); // redirect intput stream to pipe read end
			check(result, "dup2 failed");
			result = close(pipefd[0]); // close pipe end and leave only STDIN_FILE = pipefd[0]
			check(result, "close failed");
		} else { // don't have to redirect STDIN_FILENO, but should close it
			result = close(STDIN_FILENO);
			check(result, "close failed");
		}
	}


	for(int i = 0; i < n; i++) {
		wait(NULL);
	}

	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);
	return 0;
}

void execargs_free(struct execargs_t* v) {
	free(v);
}
