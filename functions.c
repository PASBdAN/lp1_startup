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

int inserir_evento(
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

    printf("Evento criado com sucesso! (Pressione qualquer tecla para continuar)\n");
    return n;
};

void mostrar_evento(struct Evento evento){
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

void listar_eventos(
    struct  Evento evento[],
    int n    
){
    for(int i = 0; i < n; i++){
        mostrar_evento(evento[i]);
    }
};

int buscar_evento_por_codigo(struct Evento eventos[], int tamanho){
    int codigo;
    printf("Insira o codigo do evento: ");
    scanf(" %d",&codigo);
    for(int i = 0; i< tamanho;i++){
        if(eventos[i].codigo == codigo){
            printf("Evento encontrado:\n");
            mostrar_evento(eventos[i]);
            return i;
        }
    }
    printf("Nao foi encontrado nenhum evento com esse codigo!\n");
    return 9999;
};

int buscar_evento_por_nome(struct Evento eventos[], int tamanho){
    char nome[100];
    printf("Insira o nome do evento: ");
    scanf(" %s",nome);
    for(int i = 0; i< tamanho;i++){
        if(strcmp(eventos[i].nome,nome) == 0){
            printf("Evento encontrado:\n");
            mostrar_evento(eventos[i]);
            return i;
        }
    }
    printf("Nao foi encontrado nenhum evento com esse nome!\n");
    return 9999;
};

int deletar_evento(
    struct Evento evento[],
    int index,
    int n
){
    for(int i = index; i < n; i ++){
        evento[i] = evento[i+1];
    }
    n--;
    return n;
}