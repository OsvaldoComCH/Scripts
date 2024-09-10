#include <stdio.h>
int main()
{
    char Matrix[3][3] = {
        {'_','_','_'},
        {'_','_','_'},
        {'_','_','_'}
    }, Player = 'X';
    int x;
    while(1)
    {
        printf("Player: %c\n", Player);
        printf("%c %c %c\t1 2 3\n%c %c %c\t4 5 6\n%c %c %c\t7 8 9\n", Matrix[0][0], Matrix[0][1],
        Matrix[0][2], Matrix[1][0], Matrix[1][1], Matrix[1][2], Matrix[2][0], Matrix[2][1], Matrix[2][2]);
        scanf("%i", &x);
        if(--x > 8){x = 8;}else
        if(x < 0){x = 0;}
        if(Matrix[x/3][x%3] == '_')
        {
            Matrix[x/3][x%3] = Player;
        }else
        {
            continue;
        }
        if(
            (Matrix[0][0] != '_' && Matrix[0][0] == Matrix[0][1] && Matrix[0][1] == Matrix[0][2]) ||
            (Matrix[1][0] != '_' && Matrix[1][0] == Matrix[1][1] && Matrix[1][1] == Matrix[1][2]) ||
            (Matrix[2][0] != '_' && Matrix[2][0] == Matrix[2][1] && Matrix[2][1] == Matrix[2][2]) ||
            (Matrix[0][0] != '_' && Matrix[0][0] == Matrix[1][0] && Matrix[1][0] == Matrix[2][0]) ||
            (Matrix[0][1] != '_' && Matrix[0][1] == Matrix[1][1] && Matrix[1][1] == Matrix[2][1]) ||
            (Matrix[0][2] != '_' && Matrix[0][2] == Matrix[1][2] && Matrix[1][2] == Matrix[2][2]) ||
            (Matrix[0][0] != '_' && Matrix[0][0] == Matrix[1][1] && Matrix[1][1] == Matrix[2][2]) ||
            (Matrix[0][2] != '_' && Matrix[0][2] == Matrix[1][1] && Matrix[1][1] == Matrix[2][0])
        )
        {
            printf("%c %c %c\t1 2 3\n%c %c %c\t4 5 6\n%c %c %c\t7 8 9\n", Matrix[0][0], Matrix[0][1],
            Matrix[0][2], Matrix[1][0], Matrix[1][1], Matrix[1][2], Matrix[2][0], Matrix[2][1], Matrix[2][2]);
            printf("Winner: %c", Player);
            break;
        }
        if(Player == 'X'){Player = 'O';}else{Player = 'X';}
    }
}