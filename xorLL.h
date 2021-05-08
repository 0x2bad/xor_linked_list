#pragma once

#include <cstdlib>
#include <cstdint>

#define SWAP(a, b) a ^= b, b ^= a, a ^= b

struct Node {
    uintptr_t PxorN; // Previous XOR Next
    uint64_t data;
};

class List {
public:
    List();
    // copy constructor
    List(const List &);
    List& operator=(List c);
    // move-constructor
    List(List&& c) noexcept;
    ~List();
    void reverse();
    void moveLeft();
    void moveRight();
    void insert(uint64_t data);
    bool isEmpty();
    bool deleteNode();
    uint64_t getData() const;
private:
    union { uint64_t *cursorCount; uintptr_t cursorCountX; };
    // Allocating 'hanger' ahead of time allows us to use
    // 'List::insert()' without having to check if list is empty.
    union { Node *hanger;   uintptr_t hangerX;   };
    union { Node *current;  uintptr_t currentX;  };
    union { Node *previous; uintptr_t previousX; };
    void swap(struct List& first, struct List& second)
    {
        SWAP(first.cursorCountX, second.cursorCountX);
        SWAP(first.hangerX, second.hangerX);
        SWAP(first.currentX, second.currentX);
        SWAP(first.previousX, second.previousX);
    }
};

List::List()
{
    cursorCount = (uint64_t*) malloc(sizeof(uint64_t));
    *cursorCount = 1;
    hanger = (Node*) calloc(sizeof(struct List), 1);
    current = hanger;
    previous = current;
}

List::List(const List& c)
{
    cursorCount = c.cursorCount;
    (*cursorCount)++;

    hanger = c.hanger;
    current = c.current;
    previous = c.previous;
}

// TODO: Figure out how this works
// https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
// TODO: Run tests on overloaded assignment and move-constructor
List& List::operator=(List c)
{ 
    swap(*this, c);
    return *this;
}

List::List(List&& c) noexcept
{
    List();
    swap(*this, c);
}

List::~List()
{
    if (--(*cursorCount) == 0) {
        while(deleteNode())
        { /* keep deleting until empty */ }
        free(cursorCount);
        free(hanger);
    }
}

inline void List::reverse()
{
    previousX ^= current->PxorN;
}


inline void List::moveLeft()
{
    SWAP(previousX, currentX);
    reverse();
}

inline void List::moveRight()
{
    reverse();
    SWAP(previousX, currentX);
}

inline void List::insert(uint64_t data)
{
    hanger->data = data;

    hanger->PxorN = previousX ^ currentX;
    current->PxorN ^= previousX ^ hangerX;
    SWAP(previousX, hangerX);
    hanger->PxorN ^= currentX ^ previousX;

    hanger = (Node*) malloc(sizeof(struct Node));
}

inline bool List::isEmpty()
{
    return (hanger == current);
}

inline bool List::deleteNode()
{
    if (isEmpty())
        return 0;

    free(hanger);
    hanger = current;
    currentX = current->PxorN ^ previousX;
    current->PxorN ^= hangerX ^ previousX;
    previous->PxorN ^= hangerX ^ currentX;

    return 1;
}

inline uint64_t List::getData() const
{
    return current->data;
}

#undef SWAP
