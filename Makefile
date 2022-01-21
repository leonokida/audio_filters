# GRR20190365 Leon Augusto Okida Goncalves

#Variaveis
CFLAGS = -Wall
OBJS = wav.o filtros.o linhaComando.o

all: wavcat wavecho wavinfo wavmix wavnorm wavrev wavvol wavwide

# Ligacao
wavcat: $(OBJS)
wavecho: $(OBJS)
wavinfo: $(OBJS)
wavmix: $(OBJS)
wavnorm: $(OBJS)
wavrev: $(OBJS)
wavvol: $(OBJS)
wavwide: $(OBJS)

# Regras de compilacao
wav.o: wav.c wav.h

filtros.o: filtros.c filtros.h wav.h

linhaComando.o: linhaComando.c linhaComando.h filtros.h wav.h

# Clean e purge
clean:
		-rm -f *~ $(OBJS)

purge: clean
		-rm -f wavcat wavecho wavinfo wavmix wavnorm wavrev wavvol wavwide