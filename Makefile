all: lib/lib cat/cat revwords/revwords lenwords/lenwords

lib/lib:
	cd lib && make

cat/cat:
	cd cat && make

revwords/revwords:
	cd revwords && make

lenwords/lenwords:
	cd lenwords && make

clean:
	cd lib && make clean
	cd cat && make clean
	cd revwords && make clean
	cd lenwords && make clean