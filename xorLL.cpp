#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include "xorLL.h"

List::List()
{
    cursorCount = (uint64_t*) malloc(sizeof(uint64_t));
    *cursorCount = 1;
    hanger = (Node*) calloc(sizeof(struct List), 1);
    current = hanger;
    previous = current;
}

List::List(const List &c)
{
    cursorCount = c.cursorCount;
    (*cursorCount)++;

    hanger = c.hanger;
    current = c.current;
    previous = c.previous;
}

List::~List()
{
    if (--(*cursorCount) == 0)
        while(deleteNode())
        { /* keep deleting until empty */ }
}

void List::reverse()
{
    previousX ^= current->PxorN;
}

#define SWAP(a, b) a ^= b, b ^= a, a ^= b

void List::moveLeft()
{
    SWAP(previousX, currentX);
    reverse();
}

void List::moveRight()
{
    reverse();
    SWAP(previousX, currentX);
}

void List::insert(uint64_t data)
{
    hanger->data = data;

    hanger->PxorN = previousX ^ currentX;
    current->PxorN ^= previousX ^ hangerX;
    SWAP(previousX, hangerX);
    hanger->PxorN ^= currentX ^ previousX;

    hanger = (Node*) malloc(sizeof(struct Node));
}

bool List::isEmpty()
{
    return (hanger == current);
}

bool List::deleteNode()
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

uint64_t List::getData() const
{
    return current->data;
}

