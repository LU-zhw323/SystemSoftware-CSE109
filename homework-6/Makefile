test: test.o 
	g++ src/lib.cpp -c -Iinclude -Ilib
	ar rs liblhashset.a lib.o
	g++ test.o -o tester -Iinclude -Ilib
	mkdir -p build/bin/release
	mkdir -p build/lib/release
	mkdir -p build/objects
	mv *.o build/objects
	mv *.a build/lib/release
	mv tester build/bin/release/test

test.o: test/test.cpp
	g++ test/test.cpp -c -I include -I lib

static:
	g++ src/lib.cpp -c -Iinclude -Ilib
	ar rs liblhashset.a lib.o
	mkdir -p build/lib/release
	mkdir -p build/lib/object
	mv *o build/lib/object
	mv *a build/lib/release

shared:
	g++ src/lib.cpp -c -fpic -Iinclude -Ilib
	g++ -shared -o libhashset.so lib.o
	mkdir -p build/lib/release
	mkdir -p build/lib/object
	mv *o build/lib/object
	mv libhashset.so build/lib/release

debug:
	g++ src/lib.cpp -c -fpic -Iinclude -Ilib
	g++ -g -shared -o libhashset.so lib.o
	mkdir -p build/lib/debug
	mkdir -p build/lib/object
	mv *o build/lib/object
	mv liblhashset.so build/lib/debug

clean:
	rm -rf lib

install:
	mv build/lib/release/libhashset.so /user/lib
	mv build/lib/debug/libhashset.so /user/lib
