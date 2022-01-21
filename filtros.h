/* GRR20190365 Leon Augusto Okida Goncalves */
#ifndef __FILTROS__
#define __FILTROS__

#include "wav.h"

#define MAX 32767
#define MIN -32767

/*
Retorna 1 se arquivo for do tipo WAVE, 0 se nao for.
*/
int testaWave(t_wav * wav);

/*
Concatena o vetor samples[] do segundo t_wav ao final do vetor do primeiro.
*/
void concatenacao(t_wav * wav1, t_wav * wav2);

/*
Trata o vetor de samples para que o som tenha eco.
*/
void echo(t_wav * wave, float level, float delay);

/*
Escreve as informacoes de t_header em stderr.
*/
void escreve(t_header som);

/*
Soma os elementos dos vetores samples[] das structs e armazena em wav1.samples[].
*/
void mix(t_wav * wav1, t_wav * wav2);

/*
Encontra um fator, que consiste em 32767 divido pelo maior elemento do vetor samples[].
Em seguida, multiplica todos os elementos do vetor samples[] por esse valor.
*/
void normaliza(t_wav * wave);

/*
Inverte o vetor samples[].
*/
void reversao(t_wav * wave);

/*
Multiplica todos os elementos do vetor samples[] por valor.
*/
void multiplica(t_wav * wave, float valor);

/*
Aumenta a diferenca entre os canais, por meio das equacoes:
diff = R[t] - L[t]
R'[t] = R[t] + k * diff
L'[t] = L[t] - k * diff
*/
void amplia(t_wav * wave, float k);

#endif