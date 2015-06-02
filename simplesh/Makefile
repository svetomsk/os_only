all: clean simplesh

simplesh:
	gcc -std=gnu99 -I../lib -Wl,-rpath=../lib -L../lib simplesh.c -o simplesh -lhelpers -lbufio

clean:
	rm -f simplesh.o
	rm -f simplesh
