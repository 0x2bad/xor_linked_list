#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include "XORLL.h"

List::List()
{
    this->hanger = (Node*)calloc(sizeof(struct List), 1);
    this->current = this->hanger;
    this->previous = this->current;
}

List::~List()
{
    while(deleteNode())
    { /* keep deleting until empty */ }
}

#define SWAP(a, b) a ^= b, b ^= a, a ^= b

void moveLeft(struct List *list)
{
    SWAP(list->previous_int, list->current_int);
    list->previous_int ^= list->current->PxorN;
}

void moveRight(struct List *list)
{
    list->previous_int ^= list->current->PxorN;
    SWAP(list->previous_int, list->current_int);
}

void reverse(struct List *list)
{
    list->previous_int ^= list->current->PxorN;
}

void insert(struct List *list, uint64_t data)
{
    list->hanger->data = data;

    list->hanger->PxorN = list->previous_int ^ list->current_int;
    list->current->PxorN ^= list->previous_int ^ list->hanger_int;
    SWAP(list->previous_int, list->hanger_int);
    list->hanger->PxorN ^= list->current_int ^ list->previous_int;

    list->hanger = (Node*)calloc(sizeof(struct Node), 1);
}

bool List::deleteNode()
{
    if (this->hanger == this->current)
        return 0; // empty

    free(this->hanger);
    this->hanger = this->current;
    this->current_int = this->current->PxorN ^ this->previous_int;
    this->current->PxorN ^= this->hanger_int ^ this->previous_int;
    this->previous->PxorN ^= this->hanger_int ^ this->current_int;

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

    while (list.delete_node())
        ;

    insert(&list, 30);
    insert(&list, 35);
    insert(&list, 40);
    insert(&list, 45);
    insert(&list, 50);

    printf("printing list 3 times...\n");
    for (int i = 0; i < 15; i++) {
        printf("%lu\n", list.current->data);
        moveRight(&list);
    }
}
