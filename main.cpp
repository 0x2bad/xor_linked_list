#include <cstdio>

#include "xorLL.h"

int main()
{
    class List list;

    list.insert(30);
    list.insert(35);
    list.insert(40);
    list.insert(45);
    list.insert(50);

    while (list.deleteNode())
        ;

    list.insert(30);
    list.insert(35);
    list.insert(40);
    list.insert(45);
    list.insert(50);

    printf("printing list 3 times...\n");
    for (int i = 0; i < 15; i++) {
        printf("%llu\n", list.getData());
        list.moveRight();
    }
}
