all: lib

lib: clean
ifeq ($(OS), Windows_NT)
	gcc -c helpers.h helpers.c bufio.h bufio.c
	gcc -shared -o libhelpers.dll helpers.o
	gcc -shared -o libbufio.dll helpers.o bufio.o
else ifeq ($(shell uname -s), Linux)
	gcc -fPIC -c helpers.h helpers.c bufio.h bufio.c
	gcc -shared -o libhelpers.so helpers.o
	gcc -shared -o libbufio.so bufio.o helpers.o
endif

clean:
ifeq ($(OS), Windows_NT)
	del helpers.o
	del libhelpers.dll
	del helpers.h.gch
	del bufio.o
else ifeq ($(shell uname -s), Linux)
	$(RM) helpers.o
	$(RM) libhelpers.so
	$(RM) helpers.h.gch
	$(RM) bufio.o
	$(RM) a.out
	$(RM) bufio.h.gch
endif