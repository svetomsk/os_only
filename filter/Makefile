all: filter

filter:
ifeq ($(OS), Windows_NT)
	gcc -o filter.o -c -Wall -I../lib filter.c
	gcc -o filter.exe -L../lib -lhelpers filter.o
else ifeq ($(shell uname -s), Linux)
	gcc -std=c99 -I../lib -Wl,-rpath=../lib -L../lib filter.c -o filter -lhelpers
endif

clean:
ifeq ($(OS), Windows_NT)
	del filter.o
	del filter.exe
else ifeq ($(shell uname -s), Linux)
	rm -f filter.o
	rm -f filter
endif