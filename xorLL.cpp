#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include "xorLL.h"

List::List()
{
    this->hanger.ptr = (Node*)calloc(sizeof(struct List), 1);
    this->current.ptr = this->hanger.ptr;
    this->previous.ptr = this->current.ptr;
}

List::~List()
{
    while(deleteNode())
    { /* keep deleting until empty */ }
}

#define SWAP(a, b) a ^= b, b ^= a, a ^= b

void List::moveLeft()
{
    SWAP(this->previous.uintptr, this->current.uintptr);
    this->previous.uintptr ^= this->current.ptr->PxorN;
}

void List::moveRight()
{
    this->previous.uintptr ^= this->current.ptr->PxorN;
    SWAP(this->previous.uintptr, this->current.uintptr);
}

void List::reverse()
{
    this->previous.uintptr ^= this->current.ptr->PxorN;
}

void List::insert(uint64_t data)
{
    this->hanger.ptr->data = data;

    this->hanger.ptr->PxorN = this->previous.uintptr ^ this->current.uintptr;
    this->current.ptr->PxorN ^= this->previous.uintptr ^ this->hanger.uintptr;
    SWAP(this->previous.uintptr, this->hanger.uintptr);
    this->hanger.ptr->PxorN ^= this->current.uintptr ^ this->previous.uintptr;

    this->hanger.ptr = (Node*)calloc(sizeof(struct Node), 1);
}

bool List::deleteNode()
{
    if (this->hanger.ptr == this->current.ptr)
        return 0; // empty

    free(this->hanger.ptr);
    this->hanger.ptr = this->current.ptr;
    this->current.uintptr = this->current.ptr->PxorN ^ this->previous.uintptr;
    this->current.ptr->PxorN ^= this->hanger.uintptr ^ this->previous.uintptr;
    this->previous.ptr->PxorN ^= this->hanger.uintptr ^ this->current.uintptr;

    return 1;
}

uint64_t List::getData() const
{
    return this->current.ptr->data;
}

