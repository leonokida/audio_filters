/* GRR20190365 Leon Augusto Okida Goncalves */
#include "filtros.h"
#include <stdlib.h>

int testaWave(t_wav * wav) {
    return ((wav->header.Format[0] == 'W') && (wav->header.Format[1] == 'A') && (wav->header.Format[2] == 'V') && (wav->header.Format[3] == 'E'));
}

void concatenacao(t_wav * wav1, t_wav * wav2) {
    /* Atualiza informacoes do header para novo tamanho. */
    wav1->header.SubChunk2Size = wav1->header.SubChunk2Size + wav2->header.SubChunk2Size;
    wav1->header.ChunkSize = wav1->header.ChunkSize + wav2->header.ChunkSize;

    wav1->samples = (int16_t *)realloc(wav1->samples, wav1->header.SubChunk2Size);
    if (wav1->samples == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(1);
    }
    int i;
    for (i = wav1->numberofsamples; i < wav1->numberofsamples + wav2->numberofsamples; i++)
        wav1->samples[i] = wav2->samples[i - wav1->numberofsamples];

    wav1->numberofsamples = wav1->numberofsamples + wav2->numberofsamples;
}

/*
Aumenta o tamanho da struct para que o arquivo tenha mais delay milissegundos de duracao. Zera os novos elementos do vetor expandido com realloc.
Altera os valores de ChunkSize, SubChunk2Size e numberofsamples para corresponder ao novo tamanho do arquivo.
*/
static void trataStruct(t_wav * wave, float level, float delay, uint32_t indexDelay) {

    wave->header.ChunkSize = wave->header.ChunkSize + indexDelay * sizeof(int16_t);
    wave->header.SubChunk2Size = wave->header.SubChunk2Size + indexDelay * sizeof(int16_t);
    uint32_t tamanho = wave->header.SubChunk2Size / sizeof(int16_t);

    wave->samples = (int16_t *)realloc(wave->samples, wave->header.SubChunk2Size);
    if (wave->samples == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(1);
    }
    int i;
    for (i = wave->numberofsamples; i < tamanho; i++)
        wave->samples[i] = 0;

    wave->numberofsamples = tamanho;
}

void echo(t_wav * wave, float level, float delay) {
    uint32_t indexDelay = wave->header.SampleRate / 1000 * delay; /* Calcula indice de inicio de delay */
    trataStruct(wave, level, delay, indexDelay);

    uint32_t i;
    int32_t novo;
    for (i = indexDelay; i < wave->numberofsamples; i++) {
        novo = wave->samples[i] + (level * wave->samples[i - indexDelay]); /* sample[t] = sample[t] + (level * sample[t - delay]) */
        /* Testa se estoura limites */
        if ((novo <= MAX) && (novo >= MIN))
            wave->samples[i] = novo;
    }
}

void escreve(t_header som) {
    fprintf(stderr, "riff tag: \"%c%c%c%c\"\n", som.ChunkID[0], som.ChunkID[1], som.ChunkID[2], som.ChunkID[3]);
    fprintf(stderr, "riff size: %u\n", som.ChunkSize);
    fprintf(stderr, "wave tag: \"%c%c%c%c\"\n", som.Format[0], som.Format[1], som.Format[2], som.Format[3]);
    fprintf(stderr, "form tag: \"%c%c%c%c\"\n", som.SubChunk1ID[0], som.SubChunk1ID[1], som.SubChunk1ID[2], som.SubChunk1ID[3]);
    fprintf(stderr, "fmt_size: %u\n", som.SubChunk1Size);
    fprintf(stderr, "audio format: %u\n", som.AudioFormat);
    fprintf(stderr, "num channels: %u\n", som.NumberOfChannels);
    fprintf(stderr, "sample rate: %u\n", som.SampleRate);
    fprintf(stderr, "byte rate: %u\n", som.ByteRate);
    fprintf(stderr, "block align: %u\n", som.BlockAlign);
    fprintf(stderr, "bits/sample: %u\n", som.BitsPerSample);
    fprintf(stderr, "bytes/sample: %u\n", som.BitsPerSample / 8);
    fprintf(stderr, "data tag: \"%c%c%c%c\"\n", som.SubChunk2ID[0], som.SubChunk2ID[1], som.SubChunk2ID[2], som.SubChunk2ID[3]);
    fprintf(stderr, "data size: %u\n", som.SubChunk2Size);
    fprintf(stderr, "samples/channel: %lu\n", som.SubChunk2Size / sizeof(int16_t) / som.NumberOfChannels);
}

