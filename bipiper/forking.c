#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <bufio.h>

#define BUF_SIZE 4096

void check(int result, char * message) {
	if(result == -1) {
		perror(message);
	}
}

static int sfd1, sfd2, cfd1, cfd2;
static struct sigaction old;

static void sigint_handler(int signal) {
	if(signal == SIGINT) {
		check(close(sfd1), "close");
		check(close(sfd2), "close");
		check(sigaction(SIGINT, &old, NULL), "sigaction");
		exit(0);
	}
}

void make_sfd(char * argument, int * fd) {
	struct addrinfo hints; // data for getaddrinfo()
	struct addrinfo *result, *rp; // results of getaddrinfo()
	int s; // descriptors

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; 
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	s = getaddrinfo(NULL, argument, &hints, &result);
	if(s != 0) {
		printf("%s\n", "Error in getaddrinfo happend");
		exit(EXIT_FAILURE);
	}
	// look thougn all returned address structures
	for(rp = result; rp != NULL; rp = rp->ai_next) {
		*fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

		if(*fd == -1) {
			continue; // not suitable
		}

		if(bind(*fd, rp->ai_addr, rp->ai_addrlen) == 0) {
			break; // found
		}

		check(close(*fd), "close"); // close current file descriptor because it is useless
	}

	if(rp == NULL) { // nothing was found
		printf("Binding failed");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(result); // no needed more
	check(listen(*fd, 1), "listen");
}

void accept_client(char * first, char * second, int * dest, int sfd) {
	printf("%s", first);
	*dest = accept(sfd, 0, 0);
	printf("%s", second);
}

void run_fork(int * cfd1, int * cfd2) {
	pid_t pid = fork();
	if(pid == -1) {
		perror("pid");
	}
	if(pid == 0) {
		check(close(sfd1), "close");
		check(close(sfd2), "close");
		while(1) {
			char reply[100];
			size_t r = read(*cfd1, reply, sizeof(reply));
			if(r == 0) { // nothing to read
				break;
			}
			if(r == -1) {
				perror("read1");
			}
			reply[r] = 0;
			//write to our own console message
			char current[r + 2];
			sprintf(current, "< %s\n", reply);
			size_t w = write(*cfd2, current, sizeof(current));
			if(w <= 0) {
				break;
			}
		}
		check(close(*cfd1), "close");
		check(close(*cfd2), "close");
		exit(0);
	}
}

int main(int argc, char * argv[]) {
	// set sigint handler in order to stop server by Ctrl+c correctly
	struct sigaction sa;
	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	check(sigaction(SIGINT, &sa, &old), "sigaction");

	if(argc != 3) {
		printf("Usage: %s port filename", argv[0]);
		exit(EXIT_FAILURE);
	}

	make_sfd(argv[1], &sfd1);
	make_sfd(argv[2], &sfd2);

	while(1) {
		accept_client("accepting first client...\n", "first client accepted\n", &cfd1, sfd1);
		accept_client("accepting second client...\n", "second client accepted\n", &cfd2, sfd2);
		run_fork(&cfd1, &cfd2);
		run_fork(&cfd2, &cfd1);
	}
	return 0;
}