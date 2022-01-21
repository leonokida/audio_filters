/* GRR20190365 Leon Augusto Okida Goncalves */
#include "linhaComando.h"
#include "filtros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int entradaCatMix(int argc, char * argv[], t_wav * som1, char ** output, opCatMix_t opcao) {
    t_wav som2;
    int flag_o;
    flag_o = 0;
    FILE * arqin1, * arqin2;

    /* Leitura do primeiro arquivo */
    arqin1 = abreArqL(argv[1]);
    *som1 = leitura(arqin1);
    fclose(arqin1);
    if (!testaWave(som1)) {
        fprintf(stderr, "O arquivo %s não é formato WAVE\n", argv[1]);
        free(som1->samples);
        exit(1);
    }

    int i = 2;
    while (i < argc) {
        if (!strcmp(argv[i], "-o")) {
            /* Argumento de direcionamento da saida */
            flag_o = 1;
            *output = argv[i + 1];
            i = i + 2;
        }
        else {
            /* Arquivo WAVE a ser tratado */
            arqin2 = abreArqL(argv[i]);
            som2 = leitura(arqin2);
            fclose(arqin2);
            if (!testaWave(&som2)) {
                fprintf(stderr, "O arquivo %s não é formato WAVE\n", argv[i]);
                free(som1->samples);
                free(som2.samples);
                exit(1);
            }
            if (som1->header.SampleRate == som2.header.SampleRate) {
                /* Chamada da funcao de tratamento de audio com base em opcao */
                if (opcao == CAT)
                    concatenacao(som1, &som2);
                else if (opcao == MIX)
                    mix(som1, &som2);
            }                
            else
                fprintf(stderr, "Taxa de amostragem de %s é diferente da taxa do primeiro arquivo.\n", argv[i]);

            free(som2.samples);
            i++;
        }
    }
    return flag_o;
}

int entradaWavecho(int argc, char * argv[], t_wav * som, char ** output) {
    char opcao;
    char *input;
    float level, delay;
    int flag_i, flag_l, flag_o, flag_t;
    flag_i = 0;
    flag_l = 0;
    flag_o = 0;
    flag_t = 0;

    while ((opcao = getopt(argc, argv, "i:l:t:o:")) != -1) {
        switch(opcao) {
        case 'i':
            /* Argumento de input */
            flag_i = 1;
            input = optarg;
            break;
        case 'l':
            /* Argumento de level */
            flag_l = 1;
            level = atof(optarg);
            break;
        case 't':
            /* Argumento de delay */
            flag_t = 1;
            delay = atof(optarg);
            break;
        case 'o':
            /* Argumento de output */
            flag_o = 1;
            *output = optarg;
            break;
        default:
            /* Argumento invalido */
            fprintf(stderr, "Erro: parâmetros válidos são: -i, -l, -t ou -o\n");
            exit(1);
            break;
        }
    }

    if (flag_i == 1) {
        /* Entrada e um arquivo */
        FILE * arqin = abreArqL(input);
        *som = leitura(arqin);
        fclose(arqin);
        if (!testaWave(som)) {
            fprintf(stderr, "O arquivo %s não é formato WAVE\n", input);
            free(som->samples);
            exit(1);
        }
    }
    else {
        /* Entrada e a padrao */
        *som = leitura(stdin);
        if (!testaWave(som)) {
            fprintf(stderr, "O arquivo passado por stdin não é formato WAVE\n");
            free(som->samples);
            exit(1);
        }
    }

    if ((flag_l == 0) || (level < 0) || (level > 1)) {
        fprintf(stderr, "Parâmetro -l entrado inválido, usando parâmetro padrão.\n");
        level = 0.5;
    }
    if ((flag_t == 0) || (delay < 0)) {
        fprintf(stderr, "Parâmetro -t entrado inválido, usando parâmetro padrão.\n");
        delay = 1000;
    }
    
    /* Chamada da funcao de tratamento do audio */
    echo(som, level, delay);

    return flag_o;
}

