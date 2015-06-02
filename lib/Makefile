all: clean lib

lib:
	gcc -std=gnu99 -fPIC -Wall -c helpers.h helpers.c bufio.h bufio.c libhelpers.h libhelpers.c
	gcc -shared -o libhelpers.so helpers.o libhelpers.o
	gcc -shared -o libbufio.so bufio.o helpers.o
clean:
	$(RM) helpers.o
	$(RM) libhelpers.so
	$(RM) helpers.h.gch
	$(RM) bufio.o
	$(RM) a.out
	$(RM) bufio.h.gch
	$(RM) libbufio.so
	$(RM) libhelpers.h.gch
	$(RM) libhelpers.o
test:
	gcc -std=gnu99 -Wall tester.c libhelpers.h libhelpers.c
