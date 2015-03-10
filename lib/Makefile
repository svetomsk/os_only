all:
	gcc -std=c99 helpers.h helpers.c

lib:
ifeq ($(OS), Windows_NT)
	gcc -c helpers.h helpers.c
	gcc -shared -o libhelpers.dll helpers.o
else ifeq ($(shell uname -s), Linux)
	gcc -fPIC -c helpers.h helpers.c
	gcc -shared -o libhelpers.so helpers.o
endif

clean:
	del helpers.o
	del libhelpers.dll
	del libhelpers.so
	del a.exe
	del a.out
	del helpers.h.gch