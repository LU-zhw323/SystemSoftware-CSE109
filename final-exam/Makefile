client: libpack109.a client.o
	g++ build/objects/release/client.o -o client -lpack109 -Lbuild/lib/release -std=c++11
	
	


server: libpack109.a server.o
	g++ build/objects/release/server.o -o server -lpack109 -Lbuild/lib/release -std=c++11

libpack109.a:
	g++ src/lib.cpp -c -Iinclude -std=c++11
	ar rs libpack109.a lib.o 
	mkdir -p build/lib/release
	mkdir -p build/objects/release
	mv *.o build/objects/release
	mv libpack109.a build/lib/release

server.o:
	g++ src/bin/server.cpp -c -lpack109 -Lbuild/lib/release -Iinclude -std=c++11
	mkdir -p build/objects/release
	mv server.o build/objects/release



client.o:
	g++ src/bin/client.cpp -c -lpack109 -Lbuild/lib/release -Iinclude -std=c++11
	mkdir -p build/objects/release
	mv client.o build/objects/release

clean:
	rm -f *.a
	rm -f *.o
	rm -rf build
	rm client
	rm server