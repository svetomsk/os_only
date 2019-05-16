all: clean lib cat

lib:
	cd ../lib && make

cat:
	gcc -std=c99 -Wall -I../lib -Wl,-rpath=../lib -L../lib cat.c -o cat -lhelpers

clean:
	rm -f cat.o
	rm -f cat
