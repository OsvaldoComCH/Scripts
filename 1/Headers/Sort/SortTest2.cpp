#include <cstdio>
#include <random>
#include <chrono>
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "QuickerSort.hpp"


inline unsigned long long rdtsc()
{
    unsigned int lo,hi;
    asm volatile("rdtsc" : "=a" (lo), "=d" (hi));
    return ((unsigned long long)hi << 32) | lo;
}

std::mt19937 RNG(rdtsc());

void BigArray(int * A, int Size)
{
    for(int i = 0; i < Size; ++i)
    {
        A[i] = RNG();
    }
}

int main()
{
    int Size = 1000000;
    int * A = new int[Size];

    unsigned long long Start, End;
    unsigned long long QuickerTotal = 0, QuickTotal = 0, MergeTotal = 0,
    InsertionTotal = 0, SelectionTotal = 0, BubbleTotal = 0;
    for(int i = 0; i < 3; ++i)
    {
        BigArray(A, Size);

        switch(i % 3)
        {
            case 0:
                Start = rdtsc();
                QuickSort(A, 0, Size - 1);
                End = rdtsc();
                QuickTotal += End - Start;
            break;
            case 1:
                Start = rdtsc();
                QuickerSort(A, Size);
                End = rdtsc();
                QuickerTotal += End - Start;
            break;
            case 2:
                Start = rdtsc();
                MergeSort(A, 0, Size - 1);
                End = rdtsc();
                MergeTotal += End - Start;
            break;
        }
    }
    printf("MergeSort:\nTotal: %llu cycles\nAvg: %llu cycles\n\n", MergeTotal, MergeTotal / 1);
    printf("QuickSort:\nTotal: %llu cycles\nAvg: %llu cycles\n\n", QuickTotal, QuickTotal / 1);
    printf("QuickerSort:\nTotal: %llu cycles\nAvg: %llu cycles\n\n", QuickerTotal, QuickerTotal / 1);
}