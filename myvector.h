#include <vector>
#include <memory>
#include <iostream>

using namespace std;

const int sconst = 12;

struct my_vector
{
    bool which;
    int sz;
    int aconst[sconst];
    shared_ptr<vector <int> > avect;
    my_vector();
    my_vector(my_vector const& other);

    void push_back(int a);
    void pop_back();
    void resize(int new_s, int val);
    void resize(int new_s);
    int size() const;

    int& operator [](int a);
    const int& operator [](int a) const;
    my_vector& operator=(my_vector const &other);
};
