all:	
ifeq ($(OS), Windows_NT)
	gcc -o cat.o -c -Wall -I../lib cat.c
	gcc -o cat.exe -L../lib -lhelpers cat.o
else ifeq ($(shell uname -s), Linux)
	gcc -o cat.o -fPIC -c -Wall -I../lib cat.c
	gcc -o cat -L../lib -Wl,-rpath=../lib -lhelpers cat.o
endif

clean:
ifeq ($(OS), Windows_NT)
	del cat.o
	del cat.exe
else ifeq ($(shell uname -s), Linux)
	rm -f cat.o
	rm -f cat
endif