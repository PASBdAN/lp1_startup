#include "defines.h"

MenuOption* create_menu_options(
    char* options_list[],
    int options_qnt
){
    int options_qnt_plus = options_qnt;
    MenuOption* options = malloc(sizeof(MenuOption)*options_qnt_plus);
    for(int i = 0; i < options_qnt; i++){
        options[i].description = options_list[i];
    };
    return options;
};

Menu* create_menu(int id,char* title, MenuOption* options, int options_size){
    Menu *menu = malloc(sizeof(Menu));
    menu->id = id;
    menu->title = strdup(title);
    menu->options = malloc(sizeof(options));
    menu->options = options;
    menu->options_size = options_size;
    menu->selection = 0;

    return menu;
};

void show_menu(
    Menu* menu
){
    printf("\e[1;1H\e[2J");
    printf("%s\n",menu->title);
    for(int i = 0; i < menu->options_size; i++){
        if(i == menu->selection){
            printf("[x] - %s\n", menu->options[i].description);
        }
        else {
            printf("[ ] - %s\n", menu->options[i].description);
        }
    }
};

int navigate_menu(
    Menu* menu
){
    while(1){
        // KEYBOARD HIT
        if(_kbhit()){
            int key_code = _getch();
            if(key_code==224) continue; // O "ENTER" INSERE DOIS CÓDIGO SEGUIDOS: 224 E 13, NECESSÁRIO PULAR O 224
            switch(key_code){
                case 72:
                    if(menu->selection == 0){
                        menu->selection = menu->options_size - 1;
                    }
                    else{
                        menu->selection--;
                    }
                    break;
                case 80:
                    if(menu->selection == menu->options_size - 1){
                        menu->selection = 0;
                    }
                    else{
                        menu->selection++;
                    }
                    break;
                case 13:
                    return menu->selection;
                default:
                    continue;
            }
            printf("\e[1;1H\e[2J");
            show_menu(menu);
        }
        else{
            continue;
        }
    }
};

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
    scanf(" %s",data);
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

void list_events(
    struct  Evento evento[],
    int n    
){
    if(n==0){
        printf("Nao tem nenhum evento cadastrado!\n");
    }
    for(int i = 0; i < n; i++){
        show_event(evento[i]);
    }
};

int search_event_by_code(struct Evento eventos[], int tamanho, int codigo){
    for(int i = 0; i< tamanho;i++){
        if(eventos[i].codigo == codigo){
            show_event(eventos[i]);
            return i;
        }
    }
    return 9999;
};

int search_event_by_name(struct Evento eventos[], int tamanho, char nome[]){
    for(int i = 0; i< tamanho;i++){
        if(strcmp(eventos[i].nome,nome) == 0){
            show_event(eventos[i]);
            return i;
        }
    }
    return 9999;
};

void edit_event(struct Evento eventos[], int index, int column){
    char nome[100], data[20], local[100], categoria[50];
    int vagas;
    switch(column){
        case 0:
            printf("Insira o novo nome: ");
            scanf(" %s", nome);
            strcpy(eventos[index].nome,nome);
            break;
        case 1:
            printf("Insira a nova data: ");
            scanf(" %s", data);
            strcpy(eventos[index].data,data);
            break;
        case 2:
            printf("Insira o novo local: ");
            scanf(" %s", local);
            strcpy(eventos[index].local,local);
            break;
        case 3:
            printf("Insira a nova categoria: ");
            scanf(" %s", categoria);
            strcpy(eventos[index].categoria,categoria);
            break;
        case 4:
            printf("Insira a nova quantidade de vagas: ");
            scanf(" %d", &vagas);
            eventos[index].vagas = vagas;
            break;
    }
}

int delete_event(
    struct Evento eventos[],
    int index,
    int tamanho
){
    for(int i = index; i < tamanho; i ++){
        eventos[i] = eventos[i+1];
    }
    tamanho--;
    return tamanho;
}

int insert_participant(
    struct Participante participant[],
    int tamanho_participants,
    struct Evento events[],
    int tamanho_events
){
    char nome[100], email[100], instituicao[100];
    int eventoCodigo, codigo = 0;

    printf("Insira o codigo do evento do participante: ");
    scanf(" %d",&eventoCodigo);
    int event_index = search_event_by_code(events,tamanho_events,eventoCodigo);
    if(event_index==9999){
        printf("O evento solicitado não existe!\n");
        return tamanho_participants;
    }
    if(events[event_index].vagasDisponiveis == 0){
        printf("O evento nao tem vagas disponiveis para registrar esse participante!\n");
        return tamanho_participants;
    }
    events[event_index].vagasDisponiveis--;
    participant[tamanho_participants].eventoCodigo = eventoCodigo;

    // LOOP PARA INSERIR UM CODIGO UNICO
    for(int i = 0; i < tamanho_participants; i++){
        if(participant[i].codigo >= codigo){
            codigo = participant[i].codigo;
        }
    }
    codigo++;

    printf("Insira o nome do participante: ");
    scanf(" %s",nome);
    strcpy(participant[tamanho_participants].nome, nome);

    printf("Insira o email do participante: ");
    scanf(" %s",email);
    strcpy(participant[tamanho_participants].email, email);

    printf("Insira a instituicao do participante: ");
    scanf(" %s",instituicao);
    strcpy(participant[tamanho_participants].instituicao, instituicao);

    participant[tamanho_participants].codigo = codigo;
    
    tamanho_participants++;

    return tamanho_participants;
};

void show_participant(struct Participante participant){
    printf(
        "%d - %s %s %s %d\n",
        participant.codigo,
        participant.nome,
        participant.email,
        participant.instituicao,
        participant.eventoCodigo
    );
};

void list_participants(
    struct  Participante participants[],
    int n,
    char instituicao[],
    int eventoCodigo
){
    if(n==0){
        printf("Nao tem nenhum participante cadastrado!\n");
    }
    for(int i = 0; i < n; i++){
        if(instituicao!=NULL){
            if(strcmp(participants[i].instituicao,instituicao) == 0){
                show_participant(participants[i]);
            }
            continue;
        }
        if(eventoCodigo!=0){
            if(participants[i].eventoCodigo == eventoCodigo){
                show_participant(participants[i]);
            }
            continue;
        }
        show_participant(participants[i]);
    }
};

void edit_participant(struct Participante participants[], int index, int column){
    char nome[100], email[100], instituicao[100];
    int eventoCodigo;
    switch(column){
        case 0:
            printf("Insira o novo nome: ");
            scanf(" %s", nome);
            strcpy(participants[index].nome,nome);
            break;
        case 1:
            printf("Insira a nova email: ");
            scanf(" %s", email);
            strcpy(participants[index].email,email);
            break;
        case 2:
            printf("Insira o novo instituicao: ");
            scanf(" %s", instituicao);
            strcpy(participants[index].instituicao,instituicao);
            break;
        case 3:
            printf("Insira o codigo do novo evento: ");
            scanf(" %d", &eventoCodigo);
            participants[index].eventoCodigo = eventoCodigo;
            break;
    }
}