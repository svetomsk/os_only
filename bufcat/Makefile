all: bufcat

bufcat: clean
ifeq ($(OS), Windows_NT)
	gcc -o bufcat.o -c -Wall -I../lib bufcat.c
	gcc -o bufcat.exe -L../lib -lbufio bufcat.o
else ifeq ($(shell uname -s), Linux)
	gcc -std=c99 -I../lib -Wl,-rpath=../lib -L../lib bufcat.c -o bufcat -lbufio
endif

clean:
ifeq ($(OS), Windows_NT)
	del bufcat.o
	del bufcat.exe
else ifeq ($(shell uname -s), Linux)
	rm -f bufcat.o
	rm -f bufcat
endif