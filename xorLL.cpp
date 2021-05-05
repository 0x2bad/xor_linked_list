#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include "xorLL.h"

List::List()
{
    cursorCount = (uint64_t*) malloc(sizeof(uint64_t));
    *cursorCount = 1;
    hanger.ptr = (Node*) calloc(sizeof(struct List), 1);
    current.ptr = hanger.ptr;
    previous.ptr = current.ptr;
}

List::List(const List &c)
{
    cursorCount = c.cursorCount;
    (*cursorCount)++;

    hanger.ptr = c.hanger.ptr;
    current.ptr = c.current.ptr;
    previous.ptr = c.previous.ptr;
}

List::~List()
{
    if (--(*cursorCount) == 0)
        while(deleteNode())
        { /* keep deleting until empty */ }
}

void List::reverse()
{
    previous.uintptr ^= current.ptr->PxorN;
}

#define SWAP(a, b) a ^= b, b ^= a, a ^= b

void List::moveLeft()
{
    SWAP(previous.uintptr, current.uintptr);
    reverse();
}

void List::moveRight()
{
    reverse();
    SWAP(previous.uintptr, current.uintptr);
}

void List::insert(uint64_t data)
{
    hanger.ptr->data = data;

    hanger.ptr->PxorN = previous.uintptr ^ current.uintptr;
    current.ptr->PxorN ^= previous.uintptr ^ hanger.uintptr;
    SWAP(previous.uintptr, hanger.uintptr);
    hanger.ptr->PxorN ^= current.uintptr ^ previous.uintptr;

    hanger.ptr = (Node*) malloc(sizeof(struct Node));
}

bool List::isEmpty()
{
    return (hanger.ptr == current.ptr);
}

uint8_t List::deleteNode()
{
    if (isEmpty())
        return 0;

    free(hanger.ptr);
    hanger.ptr = current.ptr;
    current.uintptr = current.ptr->PxorN ^ previous.uintptr;
    current.ptr->PxorN ^= hanger.uintptr ^ previous.uintptr;
    previous.ptr->PxorN ^= hanger.uintptr ^ current.uintptr;

    return 1;
}

uint64_t List::getData() const
{
    return current.ptr->data;
}