/*
Aumenta o tamanho do vetor samples[] de wav1 para o tamanho do vetor de wav2. Zera os novos elementos do vetor expandido com realloc.
Altera os valores de ChunkSize, SubChunk2Size e numberofsamples para corresponder ao novo tamanho do arquivo.
*/
static void trataTamanho(t_wav * wav1, t_wav * wav2) {
    wav1->header.SubChunk2Size = wav2->header.SubChunk2Size;
    wav1->header.ChunkSize = wav2->header.ChunkSize;
    
    wav1->samples = (int16_t *)realloc(wav1->samples, wav1->header.SubChunk2Size);
    if (wav1->samples == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(1);
    }
    int i;
    for (i = wav1->numberofsamples; i < wav2->numberofsamples; i++)
        wav1->samples[i] = 0;
    wav1->numberofsamples = wav2->numberofsamples;
}

void mix(t_wav * wav1, t_wav * wav2) {
    if (wav1->numberofsamples < wav2->numberofsamples)
        trataTamanho(wav1, wav2);
    int i;
    for (i = 0; i < wav2->numberofsamples; i++) {
        int32_t soma;
        soma = wav1->samples[i] + wav2->samples[i];
        /* Testa se estoura limites. */
        if ((soma <= MAX) && (soma >= MIN))
            wav1->samples[i] = soma;
    }
}

/*
Encontra e retorna o maior elemento do vetor samples[].
*/
static int16_t encontraMaior(t_wav * wave) {
    int i;
    int16_t maior;
    maior = wave->samples[0];
    for (i = 1; i < wave->numberofsamples; i++)
        if (wave->samples[i] > maior)
            maior = wave->samples[i];
    return maior;
}

void normaliza(t_wav * wave) {
    int16_t fator;
    fator = MAX / encontraMaior(wave); /* Fator = 32767 / pico */ 
    int i;
    for (i = 0; i < wave->numberofsamples; i++)
        wave->samples[i] = wave->samples[i] * fator; /* Ajuste */
}

void reversao(t_wav * wave) {
    int i, j, k;
    int16_t temp;

    /*
    Inversao e feita separadamente por canal.
    */
    for (k = 0; k < wave->header.NumberOfChannels; k++) {
        i = k;
        j = wave->numberofsamples - wave->header.NumberOfChannels + k;
        while (i < j) {
            temp = wave->samples[i];
            wave->samples[i] = wave->samples[j];
            wave->samples[j] = temp;
            i = i + wave->header.NumberOfChannels;
            j = j - wave->header.NumberOfChannels;
        }
    }

}

void multiplica(t_wav * wave, float valor) {
    int i;
    int32_t mul;
    for (i = 0; i < wave->numberofsamples; i++) {
        mul = wave->samples[i] * valor;
        /* Testa se estoura limites */
        if ((mul <= MAX) && (mul >= MIN))
            wave->samples[i] = mul;
    }
}

void amplia(t_wav * wave, float k) {
    int i;
    int16_t diff;
    int32_t novo;
    for (i = 0; i < wave->numberofsamples; i+=2) {

        diff = wave->samples[i + 1] - wave->samples[i]; /* diff = R[t] - L[t] */

        novo = wave->samples[i + 1] + (k * diff); /* R'[t] = R[t] + k * diff */
        /* Testa se estoura limites */
        if ((novo <= MAX) && (novo >= MIN))
            wave->samples[i + 1] = novo;

        novo = wave->samples[i] - (k * diff); /* L'[t] = L[t] - k * diff */
        /* Testa se estoura limites */
        if ((novo <= MAX) && (novo >= MIN))
            wave->samples[i] = novo;

    }
}