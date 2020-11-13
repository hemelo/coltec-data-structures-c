all: pilha

pilha: main.o pilhaV.o pilhaES.o
	gcc -o main.o pilhaV.o pilhaES.o -o pilha


main.o: main.c
	gcc -c main.c

pilhaV.o: pilhaV.c pilhaV.h
	gcc -c pilhaV.c

pilhaES.o: pilhaES.c pilhaES.h
	gcc -c pilhaES.c

clean:
	rm *.o

