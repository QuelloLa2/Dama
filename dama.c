#include <stdio.h>

#define SI 1
#define NO 0

int a_presi = 0, b_presi = 0;

void setup(char tabella[8][8]);
void stampa(char tabella[8][8]);
int spostamento_minori(char tabella[8][8], char giocatore, char opposto, int x, int y);
void input(char tabella[8][8], char giocatore, char opposto);
int abs(int x);

int main()
{
    char tabella[8][8];
    printf("Benvenuti al gioco di Dama\n");
    setup(tabella);
    stampa(tabella);
    while (SI)
    {
        input(tabella, 'A', 'B');
        input(tabella, 'B', 'A');
    }
    return 0;
}

void setup(char tabella[8][8])
{
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            tabella[y][x] = ' ';
        }
    }
    for (int x = 1; x <= 7; x += 2)
    {
        tabella[7][x] = 'a';
        tabella[5][x] = 'a';
        tabella[1][x] = 'b';
    }

    for (int x = 0; x < 7; x += 2)
    {
        tabella[6][x] = 'a';
        tabella[2][x] = 'b';
        tabella[0][x] = 'b';
    }
}
void stampa(char tabella[8][8])
{
    int q = 0;
    printf("    ");
    for (int i = 0; i < 8; i++)
    {
        q++;
        printf(" (%d)", q - 1);
    }
    printf("\n    ");
    for (int i = 0; i < 33; i++)
    {
        printf("_");
    }
    printf("\n");
    for (int y = 0; y < 8; y++)
    {
        printf("(%d) | ", y);
        for (int x = 0; x < 8; x++)
        {
            if (x < 7)
            {
                printf("%c - ", tabella[y][x]);
            }
            else
            {
                printf("%c", tabella[y][x]);
            }
        }
        printf(" |\n");
    }
    printf("    ");
    for (int i = 0; i < 33; i++)
    {
        printf("⎺");
    }
    printf("\n");
    printf("Giocatore A tiene %d pedoni\n", a_presi);
    printf("Giocatore B tiene %d pedine\n", b_presi);
}
int spostamento_minori(char tabella[8][8], char giocatore, char opposto, int x, int y)
{
    int controllo_coordinate2 = (y - 2 >= 0 && y + 2 <= 7 && x - 2 >= 0 && x + 2 <= 7);
    int controllo_coordinate1 = (y - 1 >= 0 && y + 1 <= 7 && x - 1 >= 0 && x + 1 <= 7);
    if (giocatore == 'A')
    {
        // Controllo unita minori negativo/sinistra
        if (tabella[y - 1][x - 1] == (opposto + 32))
        {
            if (controllo_coordinate2)
            {
                tabella[y - 2][x - 2] = 'X';
            }
        }
        else if (tabella[y - 1][x - 1] == ' ')
        {
            if (controllo_coordinate1)
            {
                tabella[y - 1][x - 1] = 'X';
            }
        }
        // Controllo unita minori positivo/destra
        if (tabella[y - 1][x + 1] == (opposto + 32))
        {
            if (controllo_coordinate2)
            {
                tabella[y - 2][x + 2] = 'X';
            }
        }
        else if (tabella[y - 1][x + 1] == ' ')
        {
            if (controllo_coordinate1)
            {
                tabella[y - 1][x + 1] = 'X';
            }
        }
    }
    if (giocatore == 'B')
    {
        if (tabella[y + 1][x - 1] == (opposto + 32))
        {
            if (controllo_coordinate2 && tabella[y][x] != ' ')
            {
                tabella[y + 2][x - 2] = 'X';
            }
        }
        else if (tabella[y + 1][x - 1] == ' ')
        {
            if (controllo_coordinate1 && tabella[y][x] != ' ')
            {
                tabella[y + 1][x - 1] = 'X';
            }
        }
        // Controllo unita minori positivo/destra
        if (tabella[y + 1][x + 1] == (opposto + 32))
        {
            if (controllo_coordinate2 && tabella[y][x] != ' ')
            {
                tabella[y + 2][x + 2] = 'X';
            }
        }
        else if (tabella[y + 1][x + 1] == ' ')
        {
            if (controllo_coordinate1 && tabella[y][x] != ' ')
            {
                tabella[y + 1][x + 1] = 'X';
            }
        }
    }
    stampa(tabella);
    for (y = 0; y < 8; y++)
    {
        for (x = 0; x < 8; x++)
        {
            if (tabella[y][x] == 'X')
            {
                stampa(tabella);
                return 1;
            }
        }
    }

    return 0;
}
void input(char tabella[8][8], char giocatore, char opposto)
{
    int y, x, continua = NO, y1, x1, spostamento = 0;
    do
    {
        printf("Giocatore %c,Selezione la pedina tramite le coordinate\nCoordinate Y: ", giocatore);
        scanf("%d", &y);
        printf("Coordinate X: ");
        scanf("%d", &x);
        x--;
        y--;
        if (tabella[y][x] == ' ')
        {
            printf("Hai selezionato una casella vuota\n");
            continua = NO;
        }
        else if (tabella[y][x] == (giocatore + 32) || tabella[y][x] == giocatore)
        {
            continua = SI;
            spostamento = spostamento_minori(tabella, giocatore, opposto, x, y);
        }
        else if (tabella[y][x] == (opposto + 32) || tabella[y][x] == opposto)
        {
            printf("Hai selezionato una pedina non tua\n");
        }
    } while (x <= 0 && y <= 0 && y >= 7 && y >= 7 || continua == NO || spostamento == 0);
    do
    {
        printf("Giocatore %c,Scrivi le coordinate dello spostamento del \nCoordinate Y: ", giocatore);
        scanf("%d", &y1);
        printf("Coordinate X: ");
        scanf("%d", &x1);
        x1--;
        y1--;
        if (tabella[y1][x1] != 'X')
        {
            printf("Hai selezionato una casella vuota\n");
            continua = NO;
        }
        else if (tabella[y1][x1] == 'X')
        {
            continua = SI;
        }
    } while (x <= 0 && y <= 0 && y >= 7 && y >= 7 || continua == NO);
    if (tabella[y1][x1] == 'X')
    {
        if (abs(x - x1) == 2)
        {
            printf("Sono dentro\n Giocatore:%c\nABS:%d\n\n", giocatore, abs(x - x1));
            tabella[y1][x1] = tabella[y][x];
            tabella[y][x] = ' ';
            if (giocatore == 'A')
            {
                a_presi = a_presi + 1;
                tabella[y - 1][x + 1] = ' ';
            }
            else if (giocatore == 'B')
            {

                b_presi = b_presi + 1;
                tabella[y + 1][x - 1] = ' ';
            }
        }
        else if (abs(x - x1) == 1)
        {
            tabella[y1][x1] = tabella[y][x];
            tabella[y][x] = ' ';
        }
    }
    for (y = 0; y < 8; y++)
    {
        for (x = 0; x < 8; x++)
        {
            if (tabella[y][x] == 'X')
            {
                tabella[y][x] = ' ';
            }
        }
    }
    stampa(tabella);
}
int abs(int x)
{
    if (x < 0)
    {
        return x * -1;
    }
    return x;
}