#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include "functions.c"

Menu* create_menu(int id,char* title, MenuOption* options, int options_size);

MenuOption* create_menu_options(char* options_list[],int options_qnt);

void show_menu(Menu* menu);

int navigate_menu(Menu* menu);

int insert_event(struct Evento eventos[], int n);

int search_event_by_name(struct Evento eventos[], int tamanho, char nome[]);

int search_event_by_code(struct Evento eventos[], int tamanho, int codigo);

int delete_event(struct Evento eventos[], int index, int tamanho);

void show_event(struct Evento evento);

void list_events(struct Evento eventos[],int n);

#define MAX_OPTION_QNT 15
#define MAX_MENU_QNT 15
#define MAX_EVENTOS 100
#define MAX_PARTICIPANTES 100

void main(void){

    // DEFININDO VARIÁVEIS DE EVENTOS
    // TO DO: LER EVENTOS DE ARQUIVO
    struct Evento events[MAX_EVENTOS];
    int ultima_posicao_evento = 0;
    int current_event_index = 9999;

    // DEFININDO VARIÁVEIS DE PARTICIPANTES
    //TO DO: LER PARTICIPANTES DE ARQUIVO
    struct Participante participants[MAX_PARTICIPANTES];
    int ultima_posicao_participante = 0;
    int current_participant_index = 9999;

    // DEFININDO VARIÁVEIS PARA NAVEGAÇÃO DOS MENUS
    int current_menu_id = 1, current_selection = 0;
    char escolha = 'n';

    // CRIANDO AS DECRICOES DE CADA MENU EM ORDEM
    char* all_titles[MAX_MENU_QNT] = {
        "Menu Principal",
        "Menu de Eventos",
        "Menu de Participantes",
        "Menu de Relatorios",
        "Buscar Eventos",
        "O que deseja fazer com o evento encontrado?",
        "O que voce deseja editar?",
        "Listar Participantes",
        "Buscar Participante",
        "O que deseja fazer com o participante selecionado?",
        "O que voce deseja editar?"
    };

    // CRIANDO AS OPCOES DE CADA MENU EM ORDEM
    char* all_options[MAX_MENU_QNT][MAX_OPTION_QNT] = {
        {"Modulo de eventos", "Modulo de participantes", "Modulo de relatorios", "Fechar programa"},
        {"Cadastrar novo evento", "Listar eventos", "Buscar evento", "Voltar"},
        {"Registar um participante", "Listar participantes", "Consultar participante", "Voltar"},
        {"Ranquear eventos por numero de inscritos", "Participantes por instituicao", "Listar eventos por categoria", "Listar eventos ordenados por data", "Voltar"},
        {"Buscar por nome", "Buscar por codigo", "Voltar"},
        {"Deletar evento", "Editar evento", "Voltar"},
        {"Nome", "Data", "Local", "Categoria", "Vagas", "Voltar"},
        {"Listar todos os participantes","Filtrar por evento","Filtrar por instituicao","Voltar"},
        {"Consultar por codigo","Consultar por nome","Consultar por email","Voltar"},
        {"Cancelar inscricao do participante","Editar dados do participante","Trocar evento do participante","Voltar"},
        {"Nome", "Email", "Instituicao", "Voltar"}
    };
    
    // DEFININDO A QUANTIDADE DE OPCOES POR MENU
    int menu_qnt = sizeof(all_titles)/sizeof(all_titles[0]);
    int *options_quantities = malloc(menu_qnt*sizeof(int));
    for(int i = 0; i < menu_qnt; i++){
        for(int j = 0; j<MAX_OPTION_QNT;j++){
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
                        ultima_posicao_evento = insert_event(events,ultima_posicao_evento);
                        show_menu(&all_menus[1]);
                        printf("Evento criado com sucesso!\n");
                        break;
                    case 1: // LISTAR TODOS OS EVENTOS
                        show_menu(&all_menus[1]);
                        list_events(events,ultima_posicao_evento);
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
                    case 0: // INSERE UM PARTICIPANTE
                        int success_flag = ultima_posicao_participante;
                        ultima_posicao_participante = insert_participant(participants,ultima_posicao_participante,events,ultima_posicao_evento);
                        if(success_flag!=ultima_posicao_participante){
                            show_menu(&all_menus[current_menu_id-1]);
                            printf("Participante registrado com sucesso!\n");
                        }
                        break;
                    case 1: // NAVEGA PARA O MENU DE LISTAR PARTICIPANTES
                        current_menu_id = all_menus[7].id;
                        show_menu(&all_menus[7]);
                        break;
                    case 2: // NAVEGA PARA O MENU DE BUSCAR PARTICIPANTE
                        current_menu_id = all_menus[8].id;
                        show_menu(&all_menus[8]);
                        break;
                    case 3: // NAVEGA PARA O MENU PRINCIPAL
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
                        char nome[100];
                        printf("Insira o nome do evento: ");
                        scanf(" %s",nome);
                        current_event_index = search_event_by_name(events, ultima_posicao_evento,nome);
                        if(current_event_index!=9999){
                            current_menu_id = all_menus[5].id;
                            show_menu(&all_menus[5]);
                            printf("Evento encontrado: ");
                            show_event(events[current_event_index]);
                        } else {
                            printf("Nao foi encontrado nenhum evento com esse nome!\n");
                        };
                        break;
                    case 1: // BUSCA EVENTO POR CODIGO E NAVEGA PARA MENU DE DELETAR OU EDITAR
                        int codigo;
                        printf("Insira o codigo do evento: ");
                        scanf(" %d",&codigo);
                        current_event_index = search_event_by_code(events, ultima_posicao_evento, codigo);
                        if(current_event_index!=9999){
                            current_menu_id = all_menus[5].id;
                            show_menu(&all_menus[5]);
                            printf("Evento encontrado: ");
                            show_event(events[current_event_index]);
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
                show_event(events[current_event_index]);
                switch (current_selection){
                    case 0: // DELETA EVENTO E NAVEGA PARA MENU DE BUSCA DE EVENTOS
                        delete_event(events,current_event_index,ultima_posicao_evento);
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
                show_event(events[current_event_index]);
                edit_event(events, current_event_index, current_selection);
                printf("Coluna editada com sucesso!\n");

            case 8: // MOSTRA MENU DE LISTAR PARTICIPANTES
                current_selection = navigate_menu(
                    &all_menus[current_menu_id-1]
                );
                // {"Listar todos os participantes","Filtrar por evento","Filtrar por instituicao","Voltar"}
                switch(current_selection) {
                    case 0: // Listar todos os participantes
                        show_menu(&all_menus[current_menu_id-1]);
                        list_participants(participants,ultima_posicao_participante,NULL,0);
                        break;
                    case 1: // Filtrar por evento
                        int temp_code;
                        printf("Insira o codigo do evento: ");
                        scanf(" %d", &temp_code);
                        list_participants(participants,ultima_posicao_participante,NULL,temp_code);
                        break;
                    case 2: // Filtrar por instituicao
                        char temp_insti[100];
                        printf("Insira o nome da instituicao: ");
                        scanf(" %s",temp_insti);
                        list_participants(participants,ultima_posicao_participante,temp_insti,0);
                        break;
                    case 3: // Voltar
                        current_menu_id = all_menus[2].id;
                        show_menu(&all_menus[2]);
                        break;
                    default:
                        break;
                }
                break;
            
            case 9: // MOSTRA MENU DE CONSULTAR PARTICIPANTE
                current_selection = navigate_menu(
                    &all_menus[current_menu_id-1]
                );
                // {"Consultar por codigo","Consultar por nome","Consultar por email","Voltar"}
                switch(current_selection) {
                    case 0: // Consultar por codigo
                        int codigo;
                        printf("Insira o codigo do participante: ");
                        scanf(" %d",&codigo);
                        current_participant_index = search_participant_by_code(participants, ultima_posicao_participante,codigo);
                        if(current_participant_index!=9999){
                            current_menu_id = all_menus[9].id;
                            show_menu(&all_menus[9]);
                            printf("Participante encontrado: ");
                            show_participant(participants[current_participant_index]);
                        } else {
                            printf("Nao foi encontrado nenhum evento com esse nome!\n");
                        };
                        break;
                    case 1: // Consultar por nome
                        char nome[100];
                        printf("Insira o nome do participante: ");
                        scanf(" %s",nome);
                        current_participant_index = search_participant_by_name(participants, ultima_posicao_participante,nome);
                        if(current_participant_index!=9999){
                            current_menu_id = all_menus[9].id;
                            show_menu(&all_menus[9]);
                            printf("Participante encontrado: ");
                            show_participant(participants[current_participant_index]);
                        } else {
                            printf("Nao foi encontrado nenhum evento com esse nome!\n");
                        };
                        break;
                    case 2: // Consultar por email
                        char email[100];
                        printf("Insira o email do participante: ");
                        scanf(" %s",email);
                        current_participant_index = search_participant_by_email(participants, ultima_posicao_participante,email);
                        if(current_participant_index!=9999){
                            current_menu_id = all_menus[9].id;
                            show_menu(&all_menus[9]);
                            printf("Participante encontrado: ");
                            show_participant(participants[current_participant_index]);
                        } else {
                            printf("Nao foi encontrado nenhum evento com esse email!\n");
                        };
                        break;
                    case 3: // Voltar
                        current_menu_id = all_menus[2].id;
                        show_menu(&all_menus[2]);
                        break;
                    default:
                        break;
                }
                break;
            case 10: // MOSTRA MENU DE EDITAR PARTICIPANTE
                current_selection = navigate_menu(
                    &all_menus[current_menu_id-1]
                );
                //{"Cancelar inscricao do participante","Editar dados do participante","Trocar evento do participante","Voltar"}
                switch(current_selection) {
                    case 0: // Cancelar inscricao do participante
                        delete_participant(participants,ultima_posicao_participante,current_participant_index,events,ultima_posicao_evento);
                        ultima_posicao_participante--;
                        current_menu_id = all_menus[9].id;
                        show_menu(&all_menus[9]);
                        break;
                    case 1: // Editar dados do participante
                        current_menu_id = all_menus[10].id;
                        show_menu(&all_menus[10]);
                        break;
                    case 2: // Trocar evento do participante
                        break;
                    case 3: // Voltar
                        current_menu_id = all_menus[2].id;
                        show_menu(&all_menus[2]);
                        break;
                    default:
                        break;
                }
                break;
            case 11: // MOSTRA MENU DE EDITAR DADOS DO PARTICIPANTE
                current_selection = navigate_menu(
                    &all_menus[current_menu_id-1]
                );
                //{"Nome", "Email", "Instituicao", "Voltar"}
                if(current_selection == 3){
                    current_menu_id = all_menus[9].id;
                    show_menu(&all_menus[9]);
                    printf("Participante removido com sucesso!\n");
                    break;
                }
                show_participant(participants[current_participant_index]);
                edit_participant(participants, current_participant_index, current_selection);
                printf("Coluna editada com sucesso!\n");
                
            default:
                break;
        }
    }
}