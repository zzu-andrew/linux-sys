// strngbad.h -- flawed string class definition
#include <iostream>
#ifndef STRNGBAD_H_
#define STRNGBAD_H_
class StringBad
{
private:
    char * str;                // pointer to string
    int len;                   // length of string
    static int num_strings;    // number of objects
public:
    StringBad(const char * s); // constructor
    StringBad();               // default constructor
    ~StringBad();              // destructor
// friend function
//< 使用友元函数，因为cout 属于 std os类中的成员
    friend std::ostream & operator<<(std::ostream & os, 
                       const StringBad & st);
};
#endif
