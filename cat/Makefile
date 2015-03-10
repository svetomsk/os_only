all: cat

cat:
ifeq ($(OS), Windows_NT)
	gcc -o cat.o -c -Wall -I../lib cat.c
	gcc -o cat.exe -L../lib -lhelpers cat.o
else ifeq ($(shell uname -s), Linux)
	gcc -std=c99 -I../lib -Wl,-rpath=../lib -L../lib cat.c -o cat -lhelpers
endif

clean:
ifeq ($(OS), Windows_NT)
	del cat.o
	del cat.exe
else ifeq ($(shell uname -s), Linux)
	rm -f cat.o
	rm -f cat
endif