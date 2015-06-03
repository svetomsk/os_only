all: clean lib simplesh

lib:
	cd ../lib && make

simplesh:
	gcc -std=gnu99 -Wall -I../lib -Wl,-rpath=../lib -L../lib simplesh.c -o simplesh -lhelpers -lbufio

clean:
	rm -f simplesh.o
	rm -f simplesh
