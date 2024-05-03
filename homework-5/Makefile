all: main.o libmylib.a
	gcc main.o -lmylib -L./ -Iinclude -o main

main.o:
	cpp -Iinclude src/bin/main.c > main.i
	cc main.i -S
	as main.s -c -o main.o

libmylib.a:
	cpp src/mylib1.c > mylib1.i
	cc mylib1.i -S
	as mylib1.s -c -o mylib1.o
	cpp src/mylib2.c > mylib2.i
	cc mylib2.i -S
	as mylib2.s -c -o mylib2.o
	ar -r libmylib.a mylib1.o
	ar -r libmylib.a mylib2.o

clean:
	rm -rf main.i
	rm -rf main.s
	rm -rf main.o
	rm -rf main
	rm -rf main.i.004t.gimple
	rm -rf main.i.020t.ssa
	rm -rf main.i.229r.expand
	rm -rf main.i.310r.dfinish
	rm -rf mylib1.i
	rm -rf mylib1.s
	rm -rf mylib1.o
	rm -rf mylib2.i
	rm -rf mylib2.s
	rm -rf mylib2.o
	rm -rf libmylib.a
