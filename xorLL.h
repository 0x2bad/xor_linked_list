#pragma once

#include <cstdint>

struct Node {
    uintptr_t PxorN; // Previous XOR Next
    uint64_t data;
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
    bool deleteNode();
    uint64_t getData() const;
private:
    uint64_t *cursorCount;
    // Allocating 'hanger' ahead of time allows us to use
    // 'List::insert()' without having to check if list is empty.
    union { Node *hanger;   uintptr_t hangerX;   };
    union { Node *current;  uintptr_t currentX;  };
    union { Node *previous; uintptr_t previousX; };
};
