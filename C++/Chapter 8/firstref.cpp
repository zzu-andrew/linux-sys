// firstref.cpp -- defining and using a reference


#include <iostream>



void rats_add(int & tmp)
{
    tmp ++;
}




int main()
{
    using namespace std;
    int rats = 101;
    int & rodents = rats;   // rodents is a reference
    //< 引用传入的函数值，也是传入函数参数的本身，而不是函数参数的副本
    rats_add(rats);
    cout << "rats = " << rats;
    cout << ", rodents = " << rodents << endl;
    rodents++;
    cout << "rats = " << rats;
    cout << ", rodents = " << rodents << endl;

// some implementations require type casting the following
// addresses to type unsigned
    cout << "rats address = " << &rats;
    cout << ", rodents address = " << &rodents << endl;
    // cin.get();
    return 0; 
}
