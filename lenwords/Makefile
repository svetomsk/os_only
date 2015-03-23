all: lenwords

lenwords:
ifeq ($(OS), Windows_NT)
	gcc -o lenwords.o -c -Wall -I../lib lenwords.c
	gcc -o lenwords.exe -L../lib -lhelpers lenwords.o
else ifeq ($(shell uname -s), Linux)
	gcc -std=c99 -I../lib -Wl,-rpath=../lib -L../lib lenwords.c -o lenwords -lhelpers
endif

clean:
ifeq ($(OS), Windows_NT)
	del lenwords.o
	del lenwords.exe
else ifeq ($(shell uname -s), Linux)
	rm -f lenwords.o
	rm -f lenwords
endif