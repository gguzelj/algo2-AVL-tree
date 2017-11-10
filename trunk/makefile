# Especifica o compilador
CC      = gcc

# comandso compilador
CFLAGS  = -g -Wall

# Nombre executable
PROG  = programa

# LISTA ARCHIVOS PROGRAMA
OBJS  = main.o Cola.o constructor.o \
    lexico.o Lista.o ListaOrdenada.o \
    TAVL.o parser.o Pila.o \
    sintactico.o  diccionario.o \
    indice.o tokenizer.o buscador.o

all: $(PROG)

# COMPILACION PROGRAMA
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $*.c

#BORRAR ARCHIVOS .o
.Phony: clean
clean:
	rm -f $(OBJS)