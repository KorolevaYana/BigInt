#include <cstdio>
#include <iostream>
#include "big_integer.h"

using namespace std;

int main()
{

    /*my_vector a;

    for (int i = 0; i < 1000; i++)
        a.push_back(i);

    a.resize(2000);
    my_vector b;
    b = a;
    for (int i = 0; i < b.size(); i++)
        cout << b[i] << ' ';*/

    big_integer a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");//"17179869184");
    big_integer b("100000000000000000000000000000000000000");//"17179869184");

//    cout << a.val[0] << " " << a.val[1] << endl;
//    big_integer b(100);
//    big_integer c(200);
//    c += b;
//    a += b;
 //   cout << (a += b) <fghh< endl;
    big_integer c;
    c = a * b;
    cout << a * b << endl << (a * b / b) << endl << a << endl;
    return 0;
}
