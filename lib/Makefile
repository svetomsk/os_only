linux_flags = -fPIC -c
windows_flags = del
all:
	gcc helpers.h helpers.c

lib:
ifeq ($(shell uname -s), Linux)
	gcc -fPIC -c helpers.h helpers.c
	gcc -shared -o libhelpers.so helpers.o
else if($(OS), Windows_NT)
	gcc -c helpers.h helpers.c
	gcc -shared -o libhelpers.dll helpers.o
endif

clean:
	$(RM) helpers.o
	$(RM) libhelpers.dll
	$(RM) libhelpers.so
	$(RM) a.exe
	$(RM) a.out
	$(RM) helpers.h.gch