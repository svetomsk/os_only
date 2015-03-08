#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

ssize_t read_(int fd, void *buf, size_t count);
ssize_t write_(int fd, void *buf, size_t count);