multiply_ptrs:
	gcc src/bin/multiply_ptrs.c -o multiply_ptrs

strlen.c:
	gcc src/bin/strlen.c -o my_strlen

argv.c:
	gcc src/bin/argv.c -o argv

all:
	mkdir build
	mkdir build/bin
	gcc src/bin/multiply_ptrs.c -o multiply_ptrs
	gcc src/bin/strlen.c -o my_strlen
	gcc src/bin/argv.c -o argv
	mv multiply_ptrs build/bin
	mv my_strlen build/bin
	mv argv build/bin

clean:
	rm -r build