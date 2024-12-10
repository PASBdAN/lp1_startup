#include "defines.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

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

void save_events_to_file(char filepath[], int length, struct Evento events[]){
    FILE *arquivo;
    arquivo = fopen(filepath,"w");
    fclose(arquivo);
    char linha[500], *palavra;
    int column = 0, i = 0;
    for(int i = 0; i < length; i++){
        sprintf(
            linha,
            "%d;%s;%s;%s;%s;%d;%d\n",
            events[i].codigo,
            events[i].nome,
            events[i].data,
            events[i].local,
            events[i].categoria,
            events[i].vagas,
            events[i].vagasDisponiveis
        );
        arquivo = fopen(filepath,"a");
        fprintf(arquivo,linha);
        fclose(arquivo);
    }
}

int read_events_files(char filepath[], struct Evento events[]){
    FILE *arquivo;
    char linha[500], *palavra;
    int column = 0, i = 0;

    arquivo = fopen(filepath,"r");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        palavra = strtok(linha,";");
        while(palavra!=NULL){
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
            palavra = strtok(NULL,";");
            column++;
        }
        column = 0;
        i++;
    }
    return i;
}

void save_participants_to_file(char filepath[], int length, struct Participante participants[]){
    FILE *arquivo;
    arquivo = fopen(filepath,"w");
    fclose(arquivo);
    char linha[500], *palavra, buffer[20];
    int column = 0, i = 0;
    for(int i = 0; i < length; i++){
        sprintf(
            linha,
            "%d;%s;%s;%s;%d\n",
            participants[i].codigo,
            participants[i].nome,
            participants[i].email,
            participants[i].instituicao,
            participants[i].eventoCodigo
        );
        arquivo = fopen(filepath,"a");
        fprintf(arquivo,linha);
        fclose(arquivo);
    }
}

int read_participants_file(char filepath[], struct Participante participants[]){
    FILE *arquivo;
    char linha[500], *palavra;
    int column = 0, i = 0;

    arquivo = fopen(filepath,"r");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
        palavra = strtok(linha,";");
        while(palavra!=NULL){
            printf("%s",palavra);
            switch(column){
                case 0:
                    participants[i].codigo = atoi(palavra);
                    break;
                case 1:
                    strcpy(participants[i].nome,palavra);
                    break;
                case 2:
                    strcpy(participants[i].email, palavra);
                    break;
                case 3:
                    strcpy(participants[i].instituicao, palavra);
                    break;
                case 4:
                    participants[i].eventoCodigo = atoi(palavra);
                    break;
                default:
                    break;
            }
            palavra = strtok(NULL,";");
            column++;
        }
        column = 0;
        i++;
    }
    return i;
}

