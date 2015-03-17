all: revwords

revwords:
ifeq ($(OS), Windows_NT)
	gcc -o revwords.o -c -Wall -I../lib revwords.c
	gcc -o revwords.exe -L../lib -lhelpers revwords.o
else ifeq ($(shell uname -s), Linux)
	gcc -std=c99 -I../lib -Wl,-rpath=../lib -L../lib revwords.c -o revwords -lhelpers
endif

clean:
ifeq ($(OS), Windows_NT)
	del revwords.o
	del revwords.exe
else ifeq ($(shell uname -s), Linux)
	rm -f revwords.o
	rm -f revwords
endif