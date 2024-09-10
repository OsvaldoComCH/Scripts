#ifndef LINKED_LIST
#define LINKED_LIST
#include <stdlib.h>

typedef struct LLNode
{
    void * Value;
    struct LLNode * Next;
    struct LLNode * Prev;
} LLNode;

typedef struct LList
{
    LLNode * Head;
    LLNode * Tail;
    int Size;
} LList;

void LListCreate(LList * List)
{
    List->Head = NULL;
    List->Tail = NULL;
    List->Size = 0;
}

void LListAdd(LList * List, void * Value)
{
    LLNode * N = (LLNode *) malloc(sizeof(LLNode));
    N->Value = Value;
    if(List->Size)
    {
        List->Tail->Next = N;
        N->Prev = List->Tail;
        N->Next = NULL;
        List->Tail = N;
    }else
    {
        N->Next = NULL;
        N->Prev = NULL;
        N->Value = Value;
        List->Head = N;
        List->Tail = N;
    }
    ++List->Size;
}

void * LListGet(LList * List, int index)
{
    if((unsigned) index >= List->Size)
    {
        return 0;
    }
    if(index < (List->Size << 1))
    {
        LLNode * N = List->Head;
        while(index--)
        {
            N = N->Next;
        }
        return N->Value;
    }else
    {
        LLNode * N = List->Tail;
        while(++index < List->Size)
        {
            N = N->Prev;
        }
        return N->Value;
    }
}

void LListSet(LList * List, int index, void * Value)
{
    if ((unsigned) index >= List->Size)
    {
        return;
    }

    if(index < (List->Size << 1))
    {
        LLNode * N = List->Head;
        while(index--)
        {
            N = N->Next;
        }
        N->Value = Value;
    }else
    {
        LLNode * N = List->Tail;
        while(++index < List->Size)
        {
            N = N->Prev;
        }
        N->Value = Value;
    }
}

void LListRemove(LList * List, int index)
{
    if((unsigned) index >= List->Size)
    {
        return;
    }
    
    if(index < (List->Size << 1))
    {
        LLNode * N = List->Head;
        while(index--)
        {
            N = N->Next;
        }
        if(N->Prev)
        {
            N->Prev->Next = N->Next;
        }
        if(N->Next)
        {
            N->Next->Prev = N->Prev;
        }
        free(N);
    }else
    {
        LLNode * N = List->Tail;
        while(++index < List->Size)
        {
            N = N->Prev;
        }
        if(N->Prev)
        {
            N->Prev->Next = N->Next;
        }
        if(N->Next)
        {
            N->Next->Prev = N->Prev;
        }
        free(N);
    }
}

void LListDestroy(LList * List)
{
    for(int i = 0; i < List->Size; ++i)
    {
        LListRemove(List, 0);
    }
}

#endif