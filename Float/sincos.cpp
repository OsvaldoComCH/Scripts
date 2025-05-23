#define PI 3.14159265358979311599796346854
#define HALF_PI 1.57079632679489700208819158433
#define QUARTER_PI 0.78539816339744850104409579217
#include <iostream>
#include <cstdio>

struct __declspec(dllexport) sincos_result
{
    double sin;
    double cos;
};

static inline double abs(double n)
{
    *(long long *)&n = *((long long *)&n) & 0x7FFFFFFFFFFFFFFF;
    return n;
}

static inline double flip_sign(double n)
{
    *(long long *)&n = *((long long *)&n) ^ 0x8000000000000000;
    return n;
}

static inline double negative(double n)
{
    *(long long *)&n = *((long long *)&n) | 0x8000000000000000;
    return n;
}

static inline double modulus(double x, double y)
{
    int factor = x / y;
    return x - y * factor;
}

void __declspec(dllexport) __cdecl sincos(double radians, sincos_result * result)
{
    double num = modulus(radians, PI + PI);
    double n = abs(num);

    bool sine = 0;
    double bias;

    if(n < QUARTER_PI)
    {
        bias = 0;
    }else
    if(n < QUARTER_PI + HALF_PI)
    {
        sine = 1;
        bias = HALF_PI;
    }else
    if(n < PI + QUARTER_PI)
    {
        bias = PI;
    }else
    if(n < PI + HALF_PI + QUARTER_PI)
    {
        sine = 1;
        bias = PI + HALF_PI;
    }else
    {
        bias = PI + PI;
    }

    double base = n - bias;

    double n2d2 = base * (base / 2);
    double e = 1 - (n2d2 - (n2d2 * n2d2 / 6));
    
    double a = 1 - e * e;
    double m;
    asm volatile("sqrtsd  %1, %0"
        : "=x"(m)
        : "x"(a)
    );

    if(sine)
    {
        result->sin = e;
        result->cos = m;
    }else
    {
        result->sin = m;
        result->cos = e;
    }

    if(n < HALF_PI)
    {
        result->sin = abs(result->sin);
        result->cos = abs(result->cos);
    }else
    if(n < PI)
    {
        result->sin = abs(result->sin);
        result->cos = negative(result->cos);
    }else
    if(n < PI + HALF_PI)
    {
        result->sin = negative(result->sin);
        result->cos = negative(result->cos);
    }else
    {
        result->sin = negative(result->sin);
        result->cos = abs(result->cos);
    }

    if(num < 0)
    {
        result->sin = flip_sign(result->sin);
    }
}

#undef PI
#undef HALF_PI
#undef QUARTER_PI