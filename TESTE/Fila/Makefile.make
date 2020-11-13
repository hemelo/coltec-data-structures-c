all: fila

fila: main.o filaV.o filaLE.o filaDE.o
	gcc -o main main.o filaV.o filaLE.o filaDE.o

main.o: main.c
	gcc -o main.o main.c -c

filaV.o: filaV.c filaV.h
	gcc -o filaV.o filaV.c -c

filaLE.o: filaLE.c filaLE.h
	gcc -o filaLE.o filaLE.c -c

filaDE.o: filaDE.c filaDE.h
	gcc -o filaDE.o filaDE.c -c

clean:
	rm *.O