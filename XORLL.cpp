#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include "XORLL.h"

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

int main()
{
    class List list;

    list.insert(30);
    list.insert(35);
    list.insert(40);
    list.insert(45);
    list.insert(50);

    while (list.deleteNode())
        ;

    list.insert(30);
    list.insert(35);
    list.insert(40);
    list.insert(45);
    list.insert(50);

    printf("printing list 3 times...\n");
    for (int i = 0; i < 15; i++) {
        printf("%lu\n", list.current.ptr->data);
        list.moveRight();
    }
}