void entradaWavinfo(int argc, char *argv[], t_header * som) {
    char opcao;
    FILE * arq;

    if ((opcao = getopt(argc, argv, "i:")) != -1)
        /* Entrada e um arquivo */
        arq = abreArqL(optarg);
    else
        /* Entrada e a padrao */
        arq = stdin;

    *som = leituraHeader(arq);
    fclose(arq);
    if (!((som->Format[0] == 'W') && (som->Format[1] == 'A') && (som->Format[2] == 'V') && (som->Format[3] == 'E'))) {
        fprintf(stderr, "O arquivo entrado não é formato WAVE\n");
        exit(1);
    }
    escreve(*som);
}

int entradaNormRev(int argc, char *argv[], t_wav * som, char ** output, opNormRev_t op) {
    char opcao;
    char *input;
    int flag_i, flag_o;
    flag_i = 0;
    flag_o = 0;

    while ((opcao = getopt(argc, argv, "i:o:")) != -1) {
        switch(opcao) {
            case 'i':
                /* Argumento de input */
                flag_i = 1;
                input = optarg;
                break;
            case 'o':
                /* Argumento de output */
                flag_o = 1;
                *output = optarg;
                break;
            default:
                /* Argumento invalido */
                fprintf(stderr, "Erro: parâmetros válidos são: -i ou -o\n");
                exit(1);
                break;
        }
    }

    if (flag_i == 1) {
        /* Entrada e um arquivo */
        FILE * arqin = abreArqL(input);
        *som = leitura(arqin);
        fclose(arqin);
        if (!testaWave(som)) {
            fprintf(stderr, "O arquivo %s não é formato WAVE\n", input);
            free(som->samples);
            exit(1);
        }
    }
    else {
        /* Entrada e a padrao */
        *som = leitura(stdin);
        if (!testaWave(som)) {
            fprintf(stderr, "O arquivo passado não é formato WAVE\n");
            free(som->samples);
            exit(1);
        }
    }
    /* Chamada da funcao de tratamento de audio com base em op */
    if (op == NORM)
        normaliza(som);
    else if (op == REV)
        reversao(som);

    return flag_o;
}

int entradaVolWide(int argc, char *argv[], t_wav * som, char ** output, opVolWide_t op) {
    char opcao;
    char *input;
    float fator;
    int flag_i, flag_l, flag_o;
    fator = 1;
    flag_i = 0;
    flag_l = 0;
    flag_o = 0;

    while ((opcao = getopt(argc, argv, "i:l:o:")) != -1) {
        switch(opcao) {
            case 'i':
                /* Argumento de input */
                flag_i = 1;
                input = optarg;
                break;
            case 'l':
                /* Argumento de fator */
                flag_l = 1;
                fator = atof(optarg);
                break;
            case 'o':
                /* Argumento de output */
                flag_o = 1;
                *output = optarg;
                break;
            default:
                /* Argumento invalido */
                fprintf(stderr, "Erro: parâmetros válidos são: -i, -l ou -o\n");
                exit(1);
                break;
        }
    }

    if (flag_i == 1) {
        /* Entrada e um arquivo */
        FILE * arqin = abreArqL(input);
        *som = leitura(arqin);
        fclose(arqin);
        if (!testaWave(som)) {
            fprintf(stderr, "O arquivo %s não é formato WAVE\n", input);
            free(som->samples);
            exit(1);
        }
    }
    else {
        /* Entrada e a padrao */
        *som = leitura(stdin);
        if (!testaWave(som)) {
            fprintf(stderr, "O arquivo passado não é formato WAVE\n");
            free(som->samples);
            exit(1);
        }
    }

    if ((flag_l == 0) || (fator < 0) || (fator > 10)) {
        fprintf(stderr, "Parâmetro -l entrado inválido, usando parâmetro padrão.\n");
        fator = 1;
    }
    
    /*
    Chamada da funcao de tratamento de audio com base em op.
    Se op eh WIDE e o arquivo nao for estereo, retorna erro.
    */
    if (op == VOL)
        multiplica(som, fator);
    else if ((op == WIDE) && (som->header.NumberOfChannels == 2))
        amplia(som, fator);
    else {
        fprintf(stderr, "O arquivo WAVE deve ter sinal estéreo.\n");
        free(som->samples);
        exit(1);
    }
    
    return flag_o;
}

FILE * decideSaida(int flag, char * output) {
    if (flag)
        return abreArqE(output);
    else
        return stdout;
}

void encerraPrograma(FILE ** arqout, t_wav * som) {
    escrita(*arqout, *som);
    free(som->samples);
    fclose(*arqout);
}