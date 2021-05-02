#pragma once

#include <cstdint>

struct Node {
    uintptr_t PxorN; // Previous XOR Next
    uint64_t data;
};

struct List {
    List();
    ~List();
    bool delete_node();
    union {
        struct Node *current;
        uintptr_t current_int;
    };
    union {
        uintptr_t previous_int;
        struct Node *previous;
    };
    union {
        // Allocating 'hanger' ahead of time allows us to
        // use 'insert' without having to check if list is empty.
        struct Node *hanger;
        uintptr_t hanger_int;
    };
};
