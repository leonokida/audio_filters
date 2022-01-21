/* GRR20190365 Leon Augusto Okida Goncalves */
#ifndef __LINHA__
#define __LINHA__

#include "wav.h"

/*
Decide se entradaCatMix chama a funcao de concatenacao ou a de mixagem.
*/
typedef enum { CAT, MIX } opCatMix_t;
/*
Decide se entradaNormRev chama a funcao de normalizacao ou a de reversao.
*/
typedef enum { NORM, REV } opNormRev_t;
/*
Decide se entradaVolWide chama a funcao de ajuste de volume ou a de ampliacao do estereo.
*/
typedef enum { VOL, WIDE } opVolWide_t;

/*
Trata entrada dos filtros wavcat e wavmix. Altera os valores de som1 e output. Retorna um
int que sera usado para decidir o redirecionamento da saida do programa principal.
*/
int entradaCatMix(int argc, char * argv[], t_wav * som1, char ** output, opCatMix_t opcao);

/*
Trata entrada do filtro wavecho. Altera os valores de som e output. Retorna um
int que sera usado para decidir o redirecionamento da saida do programa principal.
*/
int entradaWavecho(int argc, char * argv[], t_wav * som, char ** output);

/*
Trata entrada de wavinfo.
*/
void entradaWavinfo(int argc, char *argv[], t_header * som);

/*
Trata entrada dos filtros wavnorm e wavrev. Altera os valores de som e output. Retorna um
int que sera usado para decidir o redirecionamento da saida do programa principal.
*/
int entradaNormRev(int argc, char *argv[], t_wav * som, char ** output, opNormRev_t opcao);

/*
Trata entrada dos filtros wavvol e wavwide. Altera os valores de som e output. Retorna um
int que sera usado para decidir o redirecionamento da saida do programa principal.
*/
int entradaVolWide(int argc, char *argv[], t_wav * som, char ** output, opVolWide_t op);

/*
Decide, com base no valor de flag, se as informacoes do tipo wav serao impressas
na saida padrao ou em um arquivo, cujo nome e passado por output.
*/
FILE * decideSaida(int flag, char * output);

/*
Escreve as informacoes do tipo wav no arquivo de saida, fecha o arquivo e libera a memoria alocada por wav.samples[].
*/
void encerraPrograma(FILE ** arqout, t_wav * som);

#endif