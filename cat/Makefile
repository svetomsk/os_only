all: clean cat

cat:
	gcc -std=c99 -I../lib -Wl,-rpath=../lib -L../lib cat.c -o cat -lhelpers

clean:
	rm -f cat.o
	rm -f cat
