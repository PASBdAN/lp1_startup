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


    // CRIANDO AS OPCOES DO MENU PRINCIPAL
    char* main_options_list[] = {"Modulo de eventos", "Modulo de participantes", "Modulo de relatorios", "Fechar programa"};
    int main_options_qnt = sizeof(main_options_list)/sizeof(main_options_list[0]);
    MenuOption* main_options = create_menu_options(main_options_list, main_options_qnt);
    // CRIANDO O MENU PRINCIPAL
    Menu* main_menu = malloc(sizeof(Menu));
    char* main_title = "Menu Principal";
    main_menu = create_menu(1,main_title,main_options,main_options_qnt);

    // CRIANDO AS OPCOES MENU DE EVENTOS
    char* events_options_list[] = {"Cadastrar novo evento", "Listar eventos", "Buscar evento", "Voltar"};
    int events_options_qnt = sizeof(events_options_list)/sizeof(events_options_list[0]);
    MenuOption* events_options = create_menu_options(events_options_list, events_options_qnt);
    // CRIANDO O MENU DE EVENTOS
    Menu* events_menu = malloc(sizeof(Menu));
    char* events_title = "Menu de Eventos";
    events_menu = create_menu(2,events_title,events_options,events_options_qnt);

    // CRIANDO AS OPCOES DO MENU DE PARTICIPANTES
    char* participants_options_list[] = {"Inscrever participante em um evento", "Listar participantes de um evento", "Cancelar inscricao", "Consultar CPF/Codigo", "Voltar"};
    int participants_options_qnt = sizeof(participants_options_list)/sizeof(participants_options_list[0]);
    MenuOption* participants_options = create_menu_options(participants_options_list, participants_options_qnt);
    // CRIANDO MENU DE PARTICIPANTES
    Menu* participants_menu = malloc(sizeof(Menu));
    char* participants_title = "Menu de Participantes";
    participants_menu = create_menu(3,participants_title,participants_options,participants_options_qnt);

    // CRIANDO AS OPCOES DO MENU DE RELATORIOS
    char* reports_options_list[] = {"Ranquear eventos por numero de inscritos", "Participantes por instituicao", "Listar eventos por categoria", "Listar eventos ordenados por data", "Voltar"};
    int reports_options_qnt = sizeof(reports_options_list)/sizeof(reports_options_list[0]);
    MenuOption* reports_options = create_menu_options(reports_options_list, reports_options_qnt);
    // CRIANDO MENU DE RELATORIOS
    Menu* reports_menu = malloc(sizeof(Menu));
    char* reports_title = "Menu de Relatórios";
    reports_menu = create_menu(4,reports_title,reports_options,reports_options_qnt);

    // CRIANDO AS OPCOES DO MENU DE BUSCA DE EVENTOS
    char* events_search_options_list[] = {"Buscar por nome", "Buscar por codigo", "Voltar"};
    int events_search_options_qnt = sizeof(events_search_options_list)/sizeof(events_search_options_list[0]);
    MenuOption* events_search_options = create_menu_options(events_search_options_list, events_search_options_qnt);
    // CRIANDO MENU DE BUSCA DE EVENTOS
    Menu* events_search_menu = malloc(sizeof(Menu));
    char* events_search_title = "Buscar Eventos";
    events_search_menu = create_menu(5,events_search_title,events_search_options,events_search_options_qnt);

    // CRIANDO AS OPCOES DO MENU DE DELETAR OU EDITAR EVENTO
    char* events_del_upd_options_list[] = {"Deletar evento", "Editar evento", "Voltar"};
    int events_del_upd_options_qnt = sizeof(events_del_upd_options_list)/sizeof(events_del_upd_options_list[0]);
    MenuOption* events_del_upd_options = create_menu_options(events_del_upd_options_list, events_del_upd_options_qnt);
    // CRIANDO MENU DE DELETAR OU EDITAR EVENTO
    Menu* events_del_upd_menu = malloc(sizeof(Menu));
    char* events_del_upd_title = "O que deseja fazer com o evento encontrado?";
    events_del_upd_menu = create_menu(6,events_del_upd_title,events_del_upd_options,events_del_upd_options_qnt);


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
                        printf("Evento criado com sucesso!\n");
                        break;
                    case 1: // LISTAR TODOS OS EVENTOS
                        show_menu(events_menu);
                        listar_eventos(eventos,ultima_posicao_evento);
                        break;
                    case 2: // BUSCAR UM EVENTO
                        current_menu_id = events_search_menu->id;
                        show_menu(events_search_menu);
                        break;
                    case 3: // NAVEGA PARA O MENU PRINCIPAL
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
                        current_event_index = buscar_evento_por_nome(eventos, ultima_posicao_evento);
                        if(current_event_index!=9999){
                            current_menu_id = events_del_upd_menu->id;
                            show_menu(events_del_upd_menu);
                            printf("Evento encontrado: ");
                            mostrar_evento(eventos[current_event_index]);
                        } else {
                            printf("Nao foi encontrado nenhum evento com esse nome!\n");
                        };
                        break;
                    case 1:
                        current_event_index = buscar_evento_por_codigo(eventos, ultima_posicao_evento);
                        if(current_event_index!=9999){
                            current_menu_id = events_del_upd_menu->id;
                            show_menu(events_del_upd_menu);
                            printf("Evento encontrado: ");
                            mostrar_evento(eventos[current_event_index]);
                        } else{
                            printf("Nao foi encontrado nenhum evento com esse codigo!\n");
                        };
                        break;
                    case 2: // NAVEGA PARA O MENU DE EVENTOS
                        current_menu_id = events_menu->id;
                        show_menu(events_menu);
                        break;
                    default:
                        break;
                }
                break;

            case 6: // MOSTRA MENU DE DELETAR OU EDITAR EVENTO
                current_selection = navigate_menu(
                    events_del_upd_menu
                );
                mostrar_evento(eventos[current_event_index]);
                switch (current_selection){
                    case 0:
                        deletar_evento(eventos,current_event_index,ultima_posicao_evento);
                        ultima_posicao_evento--;
                        current_menu_id = events_search_menu->id;
                        show_menu(events_search_menu);
                        break;
                    case 1:
                        printf("Editar um evento\n");
                        break;
                    case 2: // NAVEGA PARA O MENU DE BUSCA DE EVENTOS
                        current_menu_id = events_search_menu->id;
                        show_menu(events_search_menu);
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