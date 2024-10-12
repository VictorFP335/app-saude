#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<locale.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

struct Usuario {
    char nome[100];
    int idade;
    int horasSono;
    double peso;
    double altura;
    char sexo;
};

struct EventoEsportivo {
    char nome[100];
    char data[20];
};

struct Alimento {
    char nome[100];
    int calorias;
};

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void centralizarTexto(const char *texto) {
    int larguraTela = 80; // Valor padrão

#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    larguraTela = csbi.dwSize.X;
#else
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    larguraTela = w.ws_col;
#endif

    int margemEsquerda = (larguraTela - strlen(texto)) / 2;

    // Imprime espaços em branco para centralizar
    for (int i = 0; i < margemEsquerda; i++) {
        printf(" ");
    }

    // Exibe o texto centralizado
    printf("%s\n", texto);
}

void cadastrarUsuario(struct Usuario *usuario) {
    limparTela();
    centralizarTexto("Cadastro de Usuário");

    printf("Digite seu nome completo: ");
    scanf("%s", usuario->nome);

    printf("Digite sua idade: ");
    scanf("%d", &usuario->idade);

    printf("Digite seu peso (em kg): ");
    scanf("%lf", &usuario->peso);

    printf("Digite sua altura (em metros): ");
    scanf("%lf", &usuario->altura);

    printf("Digite seu sexo (M/F): ");
    scanf(" %c", &usuario->sexo);

    printf("Cadastro concluído!\n");
}

void mostrarLembreteAgua() {
    limparTela();
    centralizarTexto("Lembrete de Água");

    printf("Lembre-se de beber água regularmente!\n");
}

void regularSono(struct Usuario *usuario) {
    limparTela();
    centralizarTexto("Regular Sono");

    printf("Quantas horas você dormiu na última noite? ");
    scanf("%d", &usuario->horasSono);

    if (usuario->horasSono < 7) {
        printf("Você deve tentar dormir pelo menos 7 horas por noite para uma boa saúde.\n");
    } else {
        printf("Ótimo! Você está dormindo o suficiente.\n");
    }
}

void horarioRefeicao() {
    time_t agora;
    struct tm *infoTempo;
    agora = time(NULL);
    infoTempo = localtime(&agora);
    int hora = infoTempo->tm_hour;

    limparTela();
    centralizarTexto("Horário de Refeição");

    if (hora >= 6 && hora < 12) {
        printf("Bom dia! É hora do café da manhã.\n");
    } else if (hora >= 12 && hora < 18) {
        printf("Boa tarde! É hora do almoço.\n");
    } else {
        printf("Boa noite! É hora do jantar.\n");
    }
}

void criarListaAlimentos(struct Alimento listaAlimentos[], int *totalCalorias) {
    int opcao;
    do {
        limparTela();
        centralizarTexto("Gerenciar Lista de Alimentos");

        printf("1. Adicionar alimento\n");
        printf("2. Visualizar lista de alimentos\n");
        printf("3. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome do alimento: ");
                scanf("%s", listaAlimentos[*totalCalorias].nome);
                printf("Digite a quantidade de calorias: ");
                scanf("%d", &listaAlimentos[*totalCalorias].calorias);
                (*totalCalorias)++;
                printf("Alimento adicionado!\n");
                break;
            case 2:
                if (*totalCalorias > 0) {
                    printf("\nLista de Alimentos:\n");
                    for (int i = 0; i < *totalCalorias; ++i) {
                        printf("%d. %s - %d calorias\n", i + 1, listaAlimentos[i].nome, listaAlimentos[i].calorias);
                    }
                    printf("Total de calorias: %d\n", *totalCalorias);
                } else {
                    printf("Lista de alimentos vazia.\n");
                }
                break;
            case 3:
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 3);
}

void mostrarEventosEsportivos(struct EventoEsportivo eventos[], int numEventos) {
    limparTela();
    centralizarTexto("Eventos Esportivos");

    for (int i = 0; i < numEventos; ++i) {
        printf("%d. %s - %s\n", i + 1, eventos[i].nome, eventos[i].data);
    }
}

int main() {
    setlocale(LC_ALL,"portuguese");
    system("color 2F");
    struct Usuario usuario;
    struct EventoEsportivo eventos[3];
    struct Alimento listaAlimentos[50];
    int totalCalorias = 0;

    strcpy(eventos[0].nome, "Corrida no Parque");
    strcpy(eventos[0].data, "10/11/2023");
    strcpy(eventos[1].nome, "Torneio de Tênis");
    strcpy(eventos[1].data, "15/11/2023");
    strcpy(eventos[2].nome, "Partida de Futebol");
    strcpy(eventos[2].data, "20/11/2023");

    int escolha;

    limparTela();
    centralizarTexto("Bem-vindo ao Programa de Saúde G Health");

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar Usuário\n");
        printf("2. Mostrar Lembrete para Beber Água\n");
        printf("3. Regular Sono\n");
        printf("4. Horário de Refeição\n");
        printf("5. Gerenciar Lista de Alimentos\n");
        printf("6. Mostrar Eventos Esportivos\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                cadastrarUsuario(&usuario);
                break;
            case 2:
                mostrarLembreteAgua();
                break;
            case 3:
                regularSono(&usuario);
                break;
            case 4:
                horarioRefeicao();
                break;
            case 5:
                criarListaAlimentos(listaAlimentos, &totalCalorias);
                break;
            case 6:
                mostrarEventosEsportivos(eventos, 3); // 3 é o número de eventos no array
                break;
            case 7:
                limparTela();
                centralizarTexto("Saindo do programa. Até mais!");
                printf("\a"); // Emitir som ao encerrar
                break;
            default:
                limparTela();
                centralizarTexto("Opção inválida. Tente novamente.");
        }

        if (escolha != 7) {
            // Aguarda um pouco para que o usuário possa ler a mensagem antes de voltar ao menu
            printf("\nPressione Enter para continuar...");
            getchar(); // Captura o caractere Enter
            getchar(); // Aguarda o próximo Enter
            limparTela();
            centralizarTexto("Bem-vindo ao Programa de Saúde G Health");
        }

    } while (escolha != 7);

    system("cls");
    return 0;
}
