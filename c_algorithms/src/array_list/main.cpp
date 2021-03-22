//
// Created by andrew on 2021/2/23.
//
#include <iostream>
#include <cassert>
#include "array_list.h"


using namespace std;

/* array list test */

int variable1 = 1, variable2 = 2, variable3 = 3, variable4 = 4;

ArrayList *generate_arraylist()
{
    ArrayList *arraylist;
    int i;

    arraylist = arraylist_new(0);

    for (i=0; i<4; ++i) {
        arraylist_append(arraylist, &variable1);
        arraylist_append(arraylist, &variable2);
        arraylist_append(arraylist, &variable3);
        arraylist_append(arraylist, &variable4);
    }

    return arraylist;
}



void test_arraylist_new_free()
{
    ArrayList *arraylist;

    /* Use a default size when given zero */

    arraylist = arraylist_new(0);
    assert(arraylist != nullptr);
    arraylist_free(arraylist);

    /* Normal allocated */

    arraylist = arraylist_new(10);
    assert(arraylist != nullptr);
    arraylist_free(arraylist);

    /* Freeing a null arraylist works */

    arraylist_free(nullptr);
}


int main(int argc, char *argv[]) {

    test_arraylist_new_free();



    return 0;
}

