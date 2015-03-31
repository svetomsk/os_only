all: clean revwords

revwords:
	gcc -std=c99 -I../lib -Wl,-rpath=../lib -L../lib revwords.c -o revwords -lhelpers

clean:
	rm -f revwords.o
	rm -f revwords
