// vect1.cpp -- introducing the vector template
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int NUM = 5;
int main()
{

    vector<int> ratings(NUM);
    vector<string> titles(NUM);
    /*
     * 声明一个迭代器
    */
    vector<string>::iterator pd;
    pd = titles.begin();
    cout << "You will do exactly as told. You will enter\n"
         << NUM << " book titles and your ratings (0-10).\n";
    int i;
    for (i = 0; i < NUM; i++)
    {
        cout << "Enter title #" << i + 1 << ": ";
        getline(cin,titles[i]);
        cout << "Enter your rating (0-10): ";
        cin >> ratings[i];
        cin.get();
    }
    titles.size();
    cout << "Thank you. You entered the following:\n"
          << "Rating\tBook\n";
    for (i = 0; i < NUM; i++)
    {
        cout << ratings[i] << "\t" << titles[i] << endl;
    }
    
    // cin.get();

    return 0; 
}
