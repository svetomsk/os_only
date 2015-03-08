RM = del

all:
	gcc helpers.h helpers.c

lib:
	gcc -c helpers.h helpers.c
ifeq ($(OS), Windows_NT)
	gcc -shared -o libhelpers.dll helpers.o
else
	gcc -shared -o libhelpers.so helpers.o
endif

clean:
ifeq ($(OS), Linux)
	RM = rm -f
endif

	$(RM) helpers.o
	$(RM) libhelpers.dll
	$(RM) libhelpers.so
	$(RM) a.exe
	$(RM) helpers.h.gch