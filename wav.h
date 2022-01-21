/* GRR20190365 Leon Augusto Okida Goncalves */
#ifndef __WAV__
#define __WAV__

#include <stdint.h>
#include <stdio.h>

/*
Tipo que armazena informacoes do header do arquivo tipo WAVE.
*/
struct t_header {
    char ChunkID[4];
    uint32_t ChunkSize;
    char Format[4];

    char SubChunk1ID[4];
    uint32_t SubChunk1Size;
    uint16_t AudioFormat;
    uint16_t NumberOfChannels;
    uint32_t SampleRate;
    uint32_t ByteRate;
    uint16_t BlockAlign;
    uint16_t BitsPerSample;
    
    char SubChunk2ID[4];
    uint32_t SubChunk2Size;
};
typedef struct t_header t_header;

/*
Tipo que armazena o header, um vetor que armazena as amostras de audio e o numero total de amostras.
*/
struct t_wav {
    t_header header;
    int16_t *samples;
    uint32_t numberofsamples;
};
typedef struct t_wav t_wav;

/*
Funcao de abertura do arquivo para leitura.
*/
FILE * abreArqL(char ender[]);

/*
Funcao de abertura do arquivo para escrita.
*/
FILE * abreArqE(char ender[]);

/*
Le o header do arquivo de tipo WAVE e preenche um t_header.
*/
t_header leituraHeader(FILE * arq);

/*
Leitura do arquivo de tipo WAVE, preenchendo a struct t_wav.
*/
t_wav leitura(FILE * arq);

/*
Escrita em arquivo do tipo WAVE.
*/
void escrita(FILE * arq, t_wav wave);

#endif