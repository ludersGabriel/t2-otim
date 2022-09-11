# Variaveis
CFLAGS = -Wall -std=c++17
LDLIBS = 
CC = g++ 
OBJ = main.o bb.o

# regra default e ligação
all: elenco

elenco: $(OBJ)
	$(CC) -o elenco $(OBJ) $(LDLIBS)

# Regras de compilação

main.o: main.cpp bb.h
	$(CC) -c main.cpp $(CFLAGS)

bb.o: bb.cpp bb.h
	$(CC) -c bb.cpp $(CFLAGS)

# Regras de limpeza

clean: 
	-rm -f *.o

purge: clean
	-rm -f elenco