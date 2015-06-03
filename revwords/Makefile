all: clean lib revwords

lib:
	cd ../lib && make

revwords:
	gcc -std=c99 -Wall -I../lib -Wl,-rpath=../lib -L../lib revwords.c -o revwords -lhelpers

clean:
	rm -f revwords.o
	rm -f revwords
