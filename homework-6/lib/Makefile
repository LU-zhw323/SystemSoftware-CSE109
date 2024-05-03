static:
	g++ ../src/lib.cpp -c -I./
	ar rs liblinkedlist.a lib.o
	mkdir -p lib/build/lib/release
	mkdir -p lib/build/lib/object
	mv *o lib/build/lib/object
	mv *a lib/build/lib/release

shared:
	g++ ../src/lib.cpp -c -fpic -I./
	g++ -shared -o liblinkedlist.so lib.o
	mkdir -p lib/build/lib/release
	mkdir -p lib/build/lib/object
	mv *o lib/build/lib/object
	mv liblinkedlist.so lib/build/lib/release

debug:
	g++ ../src/lib.cpp -c -fpic -I./
	g++ -g -shared -o liblinkedlist.so lib.o
	mkdir -p lib/build/lib/debug
	mkdir -p lib/build/lib/object
	mv *o lib/build/lib/object
	mv liblinkedlist.so lib/build/lib/debug

clean:
	rm -rf lib
