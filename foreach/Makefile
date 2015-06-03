all: clean lib foreach

lib:
	cd ../lib && make

foreach:
	gcc -std=c99 -Wall -I../lib -Wl,-rpath=../lib -L../lib foreach.c -o foreach -lbufio

clean:
	rm -f foreach.o
	rm -f foreach
