#include <iostream>

#define PI 3.14159265358979311599796346854
#define HALF_PI 1.57079632679489700208819158433
#define QUARTER_PI 0.78539816339744850104409579217

#define PI2 0x401921FB54442D18
#define PI2N 0xC01921FB54442D18
#define PI_INT 0x400921FB54442D18
#define HALF_PI_INT 0x3FF921FB54442D1A
#define QUARTER_PI_INT 0x3FE921FB54442D1A

int main()
{
    double pipi = PI + PI;
    double pi = PI;
    double half_pi = HALF_PI;
    double quarter_pi = QUARTER_PI;
    
    std::cout << *(long long *)&pipi << "\n";
    std::cout << *(long long *)&pi << "\n";
    std::cout << *(long long *)&half_pi << "\n";
    std::cout << *(long long *)&quarter_pi << "\n";
}