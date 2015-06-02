#include <bufio.h>
#include <helpers.h>
#include <libhelpers.h>
#include <string.h>

int split(char separator, const char* sequance, size_t length, char ** array) {
	int cur = 0;
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
	return count;
}

int main() {
	char * s = "$";
	char * test = "find /home/svetomsk/os_only/lib| grep a| head";
	struct execargs_t* programs[strlen(test)/2 + 1];
	int count = parse_string(test, programs);
	printf("Count = %d\n", count);
	int result = runpiped(programs, 3);
	printf("Runpiped result = %d\n", result);
	// while(1) {
	// 	write(STDOUT_FILENO, s, 1);
	// 	char buffer[4096];
	// 	struct buf_t* buf = buf_new(4096);
	// 	ssize_t read = buf_getline(STDIN_FILENO, buf, buffer);
	// 	printf("Read: %s\n", buffer);
	// }
	return 0;
}