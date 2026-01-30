#include <cstdio>
#include <cmath>
#define PI 3.14159265358979311599796346854

struct __declspec(dllimport) sincos_result
{
    double sin;
    double cos;
};

void __declspec(dllimport) __cdecl sincos(double, sincos_result *);

int main()
{
    sincos_result sc;
    sincos(63, &sc);
    double sine = sin(63);
    double cosine = cos(63);
    printf("sin: %.10f\tcos: %.10f\n", sc.sin, sc.cos);
    printf("sin: %.10f\tcos: %.10f\n", sine, cosine);
}