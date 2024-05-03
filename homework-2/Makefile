all:
	mkdir build
	mkdir build/bin
	mkdir build/object
	mkdir build/lib
	gcc src/lib.c -c
	ar rs libmylib.a lib.o
	gcc src/bin/main.c -lmylib -L. -I include -o my_which
	mv lib.o build/object
	mv libmylib.a build/lib
	mv my_which build/bin




install:
	cp build/bin/my_which /usr/bin/my_which





clean:
	rm -r build
