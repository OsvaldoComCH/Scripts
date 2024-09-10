#ifndef BUBBLE_SORT
#define BUBBLE_SORT

void BubbleSort(int * A, int Size)
{
    --Size;
    for(int i = 0; i < Size; ++i)
    {
        for(int j = 0; j < Size-i; ++j)
        {
            if(A[j] > A[j+1])
            {
                A[j+1] = A[j] ^ A[j+1];
                A[j] = A[j] ^ A[j+1];
                A[j+1] = A[j] ^ A[j+1];
            }
        }
    }
}

#endif