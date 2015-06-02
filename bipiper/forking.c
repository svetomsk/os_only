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

static int sfd1, sfd2;
static struct sigaction old;

static void sigint_handler(int signal) {
	if(signal == SIGINT) {
		check(close(sfd1), "close");
		check(close(sfd2), "close");
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
		sfd1 = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

		if(sfd1 == -1) {
			continue; // not suitable
		}

		if(bind(sfd1, rp->ai_addr, rp->ai_addrlen) == 0) {
			break; // found
		}

		close(sfd1); // close current file descriptor because it is useless
	}

	if(rp == NULL) { // nothing was found
		printf("Binding failed");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(result); // no needed more
	check(listen(sfd1, 1), "listen");

	s = getaddrinfo(NULL, argv[2], &hints, &result);
	if(s != 0) {
		printf("%s\n", "Error in getaddrinfo happend");
		exit(EXIT_FAILURE);
	}
	// look thougn all returned address structures
	for(rp = result; rp != NULL; rp = rp->ai_next) {
		sfd2 = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

		if(sfd2 == -1) {
			continue; // not suitable
		}

		if(bind(sfd2, rp->ai_addr, rp->ai_addrlen) == 0) {
			break; // found
		}

		close(sfd2); // close current file descriptor because it is useless
	}

	if(rp == NULL) { // nothing was found
		printf("Binding failed");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(result); // no needed more
	check(listen(sfd2, 1), "listen");

	while(1) {
		//accept first client
		struct sockaddr_in client1;
		socklen_t len1 = sizeof(client1);
		printf("accepting first client...");
		int cfd1 = accept(sfd1, (struct sockaddr*)&client1, &len1);
		printf("accepted first client\n");

		//accept second client
		struct sockaddr_in client2;
		socklen_t len2 = sizeof(client2);
		printf("accepting second client...");
		int cfd2 = accept(sfd2, (struct sockaddr*)&client2, &len2);
		printf("accepted second client\n");

		pid_t pid1 = fork();
		if(pid1 == -1) {
			perror("pid1");
		}
		if(pid1 == 0) {
			close(sfd1);
			close(sfd2);
			while(1) {
				char reply[100];
				size_t r = read(cfd1, reply, sizeof(reply));
				if(r == -1) {
					perror("read1");
				}
				reply[r] = 0;
				printf("reply = %s\n", reply);
				//write to our own console message
				char current[r + 2];
				sprintf(current, "< %s\n", reply);
				write(cfd2, current, sizeof(current));
			}
			close(cfd1);
			close(cfd2);
			return 0;
		}
		pid_t pid2 = fork();
		if(pid2 == -1) {
			perror("pid2");
		}
		if(pid2 == 0) {
			close(sfd1);
			close(sfd2);
			while(1) {
				char reply[100];
				//read smth from another client
				size_t r = read(cfd2, reply, sizeof(reply));
				if(r == -1) {
					perror("read2");
				}
				reply[r] = 0;
				printf("reply = %s\n", reply);

				char current[r + 2];
				//write to our own console message
				sprintf(current, "< %s\n", reply);
				write(cfd1, current, sizeof(current));
			}
			close(cfd2);
			close(cfd1);
			return 0;
		}
	}
}