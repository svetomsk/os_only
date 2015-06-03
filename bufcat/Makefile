all: clean lib bufcat

lib:
	cd ../lib && make

bufcat:
	gcc -std=c99 -Wall -I../lib -Wl,-rpath=../lib -L../lib bufcat.c -o bufcat -lbufio

clean:
	rm -f bufcat.o
	rm -f bufcat
