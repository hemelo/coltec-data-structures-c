all: grafo

grafo: main.o filaLE.o listaLE.o pilhaLE.o grafoMA.o buscaMA.o grafoLA.o hash.o
	gcc -o main ./obj/main.o ./obj/filaLE.o ./obj/listaLE.o ./obj/pilhaLE.o ./obj/grafoMA.o ./obj/grafoLA.o ./obj/buscaMA.o ./obj/hash.o

main.o: ./source/main.c
	gcc -o ./obj/main.o ./source/main.c -c

filaLE.o: ./source/FILA/filaLE.c ./source/FILA/filaLE.h ./source/FILA/fila.h
	gcc -o ./obj/filaLE.o ./source/FILA/filaLE.c -c

listaLE.o: ./source/LISTA/listaLE.c ./source/LISTA/listaLE.h ./source/LISTA/lista.h
	gcc -o ./obj/listaLE.o ./source/LISTA/listaLE.c -c

pilhaLE.o: ./source/PILHA/pilhaLE.c ./source/PILHA/pilhaLE.h ./source/PILHA/pilha.h
	gcc -o ./obj/pilhaLE.o ./source/PILHA/pilhaLE.c -c

grafoMA.o: ./source/GRAFO/grafoMA.c ./source/GRAFO/grafoMA.h ./source/GRAFO/grafo.h
	gcc -o ./obj/grafoMA.o ./source/GRAFO/grafoMA.c -c

grafoLA.o: ./source/GRAFO/grafoLA.c ./source/GRAFO/grafoLA.h ./source/GRAFO/grafo.h
	gcc -o ./obj/grafoLA.o ./source/GRAFO/grafoLA.c -c

buscaMA.o: ./source/GRAFO/buscaMA.c ./source/GRAFO/buscaMA.h ./source/GRAFO/busca.h
	gcc -o ./obj/buscaMA.o ./source/GRAFO/buscaMA.c -c

hash.o: ./source/HASH/hash.c ./source/HASH/hash.h
	gcc -o ./obj/hash.o ./source/HASH/hash.c -c

clean:
	rm *.O