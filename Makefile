all: lib/lib cat/cat

lib/lib:
	cd lib && make

cat/cat:
	cd cat && make

clean:
	cd lib && make clean
	cd cat && make clean