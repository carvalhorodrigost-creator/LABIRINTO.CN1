#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

#define N 10

#define VERDE "\033[32m"
#define VERMELHO "\033[31m"
#define AMARELO "\033[33m"
#define AZUL "\033[34m"
#define MAGENTA "\033[35m"
#define CIANO "\033[36m"
#define RESET "\033[0m"

void mostrarLabirinto(int labirinto[N][N], int x, int y);
int movimentoValido(int labirinto[N][N], int x, int y);
void somMovimento(char comando);
void somParede();
void somArmadilha();
void somVitoria();
void mostrarInformacoes(int x, int y, int movimentos, int pontos);

int main()
{
    int labirinto[N][N] =
    {
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 1, 2, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 2, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, -1}
    };

    int x = 0;
    int y = 0;
    int movimentos = 0;
    int pontos = 0;
    char comando;

    while (1)
    {
        system("cls");

        printf(CIANO);
        printf("=====================================\n");
        printf("         LABIRINTO DO MEDO\n");
        printf("=====================================\n");
        printf(RESET);

        printf("W = Cima | S = Baixo\n");
        printf("A = Esquerda | D = Direita\n\n");

        printf(VERDE);
        printf("@ = Jogador  ");
        printf(RESET);

        printf(VERMELHO);
        printf("X = Parede  ");
        printf(RESET);

        printf(AZUL);
        printf("O = Saida  ");
        printf(RESET);

        printf(MAGENTA);
        printf("^ = Armadilha");
        printf(RESET);

        printf("\n\n");

        mostrarLabirinto(labirinto, x, y);
        mostrarInformacoes(x, y, movimentos, pontos);

        if (labirinto[x][y] == -1)
        {
            printf("\n");

            printf(VERDE);
            printf("=====================================\n");
            printf("        PARABENS, VOCE ESTA LIVRE!\n");
            printf("=====================================\n");
            printf(RESET);

            printf("Movimentos: %d\n", movimentos);
            printf("Pontuacao final: %d\n", pontos);

            somVitoria();

            break;
        }

        printf("\nDigite um movimento: ");
        scanf(" %c", &comando);

        comando = toupper(comando);

        int novoX = x;
        int novoY = y;

        if (comando == 'W')
        {
            novoX--;
        }
        else if (comando == 'S')
        {
            novoX++;
        }
        else if (comando == 'A')
        {
            novoY--;
        }
        else if (comando == 'D')
        {
            novoY++;
        }
        else
        {
            printf(AMARELO);
            printf("\nTecla invalida!\n");
            printf(RESET);

            Beep(200, 150);

            system("pause");
            continue;
        }

        movimentos++;

        if (movimentoValido(labirinto, novoX, novoY) == 0)
        {
            printf(VERMELHO);
            printf("\nVoce bateu em uma parede!\n");
            printf("-5 pontos\n");
            printf(RESET);

            pontos -= 5;

            somParede();

            system("pause");
            continue;
        }

        x = novoX;
        y = novoY;

        pontos += 10;

        somMovimento(comando);

        if (labirinto[x][y] == 2)
        {
            printf(VERMELHO);
            printf("\n");
            printf("CUIDADO! Voce caiu em uma armadilha!\n");
            printf("-15 pontos\n");
            printf(RESET);

            pontos -= 15;

            somArmadilha();

            x = 0;
            y = 0;

            printf(AMARELO);
            printf("Voce voltou para o inicio.\n");
            printf(RESET);

            system("pause");
        }
    }

    return 0;
}

void mostrarLabirinto(int labirinto[N][N], int x, int y)
{
    int i;
    int j;

    printf("     ");

    for (j = 0; j < N; j++)
    {
        printf("%d ", j + 1);
    }

    printf("\n");

    for (i = 0; i < N; i++)
    {
        printf("%2d   ", i + 1);

        for (j = 0; j < N; j++)
        {
            if (i == x && j == y)
            {
                printf(VERDE);
                printf("@ ");
                printf(RESET);
            }
            else if (labirinto[i][j] == 1)
            {
                printf(VERMELHO);
                printf("X ");
                printf(RESET);
            }
            else if (labirinto[i][j] == -1)
            {
                printf(AZUL);
                printf("O ");
                printf(RESET);
            }
            else if (labirinto[i][j] == 2)
            {
                printf(MAGENTA);
                printf("^ ");
                printf(RESET);
            }
            else
            {
                printf(". ");
            }
        }

        printf("\n");
    }
}

int movimentoValido(int labirinto[N][N], int x, int y)
{
    if (x < 0 || x >= N)
    {
        return 0;
    }

    if (y < 0 || y >= N)
    {
        return 0;
    }

    if (labirinto[x][y] == 1)
    {
        return 0;
    }

    return 1;
}

void somMovimento(char comando)
{
    if (comando == 'W')
    {
        Beep(900, 70);
    }
    else if (comando == 'S')
    {
        Beep(500, 70);
    }
    else if (comando == 'A')
    {
        Beep(700, 70);
    }
    else if (comando == 'D')
    {
        Beep(800, 70);
    }
}

void somParede()
{
    Beep(250, 200);
    Beep(180, 300);
}

void somArmadilha()
{
    Beep(500, 150);
    Beep(350, 150);
    Beep(200, 350);
}

void somVitoria()
{
    Beep(523, 150);
    Beep(659, 150);
    Beep(784, 150);
    Beep(1046, 400);
}

void mostrarInformacoes(int x, int y, int movimentos, int pontos)
{
    printf("\n");
    printf("Linha: %d | Coluna: %d\n", x + 1, y + 1);
    printf("Movimentos: %d\n", movimentos);
    printf("Pontos: %d\n", pontos);
}
// dá um 10 aí professor. pls
