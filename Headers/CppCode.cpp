//We program mostly in english, but sometimes in C++
#include <iostream>
#include <cstring>

typedef struct 
{
    int x;
    int y;
} StructA;

typedef struct 
{
    int a;
    int b;
    char c[10];
} StructB;

int Sum(StructA * A)
{
    return A->x + A->y;
}

//Get absolute value of integer
#define absi(i) ((((int) i) ^ ((((int) i) >> 31))) - ((((int) i) >> 31)))


int GetValue()
{
    return 1;
}

int GetValue1()
{
    return 1;
}

int GetValue2()
{
    return 2;
}

int main()
{
    StructA A;
    A.x = 0x8000ffff;

    //High Word
    std::cout << *((unsigned short *) &A.x + 1) << "\n";
    //Low Word
    std::cout << *((unsigned short *) &A.x) << "\n";

    float F = 10;
    //Flip sign bit of float
    *(int *) &F = *((int *) &F) ^ 0x80000000;
    std::cout << F << "\n";

    StructB B;
    B.a = 10;
    B.b = 5;
    std::strcpy(B.c, "Bom dia");

    //Convert pointer type of different structs
    std::cout << Sum((StructA *) &B) << "\n";

    std::cout << absi(-60) << "\n";

    std::cout << absi(40) << "\n";
}