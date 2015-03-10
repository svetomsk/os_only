all: lib

lib:
ifeq ($(OS), Windows_NT)
	gcc -c helpers.h helpers.c
	gcc -shared -o libhelpers.dll helpers.o
else ifeq ($(shell uname -s), Linux)
	gcc -fPIC -c helpers.h helpers.c
	gcc -shared -o libhelpers.so helpers.o
endif

clean:
ifeq ($(OS), Windows_NT)
	del helpers.o
	del libhelpers.dll
	del helpers.h.gch
else ifeq ($(shell uname -s), Linux)
	$(RM) helpers.o
	$(RM) libhelpers.so
	$(RM) helpers.h.gch
endif