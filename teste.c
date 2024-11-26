#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include "functions.c"

int inserir_evento(
    struct Evento evento[],
    int n
){
    char nome[100], data[20]
    char local[100], categoria[50];
    int vagas, vagasDisponiveis;
    printf("Insira um nome: ");
    scanf(" %s",nome);
    strcpy(evento[n].nome, nome);
    printf("Insira uma data: ");
    scanf(" %s",data);
    strcpy(evento[n].data, data);
    printf("Insira o local: ");
    scanf(" %s",local);
    strcpy(evento[n].local, local);
    printf("Insira a categoria: ");
    scanf(" %s",categoria);
    strcpy(categoria[n].categoria, categoria);
    printf("Insira a vaga: ");
    scanf(" %s",vagas);
    strcpy(vagas[n].vagas, vagas);
    
    n++;
    return n;
};

void mostrar_eventos(
    struct  Evento evento[],
    int n    
){
    for(int i = 0; i<= n;i++){
        printf("O nome do evento %d eh: %s\n",i+1,evento[i].nome);
        printf("A data do evento %d eh: %s\n",i+1,evento[i].data);
        printf("O local do evento %d eh: %s\n",i+1,evento[i].local);
        printf("A categoria do evento %d eh: %s\n",i+1,evento[i].categoria);
        printf("A vaga do evento %d eh: %s\n",i+1,evento[i].vagas);
    }
}

int main(){
    struct Evento eventos[100];
    char nome[100];
    int ultima_posicao = 0;

    ultima_posicao = inserir_evento(eventos, ultima_posicao);

    ultima_posicao = inserir_evento(eventos, ultima_posicao);

    ultima_posicao = inserir_evento(eventos, ultima_posicao);

    mostrar_eventos(eventos,ultima_posicao);
    return 0;
}
