#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
// #include "functions.c"
#include "defines.h"

void show_event(struct Evento evento){
    printf(
        "%d - %s %s %s %s %d %d\n",
        evento.codigo,
        evento.nome,
        evento.data,
        evento.local,
        evento.categoria,
        evento.vagas,
        evento.vagasDisponiveis
    );
};

int teste() {
    char str[] = "Esta é uma string de exemplo";  // String original
    char *token;  // Ponteiro para armazenar cada token

    // A primeira chamada de strtok, passando a string e o delimitador
    token = strtok(str, " ");  // Delimitador: espaço em branco

    // Enquanto houver tokens, continue separando
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, " ");  // Chamada subsequente, passando NULL para continuar de onde parou
    }

    return 0;
}

void r_events_to_file(char filepath[], struct Evento events[]){
    FILE *arquivo;
    char linha[500], *palavra;
    int column = 0, i = 0;

    arquivo = fopen(filepath,"r");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
        palavra = strtok(linha,",");
        while(palavra!=NULL){
            printf("%s",palavra);
            switch(column){
                case 0:
                    events[i].codigo = atoi(palavra);
                    break;
                case 1:
                    strcpy(events[i].nome,palavra);
                    break;
                case 2:
                    strcpy(events[i].data, palavra);
                    break;
                case 3:
                    strcpy(events[i].local, palavra);
                    break;
                case 4:
                    strcpy(events[i].categoria, palavra);
                    break;
                case 5:
                    events[i].vagas = atoi(palavra);
                    break;
                case 6:
                    events[i].vagasDisponiveis = atoi(palavra);
                default:
                    break;
            }
            palavra = strtok(NULL,",");
            column++;
        }
        column = 0;
        i++;
    }
}

int main() {
    char filepath[] = "events.txt";
    struct Evento events[100];
    r_events_to_file(filepath,events);
    show_event(events[1]);
    // teste();
}