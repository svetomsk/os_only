#include "bufio.h"
#include "helpers.h"

struct buf_t *buf_new(size_t capacity) {
	struct buf_t *temp = malloc(sizeof(struct buf_t*));
	temp->capacity = capacity;
	temp->size = 0;
	temp->buf = (char *) malloc(capacity);	
	return temp;
}

void buf_free(struct buf_t * b) {
	b->capacity = 0;
	b->size = 0;
	free(b->buf);
}

size_t buf_capacity(struct buf_t * b) {
	return b->capacity;
}

size_t buf_size(struct buf_t * b) {
	return b->size;
}

ssize_t buf_fill(fd_t fd, struct buf_t *buf, size_t required) {
	ssize_t cur_read;
	size_t total_result = 0;
	while((cur_read = read_(fd, buf->buf + total_result, buf->capacity)) > 0) {
		total_result += cur_read;
	}

	if(cur_read == -1) {
		printf("Error happened: %i\n", errno);
		return -1;
	}
	buf->size = total_result;
	return total_result;
}

ssize_t buf_flush(fd_t fd, struct buf_t *buf, size_t required) {
	ssize_t cur_written;
	size_t total_result = 0;
	while((cur_written = write_(fd, buf->buf, buf->size)) > 0) {
		total_result += cur_written;
		buf->size -= cur_written;
	}

	if(cur_written == -1) {
		printf("Error happened: %i\n", errno);
		return -1;
	}

	return total_result;
}

ssize_t buf_getline(fd_t fd, struct buf_t* buf, char* dest) {
	size_t cur_pos = 0;
	for(size_t i = 0; i < buf->size; i++, cur_pos++) {
		if(buf->buf[i] == '\n')
			return i;
		dest[i] = buf->buf[i];
	}
	buf_free(buf);
	buf = buf_new(4096);

	ssize_t read;
	while((read = buf_fill(fd, buf, 1)) > 0) {
		for(size_t i = 0; i < buf->size; i++, cur_pos++) {
			if(buf->buf[i] == '\n') {
				return cur_pos;
			}				
			dest[cur_pos] = buf->buf[i];
		}			
		buf_free(buf);
		buf = buf_new(4096);
	}
}