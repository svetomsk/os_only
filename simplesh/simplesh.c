#include <bufio.h>
#include <helpers.h>
#include <libhelpers.h>
#include <string.h>

int split(char separator, const char* sequance, size_t length, char ** array) {
	int index = 0;
	int count = 0;
	char buffer[length];
	for(size_t i = 0; i < length; i++) {
		if(sequance[i] != separator) {
			buffer[index] = sequance[i];
			index++;
		} else {
			if(index != 0) {
				buffer[index] = 0;
				array[count] = malloc(index * sizeof(char));
				strcpy(array[count], buffer);
				index = 0;
				count++;
			}
		}
	}

	if(index != 0) {
		buffer[index] = 0;
		array[count] = malloc(index * sizeof(char));
		strcpy(array[count], buffer);
		count++;
	}
	return count;
}

int parse_string(char * str, struct execargs_t* programs[]) {
	char ** array = malloc((strlen(str)/2 + 1) * sizeof(char *));
	int count = split('|', str, strlen(str), array);

	for(size_t i = 0; i < count; i++) {
		int len = strlen(array[i]);
		char ** mas = malloc((len/2 + 1) * sizeof(char*));
		int cnt = split(' ', array[i], len, mas);
		mas[cnt] = NULL;
		programs[i] = execargs_new(1, mas[0], mas);
		free(array[i]);
	}
	free(array);
	return count;
}

static struct sigaction old;

static void sigint_handler(int signal) {
	if(signal == SIGINT) {
		char * s = "\n";
		write(STDOUT_FILENO, s, strlen(s));
	}
}

int main() {
	char * s = "$";
	//set handler for SIGINT
	struct sigaction sa;
	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, &old);

	while(1) {
		write(STDOUT_FILENO, s, 1);
		char * buffer = malloc(4096 * sizeof(char));
		struct buf_t* buf = buf_new(4096);
		ssize_t read = buf_getline(STDIN_FILENO, buf, buffer);
		if(read == -1) {
			free(buffer);
			buf_free(buf);
			continue;
		}
		if(read == 0) {
			break;
		}
		struct execargs_t* programs[read/2 + 1];
		int count = parse_string(buffer, programs);
		runpiped(programs, count);
		for(int i = 0; i < count; i++) {
			execargs_free(programs[i]);
		}
		free(buffer);
		buf_free(buf);
	}

	sigaction(SIGINT, &old, 0);
	return 0;
}