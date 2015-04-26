#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <vector>
#include "myvector.h"

using namespace std;

struct big_integer
{
//    private:
        my_vector val;
        bool sign;
//    public:
        big_integer();
        big_integer(big_integer const& other);
        big_integer(int a);
        explicit big_integer(std::string const& str);
/*    ~big_integer();
*/

    int div_long_short(int a);
    void mul_long_short(int a);
    void add_long_short(int a);
    void del_nul();
    void pls_mns_nul();
    bool is_nul();
    big_integer& operator=(big_integer const& other);

    big_integer& operator+=(big_integer const& rhs);
    big_integer& operator-=(big_integer const& rhs);
    big_integer& operator*=(big_integer const& rhs);
    big_integer& operator/=(big_integer const& rhs);
    big_integer& operator%=(big_integer const& rhs);

    big_integer& operator&=(big_integer const& rhs);
    big_integer& operator|=(big_integer const& rhs);
    big_integer& operator^=(big_integer const& rhs);


    big_integer& operator<<=(int rhs);
    big_integer& operator>>=(int rhs);

    big_integer operator+() const;
    big_integer operator-() const;
    big_integer operator~() const;

    big_integer& operator++();
    big_integer operator++(int);


    big_integer& operator--();
    big_integer operator--(int);

    bool operator==(big_integer const& b) const;
    bool operator!=(big_integer const& b) const;
    bool operator<(big_integer const& b) const;
    bool operator>(big_integer const& b) const;
    bool operator<=(big_integer const& b) const;
    bool operator>=(big_integer const& b) const;

};

big_integer operator+(big_integer a, big_integer const& b);
big_integer operator-(big_integer a, big_integer const& b);
big_integer operator*(big_integer a, big_integer const& b);
big_integer operator/(big_integer a, big_integer const& b);
big_integer operator%(big_integer a, big_integer const& b);

big_integer operator&(big_integer a, big_integer const& b);
big_integer operator|(big_integer a, big_integer const& b);
big_integer operator^(big_integer a, big_integer const& b);

big_integer operator<<(big_integer a, int b);
big_integer operator>>(big_integer a, int b);

std::ostream& operator<<(std::ostream& s, big_integer const& a);
string to_string(big_integer const& a);

#endif // BIG_INTEGER_H
