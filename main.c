#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include "functions.c"

Menu* create_menu(int id,char* title, MenuOption* options, int options_size);

MenuOption* create_menu_options(char* options_list[],int options_qnt);

void show_menu(Menu* menu);

int navigate_menu(Menu* menu);

int inserir_evento(struct Evento eventos[], int n);

int buscar_evento_por_nome(struct Evento eventos[], int tamanho);

int buscar_evento_por_codigo(struct Evento eventos[], int tamanho);

int deletar_evento(struct Evento eventos[], int index, int tamanho);

void mostrar_evento(struct Evento evento);

void listar_eventos(struct Evento eventos[],int n);

#define MAX_OPTIONS 10
#define MAX_MENUS 10

void main(void){

    // DEFININDO VARIÁVEIS DE EVENTOS
    // TO DO: LER EVENTOS DE ARQUIVO
    struct Evento eventos[100];
    int ultima_posicao_evento = 0;
    int current_event_index = 9999;

    // DEFININDO VARIÁVEIS DE PARTICIPANTES
    //TO DO: LER PARTICIPANTES DE ARQUIVO
    struct Participante participantes[100];
    int ultima_posicao_participante = 0;
    int current_participant_index = 9999;

    // DEFININDO VARIÁVEIS PARA NAVEGAÇÃO DOS MENUS
    int current_menu_id = 1, current_selection = 0;
    char escolha = 'n';

    // CRIANDO AS DECRICOES DE CADA MENU EM ORDEM
    char* all_titles[] = {
        "Menu Principal",
        "Menu de Eventos",
        "Menu de Participantes",
        "Menu de Relatorios",
        "Buscar Eventos",
        "O que deseja fazer com o evento encontrado?",
        "O que voce deseja editar?"
    };

    // CRIANDO AS OPCOES DE CADA MENU EM ORDEM
    char* all_options[MAX_MENUS][MAX_OPTIONS] = {
        {"Modulo de eventos", "Modulo de participantes", "Modulo de relatorios", "Fechar programa"},
        {"Cadastrar novo evento", "Listar eventos", "Buscar evento", "Voltar"},
        {"Inscrever participante em um evento", "Listar participantes de um evento", "Cancelar inscricao", "Consultar CPF/Codigo", "Voltar"},
        {"Ranquear eventos por numero de inscritos", "Participantes por instituicao", "Listar eventos por categoria", "Listar eventos ordenados por data", "Voltar"},
        {"Buscar por nome", "Buscar por codigo", "Voltar"},
        {"Deletar evento", "Editar evento", "Voltar"},
        {"Nome", "Data", "Local", "Categoria", "Vagas", "Voltar"}
    };
    
    // DEFININDO A QUANTIDADE DE OPCOES POR MENU
    int menu_qnt = sizeof(all_titles)/sizeof(all_titles[0]);
    int *options_quantities = malloc(menu_qnt*sizeof(int));
    for(int i = 0; i < menu_qnt; i++){
        for(int j = 0; j<MAX_OPTIONS;j++){
            if(all_options[i][j]==NULL){
                options_quantities[i] = j;
                break;
            }
        }
    }

    // ALOCANDO E CRIANDO OS MENUS CONFORME AS VARIAVEIS E DEFINICOES ANTERIORES
    Menu* all_menus = malloc(sizeof(Menu)*menu_qnt);
    for(int i = 0; i <= menu_qnt; i++){
        all_menus[i] = *create_menu(
            i+1,
            all_titles[i],
            create_menu_options(all_options[i],options_quantities[i]),
            options_quantities[i]
        );
    };

    // MONSTRANDO MENU PRINCIPAL E INICIANDO LOOP DE NAVEGAÇÃO
    show_menu(&all_menus[0]);
    while(current_menu_id != 0){
        switch (current_menu_id){

            case 1: // MOSTRA MENU PRINCIPAL
                current_selection = navigate_menu(
                    &all_menus[current_menu_id-1]
                );
                switch(current_selection){
                    case 0: // NAVEGA PARA MENU DE EVENTOS
                        current_menu_id = all_menus[1].id;
                        show_menu(&all_menus[1]);
                        break;
                    case 1: // NAVEGA PARA MENU DE PARTICIPANTES
                        current_menu_id = all_menus[2].id;
                        show_menu(&all_menus[2]);
                        break;
                    case 2: // NAVEGA PARA MENU DE RELATÓRIOS
                        current_menu_id = all_menus[3].id;
                        show_menu(&all_menus[3]);
                        break;
                    case 3: // TERMINA O PROGRAMA
                        current_menu_id = 0;
                        break;
                }
                break;

            case 2: // MOSTRA MENU DE EVENTOS
                current_selection = navigate_menu(
                    &all_menus[current_menu_id-1]
                );
                switch (current_selection){
                    case 0: // CADASTRAR EVENTOS
                        ultima_posicao_evento = inserir_evento(eventos,ultima_posicao_evento);
                        show_menu(&all_menus[1]);
                        printf("Evento criado com sucesso!\n");
                        break;
                    case 1: // LISTAR TODOS OS EVENTOS
                        show_menu(&all_menus[1]);
                        listar_eventos(eventos,ultima_posicao_evento);
                        break;
                    case 2: // BUSCAR UM EVENTO
                        current_menu_id = all_menus[4].id;
                        show_menu(&all_menus[4]);
                        break;
                    case 3: // NAVEGA PARA O MENU PRINCIPAL
                        current_menu_id = all_menus[0].id;
                        show_menu(&all_menus[0]);
                        break;
                    default:
                        break;
                }
                break;

            case 3: // MOSTRA MENU DE PARTICIPANTES
                current_selection = navigate_menu(
                    &all_menus[current_menu_id-1]
                );
                switch (current_selection){
                    case 0:
                        printf("Increver um participante em um evento\n");
                        break;
                    case 1:
                        printf("Listar participantes de um evento\n");
                        break;
                    case 2:
                        printf("Cancelar inscricao\n");
                        break;
                    case 3:
                        printf("Consultar inscricao por CPF/codigo\n");
                        break;
                    case 4: // NAVEGA PARA O MENU PRINCIPAL
                        current_menu_id = all_menus[0].id;
                        show_menu(&all_menus[0]);
                        break;
                    default:
                        break;
                }
                break;

            case 4: // MOSTRA MENU DE RELATÓRIOS
                current_selection = navigate_menu(
                    &all_menus[current_menu_id-1]
                );
                switch (current_selection){
                    case 0:
                        printf("Eventos com mais inscritos\n");
                        break;
                    case 1:
                        printf("Participantes por instituicao\n");
                        break;
                    case 2:
                        printf("Eventos por categoria\n");
                        break;
                    case 3:
                        printf("Eventos proximos\n");
                        break;
                    case 4: // NAVEGA PARA O MENU PRINCIPAL
                        current_menu_id = all_menus[0].id;
                        show_menu(&all_menus[0]);
                        break;
                    default:
                        break;
                }
                break;

            case 5: // MOSTRA MENU DE BUSCA DE EVENTOS
                current_selection = navigate_menu(
                    &all_menus[current_menu_id-1]
                );
                switch (current_selection){
                    case 0: // BUSCA EVENTO POR NOME E NAVEGA PARA MENU DE DELETAR OU EDITAR
                        current_event_index = buscar_evento_por_nome(eventos, ultima_posicao_evento);
                        if(current_event_index!=9999){
                            current_menu_id = all_menus[5].id;
                            show_menu(&all_menus[5]);
                            printf("Evento encontrado: ");
                            mostrar_evento(eventos[current_event_index]);
                        } else {
                            printf("Nao foi encontrado nenhum evento com esse nome!\n");
                        };
                        break;
                    case 1: // BUSCA EVENTO POR CODIGO E NAVEGA PARA MENU DE DELETAR OU EDITAR
                        current_event_index = buscar_evento_por_codigo(eventos, ultima_posicao_evento);
                        if(current_event_index!=9999){
                            current_menu_id = all_menus[5].id;
                            show_menu(&all_menus[5]);
                            printf("Evento encontrado: ");
                            mostrar_evento(eventos[current_event_index]);
                        } else{
                            printf("Nao foi encontrado nenhum evento com esse codigo!\n");
                        };
                        break;
                    case 2: // NAVEGA PARA O MENU DE EVENTOS
                        current_menu_id = all_menus[1].id;
                        show_menu(&all_menus[1]);
                        break;
                    default:
                        break;
                }
                break;

            case 6: // MOSTRA MENU DE DELETAR OU EDITAR EVENTO
                current_selection = navigate_menu(
                    &all_menus[current_menu_id-1]
                );
                mostrar_evento(eventos[current_event_index]);
                switch (current_selection){
                    case 0: // DELETA EVENTO E NAVEGA PARA MENU DE BUSCA DE EVENTOS
                        deletar_evento(eventos,current_event_index,ultima_posicao_evento);
                        ultima_posicao_evento--;
                        current_menu_id = all_menus[4].id;
                        show_menu(&all_menus[4]);
                        break;
                    case 1: // NAVEGA PARA MENU DE EDITAR EVENTO
                        current_menu_id = all_menus[6].id;
                        show_menu(&all_menus[6]);
                        break;
                    case 2: // NAVEGA PARA O MENU DE BUSCA DE EVENTOS
                        current_menu_id = all_menus[4].id;
                        show_menu(&all_menus[4]);
                        break;
                    default:
                        break;
                }
                break;

            case 7: // MOSTRA MENU DE EDITAR EVENTO
                current_selection = navigate_menu(
                    &all_menus[current_menu_id-1]
                );
                if(current_selection == 5){
                    current_menu_id = all_menus[5].id;
                    show_menu(&all_menus[5]);
                    break;
                }
                mostrar_evento(eventos[current_event_index]);
                editar_evento(eventos, current_event_index, current_selection);
                printf("Coluna editada com sucesso!\n");
            
            default:
                break;
        }
    }
}