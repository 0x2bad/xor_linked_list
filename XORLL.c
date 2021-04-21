#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct Node {
    union {
        // I wish I could think of a better name for this
        uintptr_t PxorN_int;
        struct Node *previousXORnext;
    };
    uint64_t data;
};

struct List {
    union {
        // Another bad name
        uintptr_t current_int;
        struct Node *current;
    };
    uintptr_t currentXORnext;
};

bool move(struct List *list)
{
    // make sure we're not facing end of list
    if (list->currentXORnext == list->current_int)
        return 0;

    list->current_int ^= list->currentXORnext;
    list->currentXORnext ^= list->current->PxorN_int;

    return 1;
}

void reverseMoveDirection(struct List *list)
{
    list->currentXORnext ^= list->current->PxorN_int;
}

int main()
{
    struct List list = { 0 };
    {// manually craft XOR list
        struct Node *a = calloc(sizeof(struct Node), 1);
        a->data = 50;

        struct Node *b = calloc(sizeof(struct Node), 1);
        b->data = 55;

        struct Node *c = calloc(sizeof(struct Node), 1);
        c->data = 60;

        struct Node *d = calloc(sizeof(struct Node), 1);
        d->data = 65;

        struct Node *e = calloc(sizeof(struct Node), 1);
        e->data = 70;

        a->previousXORnext = b;
        b->PxorN_int = (uintptr_t)a ^ (uintptr_t)c;
        c->PxorN_int = (uintptr_t)b ^ (uintptr_t)d;
        d->PxorN_int = (uintptr_t)c ^ (uintptr_t)e;
        e->previousXORnext = d;

        list.current = a;
        list.currentXORnext = list.current_int ^ (uintptr_t)b;
    }

    printf("printing list...\n");
    for (int i = 0; i < 5; i++) {
        printf("%lu\n", list.current->data);
        move(&list);
    }

    printf("\nreversing direction...\n");
    reverseMoveDirection(&list);

    for (int i = 0; i < 5; i++) {
        printf("%lu\n", list.current->data);
        move(&list);
    }
}
