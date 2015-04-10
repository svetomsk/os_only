all: clean foreach

foreach:
	gcc -std=c99 -I../lib -Wl,-rpath=../lib -L../lib foreach.c -o foreach -lbufio

clean:
	rm -f foreach.o
	rm -f foreach
