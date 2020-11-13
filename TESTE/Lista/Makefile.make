all: lista

lista: main.o listaES.o
	gcc -o main main.o listaES.o 

main.o: main.c
	gcc -o main.o main.c -c

listaES.o: listaES.c listaES.h
	gcc -o listaES.o listaES.c -c

clean:
	rm *.O