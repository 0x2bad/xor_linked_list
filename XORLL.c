#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct Node {
    uintptr_t PxorN; // Previous XOR Next
    uint64_t data;
};

struct List {
    union {
        struct Node *current;
        uintptr_t current_int;
    };
    uintptr_t bucket; // Current XOR previous
    union {
        // Allocating 'hanger' ahead of time allows use to
        // use 'insert' without having to check if list is empty.
        struct Node *hanger;
        uintptr_t hanger_int;
    };
};

void moveLeft(struct List *list)
{
    list->current_int ^= list->bucket;
    list->bucket ^= list->current->PxorN;
}

void moveRight(struct List *list)
{
    list->bucket ^= list->current->PxorN;
    list->current_int ^= list->bucket;
}

void reverse(struct List *list)
{// TODO: Make it to where the two 'moveRight' functions are unnecessary
    moveRight(list);
    moveRight(list);
    list->bucket ^= list->current->PxorN;
}

void insert(struct List *list, uint64_t data)
{
    list->hanger->data = data;

    list->hanger->PxorN = list->bucket;
    list->bucket ^= list->current_int ^ list->hanger_int ^ list->hanger->PxorN;
    list->current->PxorN ^= list->current_int ^ list->hanger_int ^ list->hanger->PxorN;
    list->hanger_int = list->hanger->PxorN ^ list->current_int;
    list->hanger->PxorN ^= list->bucket;

    list->hanger = calloc(sizeof(struct Node), 1);
}

int main()
{
    struct List list;
    // Allocate ahead of time
    list.hanger = calloc(sizeof(struct List), 1);
    list.current = list.hanger;

    insert(&list, 30);
    insert(&list, 35);
    insert(&list, 40);
    insert(&list, 45);
    insert(&list, 50);

    printf("printing list...\n");
    printf("%lu\n", list.current->data);
    for (int i = 0; i < 14; i++) {
        moveRight(&list);
        printf("%lu\n", list.current->data);
    }

    printf("\nreversing direction...\n");
    reverse(&list);

    moveRight(&list);
    for (int i = 0; i < 14; i++) {
        moveRight(&list);
        printf("%lu\n", list.current->data);
    }
}
