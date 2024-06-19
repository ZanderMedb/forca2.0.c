#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "forca.h"

#define TAMANHO_PALAVRA 20

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;
int max_erros = 5;

int letraexiste(char letra) {
    for (size_t j = 0; j < strlen(palavrasecreta); j++) {
        if (letra == palavrasecreta[j]) {
            return 1;
        }
    }
    return 0;
}

int chuteserrados() {
    int erros = 0;
    for (int i = 0; i < chutesdados; i++) {
        if (!letraexiste(chutes[i])) {
            erros++;
        }
    }
    return erros;
}

int enforcado() {
    return chuteserrados() >= max_erros;
}

int ganhou() {
    for (size_t i = 0; i < strlen(palavrasecreta); i++) {
        if (!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }
    return 1;
}

void abertura() {
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");
}

void chuta() {
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    if (letraexiste(chute)) {
        printf("Voce acertou: a palavra tem a letra %c\n\n", chute);
    } else {
        printf("\nVoce errou: a palavra NAO tem a letra %c\n\n", chute);
    }

    chutes[chutesdados] = chute;
    chutesdados++;
}

int jachutou(char letra) {
    for (int j = 0; j < chutesdados; j++) {
        if (chutes[j] == letra) {
            return 1;
        }
    }
    return 0;
}

   void desenhaforca() {
    int erros = chuteserrados();

    printf("  _______       \n");
    printf(" |/      |      \n");

    if (erros >= 1) {
        printf(" |      (_)     \n");
    } else {
        printf(" |              \n");
    }

    if (erros >= 2) {
        printf(" |       |      \n");
    } else {
        printf(" |              \n");
    }

    if (erros >= 3) {
        printf(" |      /|\\    \n");
    } else if (erros >= 2) {
        printf(" |       |      \n");
    } else {
        printf(" |              \n");
    }

    if (erros >= 4) {
        printf(" |      /       \n");
    } else if (erros >= 3) {
        printf(" |      /|      \n");
    } else if (erros >= 2) {
        printf(" |       |      \n");
    } else {
        printf(" |              \n");
    }

    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");
}

void escolhepalavra(const char* arquivo) {
    FILE* f = fopen(arquivo, "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    int quantidade_palavras;
    fscanf(f, "%d", &quantidade_palavras);

    srand(time(NULL));
    int escolhida = rand() % quantidade_palavras;

    char palavra[TAMANHO_PALAVRA];
    for (int i = 0; i <= escolhida; i++) {
        fscanf(f, "%s", palavra);
    }

    strcpy(palavrasecreta, palavra);

    fclose(f);
}

void seleciona_dificuldade() {
    printf("Selecione a dificuldade:\n");
    printf("1 - Facil\n");
    printf("2 - Medio\n");
    printf("3 - Dificil\n");
    int dificuldade;
    scanf("%d", &dificuldade);

    switch (dificuldade) {
        case 1:
            max_erros = 5;
            break;
        case 2:
            max_erros = 3;
            break;
        case 3:
            max_erros = 2;
            break;
        default:
            printf("Opcao invalida!\n");
            exit(1);
    }
}

void seleciona_categoria(char *arquivo) {
    printf("Selecione a categoria:\n");
    printf("1 - Profissões\n");
    printf("2 - Países\n");
    printf("3 - Frutas\n");
    printf("4 - Filmes\n");
    printf("5 - Marcas\n");
    printf("6 - Nomes\n");
    int categoria;
    scanf("%d", &categoria);

    switch (categoria) {
        case 1:
            strcpy(arquivo, "profissoes.txt");
            break;
        case 2:
            strcpy(arquivo, "paises.txt");
            break;
        case 3:
            strcpy(arquivo, "frutas.txt");
            break;
        case 4:
            strcpy(arquivo, "filmes.txt");
            break;
        case 5:
            strcpy(arquivo, "marcas.txt");
            break;
        case 6:
            strcpy(arquivo, "nomes.txt");
            break;
        default:
            printf("Opcao invalida!\n");
            exit(1);
    }
}

int main() {
    char arquivo[TAMANHO_PALAVRA];

    abertura();
    seleciona_dificuldade();
    seleciona_categoria(arquivo);
    escolhepalavra(arquivo);

    int acertou = 0;
    int perdeu = 0;

    while (!perdeu && !acertou) {
        desenhaforca();

        printf("\n");
        for (size_t i = 0; i < strlen(palavrasecreta); i++) {
            if (jachutou(palavrasecreta[i])) {
                printf("%c ", palavrasecreta[i]);
            } else {
                printf("_ ");
            }
        }
        printf("\n");

        chuta();

        perdeu = enforcado();
        acertou = ganhou();
    }

    if (acertou) {
        printf("A palavra era **%s**\n\n", palavrasecreta);
        printf("      '._==_==_=_.'     \n");
        printf("     .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::..'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
        printf("Parabens, voce ganhou!\n");
    } else {
        printf("\nPuxa, voce foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta);
        printf("    _______________         \n");
        printf("   /               \\       \n");
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    printf("FIM");

    return 0;
}