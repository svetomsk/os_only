all: clean lib

lib:
	gcc -fPIC -c helpers.h helpers.c bufio.h bufio.c
	gcc -shared -o libhelpers.so helpers.o
	gcc -shared -o libbufio.so bufio.o helpers.o
clean:
	$(RM) helpers.o
	$(RM) libhelpers.so
	$(RM) helpers.h.gch
	$(RM) bufio.o
	$(RM) a.out
	$(RM) bufio.h.gch
	$(RM) libbufio.so