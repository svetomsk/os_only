all: clean lib bipiper

lib:
	cd ../lib && make

bipiper:
	gcc -std=gnu99 -Wall -I../lib -Wl,-rpath=../lib -L../lib forking.c -o forking -lhelpers -lbufio

clean:
	rm -f forking.o
	rm -f forking
