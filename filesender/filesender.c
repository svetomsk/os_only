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

int main(int argc, char * argv[]) {
	struct addrinfo hints; // data for getaddrinfo()
	struct addrinfo *result, *rp; // results of getaddrinfo()
	int sfd, s; // descriptors
	struct sockaddr_storage peer_addr;
	socklen_t nred;
	char buf[500];

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

		close(sfd); // close current file descriptor
	}

	if(rp == NULL) {
		printf("Binding failed");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(result);

	if(listen(sfd, 1) == -1) {
		perror("listen");
	}
	while(1) {
		printf("Inside");
		struct sockaddr_in client;
		socklen_t len = sizeof(client);
		printf("Accepting\n");
		int cfd = accept(sfd, (struct sockaddr*)&client, &len);
		printf("Accepted\n");
		pid_t pid = fork();
		if(pid == -1) {
			perror("fork");
		}
		if(pid == 0) {
			int file = open(argv[2], O_RDONLY);
			struct buf_t* buf = buf_new(4096);
			ssize_t read;
			while((read = buf_fill(file, buf, 1)) > 0) {
				buf_flush(cfd, buf, buf_size(buf));
			}
			if(read == -1) {
				perror("write");
			}
			close(file);
			close(cfd);
			printf("Sent\n");
			return 0;
		} else {
			printf("In parent");
		}	
	}

	close(sfd);

	return 0;
}