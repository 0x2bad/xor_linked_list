#pragma once

#include <cstdlib>
#include <cstdint>

#define SWAP(a, b) a ^= b, b ^= a, a ^= b

template <typename T>
struct Node {
    uintptr_t PxorN; // Previous XOR Next
    T data;
};

template <typename T>
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
    void insert(T data);
    bool isEmpty();
    bool deleteNode();
    T getData() const;
private:
    union { uint64_t *cursorCount; uintptr_t cursorCountX; };
    // Allocating 'hanger' ahead of time allows us to use
    // 'List::insert()' without having to check if list is empty.
    union { Node <T>*hanger;   uintptr_t hangerX;   };
    union { Node <T>*current;  uintptr_t currentX;  };
    union { Node <T>*previous; uintptr_t previousX; };
    void swap(struct List& first, struct List& second)
    {
        SWAP(first.cursorCountX, second.cursorCountX);
        SWAP(first.hangerX, second.hangerX);
        SWAP(first.currentX, second.currentX);
        SWAP(first.previousX, second.previousX);
    }
};

template <typename T>
List<T>::List()
{
    cursorCount = (T*) malloc(sizeof(T));
    *cursorCount = 1;
    hanger = (Node <T>*) calloc(sizeof(struct List), 1);
    current = hanger;
    previous = current;
}

template <typename T>
List<T>::List(const List& c)
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
template <typename T>
List<T>& List<T>::operator=(List c)
{ 
    swap(*this, c);
    return *this;
}

template <typename T>
List<T>::List(List<T>&& c) noexcept
{
    List();
    swap(*this, c);
}

template <typename T>
List<T>::~List()
{
    if (--(*cursorCount) == 0) {
        while(deleteNode())
        { /* keep deleting until empty */ }
        free(cursorCount);
        free(hanger);
    }
}

template <typename T>
inline void List<T>::reverse()
{
    previousX ^= current->PxorN;
}


template <typename T>
inline void List<T>::moveLeft()
{
    SWAP(previousX, currentX);
    reverse();
}

template <typename T>
inline void List<T>::moveRight()
{
    reverse();
    SWAP(previousX, currentX);
}

template <typename T>
inline void List<T>::insert(T data)
{
    hanger->data = data;

    hanger->PxorN = previousX ^ currentX;
    current->PxorN ^= previousX ^ hangerX;
    SWAP(previousX, hangerX);
    hanger->PxorN ^= currentX ^ previousX;

    hanger = (Node<T>*) malloc(sizeof(struct Node<T>));
}

template <typename T>
inline bool List<T>::isEmpty()
{
    return (hanger == current);
}

template <typename T>
inline bool List<T>::deleteNode()
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

template <typename T>
inline T List<T>::getData() const
{
    return current->data;
}

#undef SWAP
