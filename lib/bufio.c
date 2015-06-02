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
	while((cur_read = read(fd, buf->buf + total_result, buf->capacity)) > 0 && total_result < required) {
		total_result += cur_read;
	}

	if(cur_read == -1) {
		return -1;
	}
	buf->size = total_result;
	return total_result;
}

ssize_t buf_flush(fd_t fd, struct buf_t *buf, size_t required) {
	ssize_t cur_written;
	size_t total_result = 0;
	while((cur_written = write(fd, buf->buf, buf->size)) > 0) {
		total_result += cur_written;
		buf->size -= cur_written;
	}

	if(cur_written == -1) {
		return -1;
	}

	return total_result;
}

ssize_t buf_getline(fd_t fd, struct buf_t* buf, char* dest) {
	size_t cur_pos = 0;
	for(size_t i = 0; i < buf->size; i++, cur_pos++) {
		if(buf->buf[i] == '\n') {
			dest[cur_pos] = 0;
			return i;
		}
		dest[i] = buf->buf[i];
	}
	buf_free(buf);
	buf = buf_new(4096);

	ssize_t read = 0;
	while((read = buf_fill(fd, buf, 1)) > 0) {
		for(size_t i = 0; i < buf->size; i++, cur_pos++) {
			if(buf->buf[i] == '\n') {
				dest[cur_pos] = 0;
				return cur_pos;
			}				
			dest[cur_pos] = buf->buf[i];
		}			
		if(cur_pos > 4095) {
			exit(1);
		}
		buf_free(buf);
		buf = buf_new(4096);
	}
	if(read == -1) {
		return -1;
	}
	return cur_pos;
}