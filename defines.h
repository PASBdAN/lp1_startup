struct Evento{
    int codigo;
    char nome[100];
    char data[20];
    char local[100];
    char categoria[50];
    int vagas;
    int vagasDisponiveis;
};

struct Participante{
    int codigo;
    char nome[100];
    char email[100];
    char instituicao[100];
    int eventoCodigo;
};

typedef struct{
    char* description;
    int menu_id;
    struct Evento event;
    struct Participante participant;
}MenuOption;

typedef struct{
    int id;
    char* title;
    MenuOption* options;
    int options_size;
    int selection;
}Menu;