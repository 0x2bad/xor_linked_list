#include <cstdio>

#include "xorLL.h"

int main()
{
    // constructor 
    class List<uint64_t> cursor1;

    cursor1.insert(30);
    cursor1.insert(35);
    cursor1.insert(40);
    cursor1.insert(45);
    cursor1.insert(50);

    while (cursor1.deleteNode())
        ;

    cursor1.insert(30);
    cursor1.insert(35);
    cursor1.insert(40);
    cursor1.insert(45);
    cursor1.insert(50);

    printf("printing list 3 times...\n");
    for (int i = 0; i < 15; i++) {
        printf("%llu\n", cursor1.getData());
        cursor1.moveRight();
    }
    // copy constructor
    class List<uint64_t> cursor2 = cursor1;

    printf("printing list 3 times from new cursor\n");
    for (int i = 0; i < 15; i++) {
        printf("%llu\n", cursor2.getData());
        cursor2.moveLeft();
    }

    cursor2.moveLeft();

    // assignment overload
    cursor2 = cursor1;
}
