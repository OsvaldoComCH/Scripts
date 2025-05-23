#include <cstdio>

struct __declspec(dllimport) sincos_result
{
    double sin;
    double cos;
};

void __declspec(dllimport) __cdecl sincos(double, sincos_result *);

int main()
{
    sincos_result sc;
    sincos(69, &sc);
    printf("sin: %.10f\ncos: %.10f", sc.sin, sc.cos);
}