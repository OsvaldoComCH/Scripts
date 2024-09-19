#pragma once
#ifndef QUICK_SORT
#define QUICK_SORT

void QuickSort(int * A, int Start, int End)
{
    
    if(Start >= End){return;}
    
    int Pivot = A[Start];
    int x = Start;

    for(int y = Start + 1; y <= End; ++y)
    {
        if(A[y]<Pivot)
        {
            ++x;
            int Temp = A[x];
            A[x] = A[y];
            A[y] = Temp;
        }
    }
    A[Start] = A[x];
    A[x] = Pivot;
    QuickSort(A, Start, x - 1);
    QuickSort(A, x + 1, End);
}

#endif