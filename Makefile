all: clean lib/lib cat/cat revwords/revwords filter/filter bufcat/bufcat foreach/foreach

lib/lib:
	cd lib && make

cat/cat:
	cd cat && make

revwords/revwords:
	cd revwords && make

filter/filter:
	cd filter && make

bufcat/bufcat:
	cd bufcat && make

foreach/foreach:
	cd foreach && make

simplesh/simplesh:
	cd simplesh && make

clean:
	cd lib && make clean
	cd cat && make clean
	cd revwords && make clean
	cd filter && make clean
	cd bufcat && make clean
	cd foreach && make clean