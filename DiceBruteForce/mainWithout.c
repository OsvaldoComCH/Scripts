#include <stdio.h>
typedef unsigned char uint8;
typedef signed char int8;
uint8 Board[8][8] = {
    {5, 5, 5, 5, 5, 5, 5, 0},
    {5, 5, 5, 5, 5, 5, 0, 5},
    {5, 5, 5, 5, 5, 0, 5, 5},
    {5, 5, 5, 5, 0, 5, 5, 5},
    {5, 5, 5, 0, 5, 5, 5, 5},
    {5, 5, 0, 5, 5, 5, 5, 5},
    {5, 0, 5, 5, 5, 5, 5, 5},
    {0, 5, 5, 5, 5, 5, 5, 5}
};

/*
uint8 Board[8][8] = {
    {5, 2, 0, 0, 1, 1, 2, 0},
    {5, 3, 5, 2, 3, 1, 3, 0},
    {2, 1, 3, 1, 3, 4, 1, 2},
    {1, 3, 3, 3, 1, 0, 1, 2},
    {0, 1, 2, 3, 1, 1, 1, 4},
    {4, 4, 3, 3, 4, 0, 4, 4},
    {2, 2, 3, 3, 2, 3, 1, 1},
    {0, 1, 2, 5, 1, 3, 0, 1}
};
*/

typedef struct Dice
{
    int8 x, y;
    uint8 Step;
    uint8 PossibleDice;
    uint8 Dir;
} Dice;

typedef struct DiceSet
{
    Dice D[6];
} DiceSet;

typedef struct Player
{
    uint8 x, y;
} Player;

void SetDirection(Dice * D, uint8 Dir)
{
    D->Dir = Dir;
    switch(Dir)
    {
        case 0:
        {
            D->x = 0;
            D->y = -D->Step;
        }
        break;
        case 1:
        {
            D->x = D->Step;
            D->y = -D->Step;
        }
        break;
        case 2:
        {
            D->x = D->Step;
            D->y = 0;
        }
        break;
        case 3:
        {
            D->x = D->Step;
            D->y = D->Step;
        }
        break;
        case 4:
        {
            D->x = 0;
            D->y = D->Step;
        }
        break;
        case 5:
        {
            D->x = -D->Step;
            D->y = D->Step;
        }
        break;
        case 6:
        {
            D->x = -D->Step;
            D->y = 0;
        }
        break;
        case 7:
        {
            D->x = -D->Step;
            D->y = -D->Step;
        }
        break;
    }
}

void DirectionGenerate(DiceSet * Ds, int Seed)
{
    uint8 AvailableDir = 0;

    int origin = 2520;
    uint8 Dir = Seed / origin;
    Seed %= origin;
    SetDirection(&Ds->D[0], Dir);

    AvailableDir |= 1 << Dir;

    int8 Desloc;


    uint8 i;

    for(int j=7; j>2; j--)
    {
        origin /= j;
        Desloc = Seed / origin;
        Seed %= origin;
        for(i = 0; i < 8 && Desloc >= 0; i++)
        {
            Desloc -= ((AvailableDir >> i) ^ 1) & 1;
        }
        SetDirection(&Ds->D[8-j], i-1);
        AvailableDir |= 1 << i-1;
    }
}

int PlayGame(DiceSet * Ds, Player * P)
{
    Player Dest;
    if(Ds->D[0].Dir >> 2)
    {
        P->x = 7;
        P->y = 0;
        Dest.x = 0;
        Dest.y = 7;
    }else
    {
        P->x = 0;
        P->y = 7;
        Dest.x = 7;
        Dest.y = 0;
    }

    for(int i = 0; i < 64; ++i)
    {
        int8 Dice = Board[P->y][P->x];
        P->x += Ds->D[Dice].x;
        P->y += Ds->D[Dice].y;
        if(P->x == Dest.x && P->y == Dest.y)
        {
            return 0;
        }
        if(P->x > 7 || P->y > 7)
        {
            return 1;
        }
    }
    return 2;
}

int main()
{
    FILE * File = fopen("Results.txt", "w");
    Player P;
    DiceSet Dados;
    Dados.D[0].Step = 1;
    Dados.D[1].Step = 2;
    Dados.D[2].Step = 3;
    Dados.D[3].Step = 4;
    Dados.D[4].Step = 5;
    Dados.D[5].Step = 6;

    for(int i = 0; i < 20160; ++i)
    {
        DirectionGenerate(&Dados, i);

        if(PlayGame(&Dados, &P) == 0)
        {
            fprintf(File, "%i,%i,%i,%i,%i,%i\n", 
                Dados.D[0].Dir,
                Dados.D[1].Dir,
                Dados.D[2].Dir,
                Dados.D[3].Dir,
                Dados.D[4].Dir,
                Dados.D[5].Dir
            );
        }
    }
}