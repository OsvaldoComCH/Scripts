#pragma once
#ifndef INSERTION_SORT
#define INSERTION_SORT

void InsertionSort(int * A, int Size)
{
    for(int i = 1, j = 0; i < Size; j = i, ++i)
    {
        int x = A[i];
        while(j >= 0 && A[j] > x)
        {
            A[j+1] = A[j];
            --j;
        }
        A[j+1] = x;
    }
}
#endif