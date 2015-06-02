#ifndef LIBHELPERS_
#define LIBHELPERS_
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

struct execargs_t {
	size_t argv;
	char * prog_name;
	char ** args;
};

struct execargs_t *execargs_new(size_t , char * , char *  []);
void execargs_free(struct execargs_t* v);
int exec(struct execargs_t* args);
int runpiped(struct execargs_t** programs, size_t n);

void test();

#endif // LIBHELPERS_
