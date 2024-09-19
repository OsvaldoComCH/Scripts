/*
MIT License

Copyright (c) 2024 Eduardo Henrique Ribeiro da Silva

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef QUICKERSORT_H
#define QUICKERSORT_H

void QuickerSort(int * A, int Start, int End)
{
    int Pivot;
    int x = Start;
    int y = Start + 1;
    
    if(End - Start <= 65)
    {
        for(; y < End; x = y, ++y)
        {
            Pivot = A[y];
            while(x >= 0 && A[x] > Pivot)
            {
                A[x+1] = A[x];
                --x;
            }
            A[x+1] = Pivot;
        }
        return;
    }
    
    Pivot = A[x];
    for(; y <= End; ++y)
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
    QuickerSort(A, Start, x - 1);
    QuickerSort(A, x + 1, End);
}

#endif
