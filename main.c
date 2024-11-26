#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include "functions.c"

Menu* create_menu(int id,char* title, MenuOption* options, int options_size);

void show_menu(Menu* menu);

int navigate_menu(Menu* menu);

void main(void){

    // DEFININDO VARIÁVEIS DE EVENTOS
    struct Evento eventos[100];
    int ultima_posicao_evento = 0;

    // DEFININDO VARIÁVEIS PARA NAVEGAÇÃO DOS MENUS
    int current_menu_id = 1, current_selection = 0;
    void* temp;

    // CRIANDO MENU PRINCIPAL
    char* main_title = "Menu Principal";
    char* main_options_list[] = {"Modulo de eventos", "Modulo de participantes", "Modulo de relatorios", "Fechar programa"};
    int main_options_qnt = sizeof(main_options_list)/sizeof(main_options_list[0]);
    MenuOption* main_options = malloc(sizeof(MenuOption)*main_options_qnt);
    for(int i = 0; i < main_options_qnt; i++){
        main_options[i].description = main_options_list[i];
    };
    main_options[0].menu_id = 2;
    main_options[1].menu_id = 3;
    main_options[2].menu_id = 4;
    main_options[3].menu_id = 0;
    Menu* main_menu = malloc(sizeof(Menu));
    main_menu = create_menu(1,main_title,main_options,main_options_qnt);

    // CRIANDO MENU DE EVENTOS
    char* events_title = "Menu de Eventos";
    char* events_options_list[] = {"Cadastrar novo evento", "Listar eventos", "Buscar evento", "Deletar evento", "Voltar"};
    int events_options_qnt = sizeof(events_options_list)/sizeof(events_options_list[0]);
    MenuOption* events_options = malloc(sizeof(MenuOption)*events_options_qnt);
    for(int i = 0; i < events_options_qnt; i++){
        events_options[i].description = events_options_list[i];
    };
    events_options[2].menu_id = 5;
    events_options[3].menu_id = 1;
    Menu* events_menu = malloc(sizeof(Menu));
    events_menu = create_menu(2,events_title,events_options,events_options_qnt);

    // CRIANDO MENU DE BUSCA DE EVENTOS
    char* events_search_title = "Buscar Eventos";
    char* events_search_options_list[] = {"Buscar por nome", "Buscar por codigo", "Voltar"};
    int events_search_options_qnt = sizeof(events_search_options_list)/sizeof(events_search_options_list[0]);
    MenuOption* events_search_options = malloc(sizeof(MenuOption)*events_search_options_qnt);
    for(int i = 0; i < events_search_options_qnt; i++){
        events_search_options[i].description = events_search_options_list[i];
    };
    events_search_options[2].menu_id = 1;
    Menu* events_search_menu = malloc(sizeof(Menu));
    events_search_menu = create_menu(5,events_search_title,events_search_options,events_search_options_qnt);

    // CRIANDO MENU DE PARTICIPANTES
    char* participants_title = "Menu de Participantes";
    char* participants_options_list[] = {"Inscrever participante em um evento", "Listar participantes de um evento", "Cancelar inscricao", "Consultar CPF/Codigo", "Voltar"};
    int participants_options_qnt = sizeof(participants_options_list)/sizeof(participants_options_list[0]);
    MenuOption* participants_options = malloc(sizeof(MenuOption)*participants_options_qnt);
    for(int i = 0; i < participants_options_qnt; i++){
        participants_options[i].description = participants_options_list[i];
    };
    participants_options[4].menu_id = 1;
    Menu* participants_menu = malloc(sizeof(Menu));
    participants_menu = create_menu(3,participants_title,participants_options,participants_options_qnt);

    // CRIANDO MENU DE RELATORIOS
    char* reports_title = "Menu de Relatórios";
    char* reports_options_list[] = {"Ranquear eventos por numero de inscritos", "Participantes por instituicao", "Listar eventos por categoria", "Listar eventos ordenados por data", "Voltar"};
    int reports_options_qnt = sizeof(reports_options_list)/sizeof(reports_options_list[0]);
    MenuOption* reports_options = malloc(sizeof(MenuOption)*reports_options_qnt);
    for(int i = 0; i < reports_options_qnt; i++){
        reports_options[i].description = reports_options_list[i];
    };
    reports_options[4].menu_id = 1;
    Menu* reports_menu = malloc(sizeof(Menu));
    reports_menu = create_menu(4,reports_title,reports_options,reports_options_qnt);

    // MONSTRANDO MENU PRINCIPAL E INICIANDO LOOP DE NAVEGAÇÃO
    show_menu(main_menu);
    while(current_menu_id != 0){

        switch (current_menu_id){

            case 1: // MOSTRA MENU PRINCIPAL
                current_selection = navigate_menu(
                    main_menu
                );
                switch(current_selection){
                    case 0: // NAVEGA PARA MENU DE EVENTOS
                        current_menu_id = events_menu->id;
                        show_menu(events_menu);
                        break;
                    case 1: // NAVEGA PARA MENU DE PARTICIPANTES
                        current_menu_id = participants_menu->id;
                        show_menu(participants_menu);
                        break;
                    case 2: // NAVEGA PARA MENU DE RELATÓRIOS
                        current_menu_id = reports_menu->id;
                        show_menu(reports_menu);
                        break;
                    case 3: // TERMINA O PROGRAMA
                        current_menu_id = 0;
                        break;
                }
                break;

            case 2: // MOSTRA MENU DE EVENTOS
                current_selection = navigate_menu(
                    events_menu
                );
                switch (current_selection){
                    case 0: // CADASTRAR EVENTOS
                        ultima_posicao_evento = inserir_evento(eventos,ultima_posicao_evento);
                        show_menu(events_menu);
                        break;
                    case 1: // LISTAR TODOS OS EVENTOS
                        mostrar_eventos(eventos,ultima_posicao_evento);
                        break;
                    case 2: // BUSCAR UM EVENTO POR CODIGO OU NOME
                        break;
                    case 3: // DELETAR UM EVENTO POR CODIGO OU NOME
                        break;
                    case 4: // NAVEGA PARA O MENU PRINCIPAL
                        current_menu_id = main_menu->id;
                        show_menu(main_menu);
                        break;
                    default:
                        break;
                }
                break;

            case 3: // MOSTRA MENU DE PARTICIPANTES
                current_selection = navigate_menu(
                    participants_menu
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
                        current_menu_id = main_menu->id;
                        show_menu(main_menu);
                        break;
                    default:
                        break;
                }
                break;

            case 4: // MOSTRA MENU DE RELATÓRIOS
                current_selection = navigate_menu(
                    reports_menu
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
                        current_menu_id = main_menu->id;
                        show_menu(main_menu);
                        break;
                    default:
                        break;
                }
                break;

            case 5: // MOSTRA MENU DE BUSCA DE EVENTOS
                current_selection = navigate_menu(
                    events_search_menu
                );
                switch (current_selection){
                    case 0:
                        printf("Buscar evento por nome\n");
                        break;
                    case 1:
                        printf("Buscar evento por codigo\n");
                        break;
                    case 2: // NAVEGA PARA O MENU DE EVENTOS
                        current_menu_id = events_menu->id;
                        show_menu(events_menu);
                        break;
                    default:
                        break;
                }
                break;
            
            default:
                break;
        }
    }
}