.PHONY: clean

points: points-program.o points-aux.o point.o
	gcc -o points points-program.o points-aux.o point.o

points-program.o: points-program.c point.h
	gcc -o points-program.o -c points-program.c

points-aux.o: points-aux.c point.h
	gcc -o points-aux.o -c points-aux.c

point.o: point.c point.h
	gcc -o point.o -c point.c

clean:
	rm -f *.o points
