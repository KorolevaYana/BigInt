#include "myvector.h"

my_vector::my_vector()
{
    this->which = 0;
    this->sz = 0;
}

my_vector::my_vector(my_vector const& other)
{
    this->which = other.which;
    this->sz = other.sz;
    if (other.which)
        this->avect = other.avect;
    else
        for (int i = 0; i < other.sz; i++)
            this->aconst[i] = other.aconst[i];
}

void my_vector::push_back(int a)
{
    if (this->sz < sconst)
        this->aconst[this->sz] = a;

    else if (this->sz == sconst)
    {
        this->avect = make_shared<vector <int> >();
        (*(this->avect)).resize(this->sz);
        for (int i = 0; i < this->sz; i++)
            (*(this->avect))[i] = this->aconst[i];
        this->avect->push_back(a);
        this->which = 1;
    }
    else
    {
        if (this->avect.use_count() > 1)
            this->avect = make_shared<vector <int> >();
        (*(this->avect)).push_back(a);
    }
    this->sz++;
}

void my_vector::pop_back()
{
    if (this->sz > sconst + 1)
        this->avect->pop_back();
    else if(this->sz == sconst + 1)
    {
        for (int i = 0; i < this->sz; i++)
            this->aconst[i] = (*(this->avect))[i];
        this->which = 0;
    }
    this->sz--;
}

void my_vector::resize(int new_s, int val)
{
    int tmp = this->sz;
    if (new_s > tmp)
        for (int i = 0; i < new_s - tmp; i++)
            this->push_back(val);
    else
        for (int i = 0; i < tmp - new_s; i++)
            this->pop_back();
}

void my_vector::resize(int new_s)
{
    int tmp = this->sz;
    if (new_s > tmp)
        for (int i = 0; i < new_s - tmp; i++)
            this->push_back(0);
    else
        for (int i = 0; i < tmp - new_s; i++)
            this->pop_back();
}

int my_vector::size() const
{
    return this->sz;
}

int& my_vector::operator [](int a)
{
    if (this->which)
        return (*(this->avect))[a];
    else
        return this->aconst[a];
}

const int& my_vector::operator [](int a) const
{
    if (this->which)
        return (*(this->avect))[a];
    else
        return this->aconst[a];
}

my_vector& my_vector::operator=(my_vector const &other)
{
    this->sz = other.sz;
    this->which = other.which;
    if (other.which)
        this->avect = other.avect;
    else
        for (int i = 0; i < other.sz; i++)
            this->aconst[i] = other.aconst[i];
    return *this;
}
