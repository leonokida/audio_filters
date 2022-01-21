/* GRR20190365 Leon Augusto Okida Goncalves */
#include <stdlib.h>
#include "wav.h"
#include "linhaComando.h"

int main(int argc, char *argv[]) {
    char *output;
    t_wav som;
    int flag_o;
    FILE * arqout;

    flag_o = entradaVolWide(argc, argv, &som, &output, WIDE);
    
    arqout = decideSaida(flag_o, output);

    encerraPrograma(&arqout, &som);
    exit(0);
}