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

static int sfd;
static struct sigaction old;

static void sigint_handler(int signal) {
	if(signal == SIGINT) {
		check(close(sfd), "close");
		check(sigaction(SIGINT, &old, NULL), "sigaction");
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

	struct addrinfo hints; // data for getaddrinfo()
	struct addrinfo *result, *rp; // results of getaddrinfo()
	int s; // descriptors

	if(argc != 3) {
		printf("Usage: %s port filename", argv[0]);
		exit(EXIT_FAILURE);
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; 
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	s = getaddrinfo(NULL, argv[1], &hints, &result);
	if(s != 0) {
		printf("%s\n", "Error in getaddrinfo happend");
		exit(EXIT_FAILURE);
	}
	// look thougn all returned address structures
	for(rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

		if(sfd == -1) {
			continue; // not suitable
		}

		if(bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0) {
			break; // found
		}

		close(sfd); // close current file descriptor because it is useless
	}

	if(rp == NULL) { // nothing was found
		printf("Binding failed");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(result); // no needed more
	check(listen(sfd, 1), "listen");

	while(1) {
		struct sockaddr_in client;
		socklen_t len = sizeof(client);
		printf("accepting...");
		int cfd = accept(sfd, (struct sockaddr*)&client, &len);
		printf("accepted");
		check(cfd, "accept");

		pid_t pid = fork();

		int file = open(argv[2], O_RDONLY);
		check(file, "open");

		if(pid == -1) {
			perror("fork");
		}
		if(pid == 0) {
			check(close(sfd), "close");
			struct buf_t* buf = buf_new(4096);
			ssize_t write;
			while((write = buf_fill(file, buf, 1)) > 0) {
				ssize_t res = buf_flush(cfd, buf, buf_size(buf));
				check(res, "flush");
			}
			check(write, "write");
			check(close(file), "close");

			return 0;
		} else {
			check(close(cfd), "close");
		}	
	}

	return 0;
}