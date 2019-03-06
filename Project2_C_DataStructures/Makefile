# Nicu Razvan-Alexandru 313CB
build: tema2
tema2: main.o functii.o
	gcc -o tema2 $^ functii.h -g -Wall -lm
run:
	valgrind --leak-check=yes --track-origins=yes ./tema2 test01.in 1.out
functii.o: functii.c
	gcc -c functii.c
main.o: main.c
	gcc -c main.c
clean:
	rm -rf *.o tema2

