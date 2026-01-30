//We program mostly in english, but sometimes in C++
#include <iostream>
#include <cstring>
#include <ctime>

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

int RNG()
{
    static int Random = time(NULL);
    Random = Random * 48271 % 2147483647;
    return Random;
}

//Get absolute value of integer
#define absi(i) ((((int) i) ^ ((((int) i) >> 31))) - ((((int) i) >> 31)))

int(*GetValue)();

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
    std::cout << *((unsigned short *)&A.x + 1) << "\n";
    //Low Word
    std::cout << *((unsigned short *)&A.x) << "\n";

    //Flip sign bit of float
    float F = 10;
    *(int *)&F = *((int *)&F) ^ 0x80000000;
    std::cout << F << "\n";

    //Convert pointer type of different structs
    StructB B;
    B.a = 10;
    B.b = 5;
    std::strcpy(B.c, "Bom dia");

    std::cout << Sum((StructA *)&B) << "\n";

    //Create macros for 
    std::cout << absi(-60) << "\n";
    std::cout << absi(40) << "\n";

    //Changing function behavior in runtime with function pointers
    GetValue = GetValue1;
    std::cout << GetValue() << "\n";

    GetValue = GetValue2;
    std::cout << GetValue() << "\n";

    //Generating random float (0 <= Random < 1) from random integer generator
    float Random;
    *(int *)&Random = (RNG() & 0x007fffff);
    std::cout << Random << "\n";
}