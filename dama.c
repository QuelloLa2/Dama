#include <stdio.h>

#define SI 1
#define NO 0

int a_presi = 0, b_presi = 0;

void setup(char tabella[8][8]);
void stampa(char tabella[8][8]);
int spostamento_minori(char tabella[8][8], char giocatore, char opposto, int x, int y, int scelta);
int spostamento_maggiore(char tabella[8][8], char giocatore, char opposto, int x, int y, int scelta);
void input(char tabella[8][8], char giocatore, char opposto);
int abs(int x);
int vittoria(char tabella[8][8]);

int main()
{
    char tabella[8][8];
    printf("Benvenuti al gioco di Dama\n");
    setup(tabella);
    // tabella[1][7] = 'a';
    // tabella[5][3] = 'A';
    // tabella[4][4] = 'B';
    // tabella[3][3] = 'a';
    // tabella[3][5] = 'a';
    // tabella[2][6] = 'a';
    // tabella[2][2] = 'a';
    stampa(tabella);
    while (SI)
    {
        input(tabella, 'A', 'B');
        if (vittoria(tabella) == 1)
        {
            printf("Il Giocatore A ha vinto!!\n");
            return 0;
        }
        if (vittoria(tabella) == 2)
        {
            printf("Il Giocatore B ha vinto!!\n");
            return 0;
        }
        input(tabella, 'B', 'A');
        if (vittoria(tabella) == 1)
        {
            printf("Il Giocatore A ha vinto!!\n");
            return 0;
        }
        if (vittoria(tabella) == 2)
        {
            printf("Il Giocatore B ha vinto!!\n");
            return 0;
        }
    }
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
int spostamento_minori(char tabella[8][8], char giocatore, char opposto, int x, int y, int scelta)
{
    int controllo_coordinate2_negativo = (y - 2 >= 0 && x - 2 >= 0);
    int controllo_coordinate1_negativo = (y - 1 >= 0 && x - 1 >= 0);
    int controllo_coordinate2_positivo = (y + 2 <= 7 && x + 2 <= 7);
    int controllo_coordinate1_positivo = (y + 1 <= 7 && x + 1 <= 7);

    if (giocatore == 'A')
    {
        // Controllo unita minori negativo/sinistra
        if (tabella[y - 1][x - 1] == (opposto + 32))
        {
            if (controllo_coordinate2_negativo && tabella[y - 2][x - 2] == ' ')
            {
                tabella[y - 2][x - 2] = 'X';
            }
        }
        else if (tabella[y - 1][x - 1] == ' ')
        {
            if (controllo_coordinate1_negativo)
            {
                tabella[y - 1][x - 1] = 'X';
            }
        }
        // Controllo unita minori positivo/destra
        if (tabella[y - 1][x + 1] == (opposto + 32))
        {
            if (controllo_coordinate2_positivo && tabella[y - 2][x + 2] == ' ')
            {
                tabella[y - 2][x + 2] = 'X';
            }
        }
        else if (tabella[y - 1][x + 1] == ' ')
        {
            if (controllo_coordinate1_positivo)
            {
                tabella[y - 1][x + 1] = 'X';
            }
        }
    }
    if (giocatore == 'B')
    {
        if (tabella[y + 1][x - 1] == (opposto + 32))
        {
            if (controllo_coordinate2_negativo && tabella[y + 2][x - 2] == ' ')
            {
                tabella[y + 2][x - 2] = 'X';
            }
        }
        else if (tabella[y + 1][x - 1] == ' ')
        {
            if (controllo_coordinate1_negativo)
            {
                tabella[y + 1][x - 1] = 'X';
            }
        }
        // Controllo unita minori positivo/destra
        if (tabella[y + 1][x + 1] == (opposto + 32))
        {
            if (controllo_coordinate2_positivo && tabella[y + 2][x + 2] == ' ')
            {
                tabella[y + 2][x + 2] = 'X';
            }
        }
        else if (tabella[y + 1][x + 1] == ' ')
        {
            if (controllo_coordinate1_positivo)
            {
                tabella[y + 1][x + 1] = 'X';
            }
        }
    }
    for (y = 0; y < 8; y++)
    {
        for (x = 0; x < 8; x++)
        {
            if (tabella[y][x] == 'X')
            {
                if (scelta == 1)
                {
                    stampa(tabella);
                }
                return 1;
            }
        }
    }
    return 0;
}
int spostamento_maggiore(char tabella[8][8], char giocatore, char opposto, int x, int y, int scelta)
{
    int controllo_coordinate2_negativo = (y - 2 >= 0 && x - 2 >= 0);
    int controllo_coordinate1_negativo = (y - 1 >= 0 && x - 1 >= 0);
    int controllo_coordinate2_positivo = (y + 2 <= 7 && x + 2 <= 7);
    int controllo_coordinate1_positivo = (y + 1 <= 7 && x + 1 <= 7);

    if (tabella[y - 1][x - 1] == (opposto + 32))
    {
        if (controllo_coordinate2_negativo && tabella[y - 2][x - 2] == ' ')
        {
            tabella[y - 2][x - 2] = 'X';
        }
    }
    else if (tabella[y - 1][x - 1] == ' ')
    {
        if (controllo_coordinate1_negativo)
        {
            tabella[y - 1][x - 1] = 'X';
        }
    }
    if (tabella[y - 1][x + 1] == (opposto + 32))
    {
        if (controllo_coordinate2_positivo && tabella[y - 2][x + 2] == ' ')
        {
            tabella[y - 2][x + 2] = 'X';
        }
    }
    else if (tabella[y - 1][x + 1] == ' ')
    {
        if (controllo_coordinate1_positivo)
        {
            tabella[y - 1][x + 1] = 'X';
        }
    }
    if (tabella[y + 1][x - 1] == (opposto + 32))
    {
        if (controllo_coordinate2_positivo && tabella[y + 2][x - 2] == ' ')
        {
            tabella[y + 2][x - 2] = 'X';
        }
    }
    else if (tabella[y + 1][x - 1] == ' ')
    {
        if (controllo_coordinate1_positivo)
        {
            tabella[y + 1][x - 1] = 'X';
        }
    }
    if (tabella[y + 1][x + 1] == (opposto + 32))
    {
        if (controllo_coordinate2_positivo && tabella[y + 2][x + 2] == ' ')
        {
            tabella[y + 2][x + 2] = 'X';
        }
    }
    else if (tabella[y + 1][x + 1] == ' ')
    {
        if (controllo_coordinate1_positivo)
        {
            tabella[y + 1][x + 1] = 'X';
        }
    }
    for (y = 0; y < 8; y++)
    {
        for (x = 0; x < 8; x++)
        {
            if (tabella[y][x] == 'X')
            {
                if (scelta == 1)
                {
                    stampa(tabella);
                }
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
            if (tabella[y][x] == giocatore)
            {
                spostamento = spostamento_maggiore(tabella, giocatore, opposto, x, y, 1);
            }
            else if (tabella[y][x] == giocatore + 32)
            {
                spostamento = spostamento_minori(tabella, giocatore, opposto, x, y, 1);
            }
        }
        else if (tabella[y][x] == (opposto + 32) || tabella[y][x] == opposto)
        {
            printf("Hai selezionato una pedina non tua\n");
        }
    } while (x <= 0 && y <= 0 && x >= 7 && y >= 7 || continua == NO || spostamento == 0);
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
            tabella[y1][x1] = tabella[y][x];
            tabella[y][x] = ' ';
            if (giocatore == 'A')
            {
                if (tabella[y1 + 1][x1 + 1] == (opposto + 32))
                {
                    tabella[y1 + 1][x1 + 1] = ' ';
                    a_presi = a_presi + 1;
                }
                else if (tabella[y1 + 1][x1 - 1] == (opposto + 32))
                {
                    tabella[y1 + 1][x1 - 1] = ' ';
                    a_presi = a_presi + 1;
                }
            }
            else if (giocatore == 'B')
            {
                if (tabella[y1 - 1][x1 + 1] == (opposto + 32))
                {
                    tabella[y1 - 1][x1 + 1] = ' ';
                    b_presi = b_presi + 1;
                }
                else if (tabella[y1 - 1][x1 - 1] == (opposto + 32))
                {
                    tabella[y1 - 1][x1 - 1] = ' ';
                    b_presi = b_presi + 1;
                }
            }
        }
        else if (abs(x - x1) == 1)
        {
            tabella[y1][x1] = tabella[y][x];
            tabella[y][x] = ' ';
        }
    }
    if (giocatore == 'A')
    {

        for (x = 0; x < 8; x++)
        {
            if (tabella[0][x] == (giocatore + 32))
            {
                tabella[0][x] = giocatore;
            }
        }
    }
    if (giocatore == 'B')
    {
        for (x = 0; x < 8; x++)
        {
            if (tabella[7][x] == (giocatore + 32))
            {
                tabella[7][x] = giocatore;
            }
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
int vittoria(char tabella[8][8])
{
    int controllo_a = 0, controllo_b = 0;
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (tabella[y][x] == 'A' || tabella[y][x] == 'a')
            {
                controllo_a++;
            }
            if (tabella[y][x] == 'B' || tabella[y][x] == 'b')
            {
                controllo_b++;
            }
        }
    }
    if (controllo_a == 1)
    {
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                if (tabella[y][x] == 'a')
                {
                    if (spostamento_minori(tabella, 'A', 'B', x, y, 0) == 0)
                    {
                        return 2;
                    }
                }
                if (tabella[y][x] == 'A')
                {
                    if (spostamento_maggiore(tabella, 'A', 'B', x, y, 0) == 0)
                    {
                        return 2;
                    }
                }
            }
        }
    }
    if (controllo_b == 1)
    {
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                if (tabella[y][x] == 'b')
                {
                    if (spostamento_minori(tabella, 'B', 'A', x, y, 0) == 0)
                    {
                        return 1;
                    }
                }
                if (tabella[y][x] == 'B')
                {
                    if (spostamento_maggiore(tabella, 'B', 'A', x, y, 0) == 0)
                    {
                        return 1;
                    }
                }
            }
        }
    }
    if (controllo_a == 0)
    {
        return 1;
    }
    if (controllo_b == 0)
    {
        return 2;
    }
    return 0;
}