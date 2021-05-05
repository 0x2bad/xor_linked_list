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
    List(const List &);
    ~List();
    void reverse();
    void moveLeft();
    void moveRight();
    void insert(uint64_t data);
    bool isEmpty();
    uint8_t deleteNode();
    uint64_t getData() const;
private:
    uint64_t *cursorCount;
    union _Node current;
    union _Node previous;
    // Allocating 'hanger' ahead of time allows us to use
    // 'List::insert()' without having to check if list is empty.
    union _Node hanger;
};
