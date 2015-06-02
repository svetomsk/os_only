all: clean filesender

filesender:
	gcc -std=gnu99 -I../lib -Wl,-rpath=../lib -L../lib filesender.c -o filesender -lhelpers -lbufio

clean:
	rm -f filesender.o
	rm -f filesender