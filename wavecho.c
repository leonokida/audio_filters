/* GRR20190365 Leon Augusto Okida Goncalves */
#include <stdlib.h>
#include "wav.h"
#include "linhaComando.h"

int main(int argc, char *argv[]) {
    char * output;
    int flag_o;
    FILE * arqout;
    t_wav som;

    flag_o = entradaWavecho(argc, argv, &som, &output);
    
    arqout = decideSaida(flag_o, output);

    encerraPrograma(&arqout, &som);
    exit(0);
}