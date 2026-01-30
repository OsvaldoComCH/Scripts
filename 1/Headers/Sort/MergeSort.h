#pragma once
#ifndef MERGE_SORT
#define MERGE_SORT
#include <stdlib.h>

void MergeSort(int * A, int Start, int End)
{
    if(Start >= End)
    {
        return;
    }

    int Mid = Start+((End-Start) >> 1);
    MergeSort(A, Start, Mid);
    MergeSort(A, Mid + 1, End);

    int * B = (int *) malloc((End-Start+1)*sizeof(int));
    int x = Start, y = Mid+1, z = 0;

    while(x <= Mid && y <= End)
    {
        if(A[x] < A[y])
        {
            B[z++] = A[x++];
        }else
        {
            B[z++] = A[y++];
        }
    }
    while(x <= Mid)
    {
        B[z++] = A[x++];
    }
    while(y <= End)
    {
        B[z++] = A[y++];
    }

    for(int i = Start, j = 0; i <= End; ++i, ++j)
    {
        A[i] = B[j];
    }
    free(B);
}
#endif