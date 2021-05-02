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

class List {
public:
    List();
    ~List();
    void moveLeft();
    void moveRight();
    void reverse();
    void insert(uint64_t data);
    bool isEmpty();
    bool deleteNode();
    uint64_t getData() const;
private:
    union _Node current;
    union _Node previous;
    // Allocating 'hanger' ahead of time allows us to use
    // 'List::insert()' without having to check if list is empty.
    union _Node hanger;
};
