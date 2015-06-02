#include "libhelpers.h"

struct execargs_t* execargs_new(size_t size, char * name, char * args []) {
	struct execargs_t* cur = malloc(sizeof(struct execargs_t*));
	cur->argv = size;
	cur->prog_name = name;
	cur->args = args;
	return cur;
}

// perform exec in child process
// and return pid of process to 
// be able to control it
int exec(struct execargs_t* args) {
    pid_t pid = fork();
    if(pid == -1) {
    	perror("fork failed");
    	exit(EXIT_FAILURE);
    }
    if(pid == 0) {
    	// child process
		int result = execvp(args->prog_name, args->args);
    	if(result == -1) {
    		perror("exec failed");
    		exit(EXIT_FAILURE);
    	}
    }
    return pid;
}

int runpiped(struct execargs_t** programs, size_t n) {
	int pipefd[2];
	for(int i = 0; i < n; i++) {
		if(pipe(pipefd) == -1) {
			perror("pipe creation failed");
			exit(EXIT_FAILURE);
		}

		dup2(pipefd[1], STDOUT_FILENO); // redirect output stream to pipe write end

		close(pipefd[1]); // close pipe end and leave only STDOUT_FILENO = pipefd[1]
		if(exec(programs[i]) == -1) { // run program 
			perror("exec failed");
			// TODO: stop process
		}
		
		dup2(pipefd[0], STDIN_FILENO); // redirect intput stream to pipe read end
		close(pipefd[0]); // close pipe end and leave only STDIN_FILENO = pipefd[0]
	}
}

void execargs_free(struct execargs_t* v) {
	free(v);
}
