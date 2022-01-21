/* GRR20190365 Leon Augusto Okida Goncalves */
#include <stdlib.h>
#include "wav.h"
#include "linhaComando.h"

int main(int argc, char *argv[]) {
    char *output;
    t_wav som;
    FILE * arqout;
    int flag_o;

    flag_o = entradaCatMix(argc, argv, &som, &output, MIX);
    
    arqout = decideSaida(flag_o, output);

    encerraPrograma(&arqout, &som);
    exit(0);
}