CC = gcc
CFLAGS = -I./AED_1

lista:
	$(CC) $(CFLAGS) -DLISTA main.c AED_2/grafoListaAdj.c AED_2/buscaGrafo.c AED_1/filas.c -o main

matriz:
	$(CC) $(CFLAGS) -DMATRIZ main.c grafoMatrizAdj.c buscaGrafo.c -o main

clean:
	rm -f *.o main