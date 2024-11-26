#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
// #include "functions.c"
#include "defines.h"

int insert_event(
    struct Evento evento[],
    int n
){
    char nome[100], data[20];
    char local[100], categoria[50];
    int vagas, vagasDisponiveis, codigo = 0;

    // LOOP PARA INSERIR UM CODIGO UNICO
    for(int i = 0; i < n; i++){
        if(evento[i].codigo >= codigo){
            codigo = evento[i].codigo;
        }
    }
    codigo++;

    printf("Insira um nome: ");
    scanf(" %s",nome);
    strcpy(evento[n].nome, nome);

    printf("Insira uma data: ");
    scanf(" %s\n",data);
    strcpy(evento[n].data, data);

    printf("Insira o local: ");
    scanf(" %s",local);
    strcpy(evento[n].local, local);

    printf("Insira a categoria: ");
    scanf(" %s",categoria);
    strcpy(evento[n].categoria, categoria);

    printf("Insira a vaga: ");
    scanf(" %d",&vagas);
    evento[n].vagas = vagas;

    evento[n].vagasDisponiveis = vagas;

    evento[n].codigo = codigo;
    
    n++;
    return n;
};

void mostrar_eventos(
    struct  Evento evento[],
    int n    
){
    for(int i = 0; i < n; i++){
        int s_nome = strlen(evento[i].nome);
        int s_data = strlen(evento[i].data);
        int s_local = strlen(evento[i].local);
        int s_categoria = strlen(evento[i].categoria);
        printf("CODIGO - NOME DATA LOCAL CATEGORIA VAGAS VAGAS_DISPONIVEIS\n");
        printf(
            "%d - %s %s %s %s %d %d\n",
            evento[i].codigo,
            evento[i].nome,
            evento[i].data,
            evento[i].local,
            evento[i].categoria,
            evento[i].vagas,
            evento[i].vagasDisponiveis
        );
    }
}

int main(){
    struct Evento eventos[100];
    int ultima_posicao = 0;

    ultima_posicao = insert_event(eventos, ultima_posicao);

    // ultima_posicao = inserir_evento(eventos, ultima_posicao);

    // ultima_posicao = inserir_evento(eventos, ultima_posicao);

    mostrar_eventos(eventos,ultima_posicao);
    return 0;
}
