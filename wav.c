/* GRR20190365 Leon Augusto Okida Goncalves */
#include "wav.h"
#include <stdlib.h>

FILE * abreArqL(char ender[]) {
    FILE * arq = fopen(ender, "r");

    if (!arq) {
        /* Arquivo apontado nao existe */
        fprintf(stderr, "Arquivo nao encontrado\n");
        exit(1);
    }

    return arq;
}

FILE * abreArqE(char ender[]) {
    FILE * arq = fopen(ender, "w");

    if (!arq) {
        /* Arquivo apontado nao existe */
        fprintf(stderr, "Arquivo %s nao encontrado\n", ender);
        exit(1);
    }

    return arq;
}

t_header leituraHeader(FILE * arq) {
    t_header header;
    int sucesso;
    sucesso = fread(&header, sizeof(t_header), 1, arq);
    if (sucesso)
        return header;
    else {
        fprintf(stderr, "Erro ao ler arquivo\n");
        fclose(arq);
        exit(1);
    }
}

t_wav leitura(FILE * arq) {
    t_wav info;

    /* Leitura do header. */
    info.header = leituraHeader(arq);

    /* Leitura de samples[] e calculo de numberofsamples. */
    info.samples = malloc(info.header.SubChunk2Size);
    if (info.samples == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        fclose(arq);
        exit(1);
    }
    info.numberofsamples = info.header.SubChunk2Size / sizeof(int16_t);
    uint32_t i;
    int sucesso;
    for (i = 0; i < info.numberofsamples; i++) {
        sucesso = fread(&info.samples[i], sizeof(int16_t), 1, arq);
        if (!sucesso) {
            fprintf(stderr, "Erro ao ler arquivo\n");
            free(info.samples);
            fclose(arq);
            exit(1);
        }
    }

    return info;
}

void escrita(FILE * arq, t_wav wave) {
    int sucesso;
    sucesso = fwrite(&wave.header, sizeof(t_header), 1, arq);
    if (!sucesso) {
        fprintf(stderr, "Erro ao escrever no arquivo\n");
            free(wave.samples);
            fclose(arq);
            exit(1);
    }
    sucesso = fwrite(wave.samples, sizeof(int16_t), wave.numberofsamples, arq);
    if (!sucesso) {
        fprintf(stderr, "Erro ao escrever no arquivo\n");
            free(wave.samples);
            fclose(arq);
            exit(1);
    }
}