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

void moveLeft(struct List *list)
{
    SWAP(list->previous.uintptr, list->current.uintptr);
    list->previous.uintptr ^= list->current.ptr->PxorN;
}

void moveRight(struct List *list)
{
    list->previous.uintptr ^= list->current.ptr->PxorN;
    SWAP(list->previous.uintptr, list->current.uintptr);
}

void reverse(struct List *list)
{
    list->previous.uintptr ^= list->current.ptr->PxorN;
}

void insert(struct List *list, uint64_t data)
{
    list->hanger.ptr->data = data;

    list->hanger.ptr->PxorN = list->previous.uintptr ^ list->current.uintptr;
    list->current.ptr->PxorN ^= list->previous.uintptr ^ list->hanger.uintptr;
    SWAP(list->previous.uintptr, list->hanger.uintptr);
    list->hanger.ptr->PxorN ^= list->current.uintptr ^ list->previous.uintptr;

    list->hanger.ptr = (Node*)calloc(sizeof(struct Node), 1);
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
    struct List list;

    insert(&list, 30);
    insert(&list, 35);
    insert(&list, 40);
    insert(&list, 45);
    insert(&list, 50);

    while (list.deleteNode())
        ;

    insert(&list, 30);
    insert(&list, 35);
    insert(&list, 40);
    insert(&list, 45);
    insert(&list, 50);

    printf("printing list 3 times...\n");
    for (int i = 0; i < 15; i++) {
        printf("%lu\n", list.current.ptr->data);
        moveRight(&list);
    }
}

