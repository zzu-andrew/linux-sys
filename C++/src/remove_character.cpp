//
// Created by andrew on 2021/3/8.
//
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <map>

using namespace std;

void RemoveCharacter(char *testStr, char c) {
    char *head;
    char *tail;
    head = testStr;
    tail = testStr;
    int len = strlen(testStr);
    for (int i = 0; i < len; i++) {
        if (*tail == c) {
            tail++;
        } else {
            *head = *tail;
            head ++;
            tail ++;
        }
        cout << testStr[i] << endl;
    }

    if (tail - head > 0) {
        *head = '\0';
    }

}


int main(int argc, char ** argv)
{

    char testStr[128] = "testStrdsfdsf";


    RemoveCharacter(testStr, 's');

    cout << string(testStr) << endl;

    return 0;
}
