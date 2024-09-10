#ifndef SELECTION_SORT
#define SELECTION_SORT

void SelectionSort(int * A, int Size)
{
    for(int i = 0, j = 0; i < Size; ++i, j = i)
    {
        int x = i;
        while(j < Size)
        {
            ++j;
            if(A[j] < A[x])
            {
                x = j;
            }
        }
        int Temp = A[x];
        A[x] = A[i];
        A[i] = Temp;
    }
}
#endif