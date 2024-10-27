//We program mostly in english, but sometimes in C++
#include <iostream>

static inline unsigned short HiWord(unsigned int Long)
{
    return *((unsigned short *) &Long + 1);
}

static inline unsigned short LoWord(unsigned int Long)
{
    return *((unsigned short *) &Long);
}

int main()
{
    std::cout << HiWord(0x8000ffff) << "\n" << LoWord(0x8000ffff);
}