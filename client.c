#include<stdio.h> 
#include"header.h"

int main() 
    {
        multi_t t;
        init(&t);
        readFile(&t);
        initialize_down(&t);
        pathFinder(&t);
        return 0;
    }