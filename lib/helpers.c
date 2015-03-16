#include "helpers.h"
#include "stdio.h"

ssize_t read_(int fd, void *buf, size_t count) {
	size_t result = 0;
	ssize_t cur_read;

	while(count > 0 && (cur_read = read(fd, buf + result, count)) > 0) {
		result += cur_read;
		count -= cur_read;
	}

	if(cur_read == -1) {
		return -1;
	}

	return result;
}

ssize_t read_until(int fd, void *buf, size_t count, char delimiter) {
	ssize_t cur_read;
	size_t result = 0;

	while(count > 0 && (cur_read = read(fd, buf + result, 1)) > 0) {
		char c = ((char *) buf)[result];
		if(c == delimiter) {
			break;
		}
		result++;
		count--;
	}

	if(cur_read == -1) {
		return -1;
	}

	return result;
}

ssize_t write_(int fd, void *buf, size_t count) {
	size_t result = 0;
	ssize_t cur_writen;

	while(count > 0 && (cur_writen = write(fd, buf + result, count)) > 0) {
		result += cur_writen;
		count -= cur_writen;
	}

	if(cur_writen == -1) {
		return -1;
	}

	return result;
}