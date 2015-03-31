all: clean bufcat

bufcat:
	gcc -std=c99 -I../lib -Wl,-rpath=../lib -L../lib bufcat.c -o bufcat -lbufio

clean:
	rm -f bufcat.o
	rm -f bufcat
