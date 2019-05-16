all: clean lib filter

lib:
	cd ../lib && make

filter:
	gcc -std=c99 -Wall -I../lib -Wl,-rpath=../lib -L../lib filter.c -o filter -lhelpers

clean:
	rm -f filter.o
	rm -f filter
