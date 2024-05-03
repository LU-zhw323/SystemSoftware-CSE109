static:
	mkdir -p build/lib
	gcc src/insert.c src/remove.c src/lib.c src/rebalance.c src/find.c -c -Iinclude
	ar rs libbst.a insert.o remove.o lib.o rebalance.o find.o
	mv libbst.a build/lib

shared:
	mkdir -p build/lib
	gcc -c -fpic src/insert.c src/remove.c src/lib.c src/rebalance.c src/find.c -Iinclude
	gcc -shared -o libbst.so insert.o remove.o lib.o rebalance.o find.o
	mv libbst.so build/lib

bin: static
	
	mkdir -p build/bin
	mkdir -p build/object
	gcc src/bin/main.c -o main -lbst -Lbuild/lib -Iinclude
	mv *.o build/object
	mv main build/bin

all:
	mkdir -p build/lib
	mkdir -p build/bin
	mkdir -p build/object
	gcc -c -fpic src/insert.c src/remove.c src/lib.c src/rebalance.c src/find.c -Iinclude
	gcc -shared -o libbst.so insert.o remove.o lib.o rebalance.o find.o
	mv libbst.so build/lib
	mv *.o build/object
	gcc src/insert.c src/remove.c src/lib.c src/rebalance.c src/find.c -c -Iinclude
	ar rs libbst.a insert.o remove.o lib.o rebalance.o find.o 
	gcc src/bin/main.c -lbst -L. -Iinclude -o main
	mv libbst.a build/lib
	mv *.o build/object
	mv main build/bin

clean:
	rm -rf build

install:
	mv build/lib/libbst.so /user/lib


