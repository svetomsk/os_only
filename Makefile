all: lib/lib cat/cat revwords/revwords

lib/lib:
	cd lib && make

cat/cat:
	cd cat && make

revwords/revwords:
	cd revwords && make

clean:
	cd lib && make clean
	cd cat && make clean
	cd revwords && make clean