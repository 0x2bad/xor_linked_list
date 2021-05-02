#pragma once

#include <cstdint>

struct Node {
    uintptr_t PxorN; // Previous XOR Next
    uint64_t data;
};

union _Node {
    uintptr_t uintptr;
    struct Node *ptr;
};

struct List {
    List();
    ~List();
    bool deleteNode();
    union _Node current;
    union _Node previous;
    // Allocating 'hanger' ahead of time allows us to
    // use 'insert' without having to check if list is empty.
    union _Node hanger;
};
