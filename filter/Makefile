all: clean filter

filter:
	gcc -std=c99 -I../lib -Wl,-rpath=../lib -L../lib filter.c -o filter -lhelpers

clean:
	rm -f filter.o
	rm -f filter
