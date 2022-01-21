/* GRR20190365 Leon Augusto Okida Goncalves */
#include <stdlib.h>
#include "linhaComando.h"
#include "wav.h"

int main(int argc, char *argv[]) {
    char *output;
    t_wav som;
    int flag_o;
    FILE * arqout;

    flag_o = entradaNormRev(argc, argv, &som, &output, NORM);
    
    arqout = decideSaida(flag_o, output);

    encerraPrograma(&arqout, &som);
    exit(0);
}