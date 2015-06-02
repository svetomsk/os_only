#include "libhelpers.h"

struct execargs_t* execargs_new(size_t size, char * name, char ** args) {
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

/* Perform exec in child process
 and return pid of process to 
 be able to control it
*/
int exec(struct execargs_t* args) {
    pid_t pid = fork();

    if(pid == 0) {
    	// child process
		check(execvp(args->prog_name, args->args), "exec failed");
		exit(0);
    }
    return pid;
}

static int * children;
static int count;
static int stdin_fd;
static int stdout_fd;

void stop_process() {
	for(int i = 0; i < count; i++) {
		if(children[i] != -1) { // if pid is valid
			kill(children[i], SIGKILL); // send SIGKILL
			waitpid(children[i], 0, 0);
			children[i] = -1;
		}
	}
	// restore old values of STDIN and STDOUT
	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdin_fd);
	close(stdout_fd);
}

int runpiped(struct execargs_t** programs, size_t n) {
	int pipefd[2];
	stdin_fd = dup(STDIN_FILENO);
	check(stdin_fd, "dup2 error");
	stdout_fd = dup(STDOUT_FILENO);
	check(stdout_fd, "dup2 error");
	int a[n];
	for(int i = 0; i < n; i++) {
		a[i] = -1;
	}
	children = a;
	count = n;

	for(int i = 0; i < n; i++) {
		if(i != n - 1) { // if not last program 			
			check(pipe(pipefd), "pipe failed"); // create pipe
			check(dup2(pipefd[1], STDOUT_FILENO), "dup2 failed"); // redirect output stream to pipe write end
			check(close(pipefd[1]), "close failed"); // close pipe end and leave only STDOUT_FILENO = pipefd[1]
		} else { // last program don't have to write in pipe
			check(dup2(stdout_fd, STDOUT_FILENO), "dup2 failed"); // restore STDOUT_FILENO
			check(close(stdout_fd), "close failed");
		}

		children[i] = exec(programs[i]); // run program and save child pid
		if(children[i] == -1) { 
			perror("exec failed");
			// TODO: stop process
		}

		if(i != n - 1) { // if not last program
			check(dup2(pipefd[0], STDIN_FILENO), "dup2 failed"); // redirect intput stream to pipe read end
			check(close(pipefd[0]), "close failed"); // close pipe end and leave only STDIN_FILE = pipefd[0]
		} else { // don't have to redirect STDIN_FILENO, but should close it
			check(close(STDIN_FILENO), "close failed");
		}
	}


	// wait for all children 
	for(int i = 0; i < n; i++) {
		wait(NULL);
	}

	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);	
	// restore STDIN and STDOUT descriptors
	return 0;
}

void execargs_free(struct execargs_t* v) {
	int index = 0;
	while((v->args)[index] != NULL) {
		free((v->args)[index]);
		index++;
	}
	free(v->args);
	free(v);
}
