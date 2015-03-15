all:
	gcc -c io.c -o io.o -fPIC
	gcc -c -std=c99 `pkg-config --libs --cflags gtk+-2.0` interpreter.c -o interpreter.o -fPIC
	gcc io.o interpreter.o -o zzi `pkg-config --libs --cflags gtk+-2.0`