int insert_event(
    struct Evento events[],
    int length_events
){
    char nome[100], data[20];
    char local[100], categoria[50];
    int vagas, vagasDisponiveis, codigo = 0;

    // LOOP PARA INSERIR UM CODIGO UNICO
    for(int i = 0; i < length_events; i++){
        if(events[i].codigo >= codigo){
            codigo = events[i].codigo;
        }
    }
    codigo++;

    printf("Insira um nome: ");
    scanf(" %s",nome);
    strcpy(events[length_events].nome, nome);

    printf("Insira uma data: ");
    scanf(" %s",data);
    strcpy(events[length_events].data, data);

    printf("Insira o local: ");
    scanf(" %s",local);
    strcpy(events[length_events].local, local);

    printf("Insira a categoria: ");
    scanf(" %s",categoria);
    strcpy(events[length_events].categoria, categoria);

    printf("Insira a vaga: ");
    scanf(" %d",&vagas);
    events[length_events].vagas = vagas;

    events[length_events].vagasDisponiveis = vagas;

    events[length_events].codigo = codigo;
    
    length_events++;

    save_events_to_file("events.csv",length_events,events);

    return length_events;
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

int search_event_by_code(struct Evento events[], int length, int codigo){
    for(int i = 0; i< length;i++){
        if(events[i].codigo == codigo){
            show_event(events[i]);
            return i;
        }
    }
    return 9999;
};

int search_event_by_name(struct Evento events[], int length, char nome[]){
    for(int i = 0; i< length;i++){
        if(strcmp(events[i].nome,nome) == 0){
            show_event(events[i]);
            return i;
        }
    }
    return 9999;
};

void edit_event(struct Evento events[], int index, int column){
    char nome[100], data[20], local[100], categoria[50];
    int vagas;
    switch(column){
        case 0:
            printf("Insira o novo nome: ");
            scanf(" %s", nome);
            strcpy(events[index].nome,nome);
            break;
        case 1:
            printf("Insira a nova data: ");
            scanf(" %s", data);
            strcpy(events[index].data,data);
            break;
        case 2:
            printf("Insira o novo local: ");
            scanf(" %s", local);
            strcpy(events[index].local,local);
            break;
        case 3:
            printf("Insira a nova categoria: ");
            scanf(" %s", categoria);
            strcpy(events[index].categoria,categoria);
            break;
        case 4:
            printf("Insira a nova quantidade de vagas: ");
            scanf(" %d", &vagas);
            events[index].vagas = vagas;
            break;
    }
}

int delete_event(
    struct Evento events[],
    int index,
    int length
){
    for(int i = index; i < length; i ++){
        events[i] = events[i+1];
    }
    length--;
    save_events_to_file("events.csv",length,events);
    return length;
}

int insert_participant(
    struct Participante participants[],
    int length_participants,
    struct Evento events[],
    int length_events
){
    char nome[100], email[100], instituicao[100];
    int eventoCodigo, codigo = 0;

    printf("Insira o codigo do evento do participante: ");
    scanf(" %d",&eventoCodigo);
    int event_index = search_event_by_code(events,length_events,eventoCodigo);
    if(event_index==9999){
        printf("O evento solicitado não existe!\n");
        return length_participants;
    }
    if(events[event_index].vagasDisponiveis == 0){
        printf("O evento nao tem vagas disponiveis para registrar esse participante!\n");
        return length_participants;
    }
    events[event_index].vagasDisponiveis--;
    participants[length_participants].eventoCodigo = eventoCodigo;

    // LOOP PARA INSERIR UM CODIGO UNICO
    for(int i = 0; i < length_participants; i++){
        if(participants[i].codigo >= codigo){
            codigo = participants[i].codigo;
        }
    }
    codigo++;

    printf("Insira o nome do participante: ");
    scanf(" %s",nome);
    strcpy(participants[length_participants].nome, nome);

    printf("Insira o email do participantse: ");
    scanf(" %s",email);
    strcpy(participants[length_participants].email, email);

    printf("Insira a instituicao do participante: ");
    scanf(" %s",instituicao);
    strcpy(participants[length_participants].instituicao, instituicao);

    participants[length_participants].codigo = codigo;
    
    length_participants++;

    save_participants_to_file("participants.csv",length_participants,participants);

    return length_participants;
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

void edit_participant(struct Participante participants[], int index, int column, struct Evento events[], int length_events){
    char nome[100], email[100], instituicao[100];
    int eventoCodigo;
    switch(column){
        case 0:
            printf("Insira o novo nome do participante: ");
            scanf(" %s", nome);
            strcpy(participants[index].nome,nome);
            break;
        case 1:
            printf("Insira o novo email do participante: ");
            scanf(" %s", email);
            strcpy(participants[index].email,email);
            break;
        case 2:
            printf("Insira a nova instituicao do participante: ");
            scanf(" %s", instituicao);
            strcpy(participants[index].instituicao,instituicao);
            break;
        case 3:
            printf("Insira o codigo do novo evento do participante: ");
            scanf(" %d", &eventoCodigo);
            int event_index = search_event_by_code(events,length_events,eventoCodigo);
            if(event_index==9999){
                printf("O evento solicitado não existe!\n");
            } else {
                if(events[event_index].vagasDisponiveis == 0) {
                    printf("Na ha vagas disponiveis para este events!\n");
                } else {
                    events[event_index].vagasDisponiveis--;
                    event_index = search_event_by_code(events,length_events,participants[index].eventoCodigo);
                    events[event_index].vagasDisponiveis++;
                }
            }
            participants[index].eventoCodigo = eventoCodigo;
            break;
    }
}

int search_participant_by_code(struct Participante participants[], int length, int codigo){
    for(int i = 0; i< length;i++){
        if(participants[i].codigo == codigo){
            show_participant(participants[i]);
            return i;
        }
    }
    return 9999;
};

int search_participant_by_name(struct Participante participants[], int length, char nome[]){
    for(int i = 0; i< length;i++){
        if(strcmp(participants[i].nome,nome) == 0){
            show_participant(participants[i]);
            return i;
        }
    }
    return 9999;
};

int search_participant_by_email(struct Participante participants[], int length, char email[]){
    for(int i = 0; i< length;i++){
        if(strcmp(participants[i].email,email) == 0){
            show_participant(participants[i]);
            return i;
        }
    }
    return 9999;
};

int delete_participant(
    struct Participante participants[],
    int length_participants,
    int index,
    struct Evento events[],
    int length_events
){

    int event_index = search_event_by_code(events,length_events,participants[index].eventoCodigo);
    // if((events[event_index].vagasDisponiveis != events[event_index].vagas) && (event_index!=9999)){
    events[event_index].vagasDisponiveis++;
    //}
    
    for(int i = index; i < length_participants; i ++){
        participants[i] = participants[i+1];
    }
    length_participants--;
    save_participants_to_file("participants.csv",length_participants,participants);
    
    return length_participants;
}