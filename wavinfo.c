/* GRR20190365 Leon Augusto Okida Goncalves */
#include "wav.h"
#include "linhaComando.h"

int main(int argc, char *argv[]) {
    t_header som;
    entradaWavinfo(argc, argv, &som);
    return 0;
}