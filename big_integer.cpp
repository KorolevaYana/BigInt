#include <iostream>
#include <vector>
#include <algorithm>

#include "big_integer.h"

const long long base = (1LL << 31);

using namespace std;

big_integer::big_integer() {
    this->sign = 0;
    this->val.push_back(0);
}

big_integer::big_integer(big_integer const& other) {
    this->val.resize((int)other.val.size(), 0);
    for (int i = 0; i < (int)other.val.size(); i++)
        this->val[i] = other.val[i];
    this->sign = other.sign;
}

big_integer::big_integer(int a) {
    if (a < 0) {
        this->sign = 1;
        a = -a;
    } else {
        this->sign = 0;
    }
    this->val.resize(0);
    this->val.push_back(a);
}

//============================================================

void big_integer::del_nul()
 {
     for (int i = (int)this->val.size() - 1; i > 0; i--)
     {
         if (this->val[i] == 0)
            this->val.pop_back();
         else
            break;
     }
 }


bool big_integer::is_nul()
{
    if ((int)(this->val.size()) == 1 && this->val[0] == 0)
        return true;
    return false;
}


 void big_integer::pls_mns_nul()
 {
     if ((int)this->val.size() == 1)
        if (this->val[0] == 0 && this->sign == 1)
            this->sign = 0;
}

 //============================================================

 int big_integer::div_long_short(int a)
{
    int carry = 0;
    long long tmp;
    for (int i = (int)this->val.size() - 1; i >= 0; i--)
    {
        tmp = (long long)carry * base + this->val[i];
        carry = tmp % a;
        this->val[i] = tmp / a;
    }
    this->del_nul();
    this->pls_mns_nul();
    return carry;
}

void big_integer::mul_long_short(int a)
{
    int carry = 0;
    long long tmp;
    for (int i = 0; i < (int)this->val.size(); i++)
    {
        tmp = (long long)this->val[i] * a + carry;
        carry = tmp / base;
        this->val[i] = tmp % base;
    }
    this->val.push_back(carry);
    this->del_nul();
    this->pls_mns_nul();
}

void big_integer::add_long_short(int a)
{
    long long tmp = (long long)this->val[0] + a;
    this->val[0] = tmp % base;
    int carry =  tmp / base;
    int i = 1;
    while (carry > 0 && i < (int)this->val.size())
    {
        tmp = (long long)this->val[i] + carry;
        this->val[i] = tmp % base;
        carry = tmp / base;
        i++;
    }
    this->val.push_back(carry);
    this->del_nul();
    this->pls_mns_nul();
}

//============================================================

big_integer::big_integer(std::string const& str)
{
    big_integer x;
    int i = 0;
    bool si = 0;
    if (str[i] == '-')
    {
        si++;
        i++;
    }
    while (i < (int)str.size())
    {
        x.mul_long_short(10);
        x.add_long_short((int)(str[i] - '0'));
        i++;
    }
    x.sign = si;
    x.del_nul();
    x.pls_mns_nul();
    *this = x;
}


ostream& operator<<(ostream& s, big_integer const& a) {
    s << to_string(a);
    return s;
}

string to_string(big_integer const& a)
{
    big_integer x = a;
    bool si = x.sign;
    string tmp;
    do {
        tmp.push_back(x.div_long_short(10) + '0');
    } while (!x.is_nul());
    if (si == 1)
        tmp.push_back('-');
    reverse(tmp.begin(), tmp.end());
    return tmp;
}
//=============================================================
big_integer& big_integer::operator=(big_integer const& other){
    this->val.resize((int)other.val.size());
        for (int i = 0; i < (int)other.val.size(); i++)
             this->val[i] = other.val[i];
    this->sign = other.sign;
    return *this;
}

big_integer& big_integer:: operator+=(big_integer const& rhs) {
    *this = *this + rhs;
    return *this;
}

big_integer& big_integer:: operator-=(big_integer const& rhs)
{
    *this = *this - rhs;
    return *this;
}

big_integer& big_integer:: operator*=(big_integer const& rhs)
{
    *this = *this * rhs;
    return *this;
}

big_integer& big_integer:: operator/=(big_integer const& rhs)
{
   *this = *this / rhs;
    return *this;
}

big_integer& big_integer:: operator%=(big_integer const& rhs)
{
   *this = *this % rhs;
    return *this;
}

big_integer& big_integer::operator&=(big_integer const& rhs)
{
    *this = *this & rhs;
    return *this;
}

big_integer& big_integer::operator|=(big_integer const& rhs)
{
    *this = *this | rhs;
    return *this;
}

big_integer& big_integer::operator^=(big_integer const& rhs)
{
    *this = *this ^ rhs;
    return *this;
}

big_integer& big_integer::operator<<=(int rhs)
{
    *this = *this << rhs;
    return *this;
}

big_integer& big_integer::operator>>=(int rhs)
{
    *this = *this >> rhs;
    return *this;
}



//================================================================

void sim_size(big_integer &a, big_integer &b)
{
    int a_size = a.val.size(), b_size = b.val.size();
    a.val.resize(max(a_size, b_size), 0);
    b.val.resize(max(a_size, b_size), 0);
}

big_integer clear_pls(big_integer a, big_integer const& b)
{
    big_integer x = b;
    sim_size(a, x);
    long long tmp;
    int carry = 0;
    for (int i = 0; i < (int)a.val.size(); i++)
    {
        tmp = (long long)a.val[i] + x.val[i] + carry;
        carry = tmp / base;
        a.val[i] = tmp % base;
    }
    a.val.push_back(carry);
    a.del_nul();
    a.pls_mns_nul();
    return a;
}

big_integer clear_mns(big_integer a, big_integer const& b)
{
    big_integer x = b;
    sim_size(a, x);
    int carry = 0;
    long long tmp;
    for (int i = 0; i < (int)a.val.size(); i++)
    {
        tmp = a.val[i] - (long long)x.val[i] - carry;
        if (tmp < 0)
        {
            a.val[i] = tmp + base;
            carry = 1;
        }
        else
        {
            a.val[i] = tmp;
            carry = 0;
        }
    }
    a.del_nul();
    a.pls_mns_nul();
    return a;
}

//============================================================
big_integer big_integer::operator+() const
{
    return *this;
}

big_integer big_integer::operator-() const
{
    big_integer res = *this;
    res.sign = !(res.sign);
    res.pls_mns_nul();
    return res;
}

big_integer big_integer::operator~() const
{
    big_integer res = --(-(*this));
    res.del_nul();
    res.pls_mns_nul();
    return res;
}
//============================================================

big_integer operator+(big_integer a, big_integer const& b)
{
    big_integer mod_a = a;
    big_integer mod_b = b;
    mod_a.sign = mod_b.sign = 0;
    big_integer res;
    if (a.sign == 0 && b.sign == 0)
        return clear_pls(mod_a, mod_b);
    if (a.sign == 0 && b.sign == 1)
    {
        if (mod_a >= mod_b)
            res = clear_mns(mod_a, mod_b);
        else
        {
            res = clear_mns(mod_b, mod_a);
            res.sign = 1;
        }
    }
    if (a.sign == 1 && b.sign == 0)
    {
        if (mod_a >= mod_b)
        {
            res = clear_mns(mod_a, mod_b);
            res.sign = 1;
        }
        else
            res = clear_mns(mod_b, mod_a);
    }
    if (a.sign == 1 && b.sign == 1)
    {
        res = clear_pls(mod_a, mod_b);
        res.sign = 1;
    }
    res.del_nul();
    res.pls_mns_nul();
    return res;
}

big_integer operator-(big_integer a, big_integer const& b)
{
    big_integer x = b;
    x.sign = !x.sign;
    return a + x;
}

big_integer operator*(big_integer a, big_integer const& b)
{
    big_integer mod_a = a;
    big_integer mod_b = b;
    sim_size(mod_a, mod_b);
    mod_a.sign = 0;
    mod_b.sign = 0;

    big_integer res;
    if (mod_b.val.size() == 1)
    {
        res = mod_a;
        res.mul_long_short(mod_b.val[0]);
    }
    else
    {
        big_integer tmp;

        for (int i = mod_b.val.size() - 1; i >= 0; i--)
        {
            tmp = mod_a;
            tmp.mul_long_short(mod_b.val[i]);
            res.val.push_back(0);
            res <<= 31;
            res += tmp;
            res.del_nul();
            res.pls_mns_nul();
        }
    }
    res.sign = a.sign ^ b.sign;
    res.del_nul();
    res.pls_mns_nul();

    return res;
}

/*big_integer operator/(big_integer a, big_integer const& b)
{
    big_integer mod_a = a;
    big_integer mod_b = b;
    big_integer res;
    mod_a.sign = mod_b.sign = 0;

    long long d_tmp = (base / ((long long)mod_b.val[(int)mod_b.val.size() - 1] + 1LL));
    int d = (int)d_tmp;

    if (d == 1)
        mod_a.val.push_back(0);
    else
    {
        mod_a.mul_long_short(d);
        mod_b.mul_long_short(d);
    }

    int j = mod_a.val.size() - mod_b.val.size();
    int n = mod_b.val.size();
    res.val.resize(j + 1);

    if (mod_a < mod_b)
    {
        a = big_integer(0);
        return a;
    }

    long long q_tmp, r_tmp;
    big_integer tmp, x, y;
    tmp.val.resize(n + 1);
    while (j >= 0)
    {
        for (int i = 0; i <= n; i++)
            tmp.val[i] = mod_a.val[j + i];
        q_tmp = (mod_a.val[j + n] * base + mod_a.val[j + n - 1]) / mod_b.val[n - 1];
        r_tmp = (mod_a.val[j + n] * base + mod_a.val[j + n - 1]) % mod_b.val[n - 1];
        if (q_tmp == base || q_tmp  * mod_b.val[n - 2] > r_tmp * base + mod_a.val[j + n - 2])
        {
            q_tmp--;
            r_tmp += mod_b.val[n - 1];
            if (r_tmp < base)
                if (q_tmp == base || q_tmp * mod_b.val[n - 2] > r_tmp * base + mod_a.val[j + n - 2])
                {
                    q_tmp--;
                    r_tmp += mod_b.val[n - 1];
                }
        }
        x = tmp;
        y = mod_b;
        y.mul_long_short(q_tmp);
        x -= y;
        for (int i = 0; i < (int)x.val.size(); i++)
            tmp.val[i] = x.val[i];
        for (int i = x.val.size(); i <= n; i++)
            tmp.val[i] = 0;
        res.val[j] = q_tmp;
        if (tmp.sign == 1)
        {
            res.val[j]--;
            tmp += mod_b;
        }
        for(int i = 0; i <= n; i++)
            mod_a.val[j + i] = tmp.val[i];
        j--;
    }

    bool si = a.sign ^ b.sign;
    res.sign = si;
    res.del_nul();
    res.pls_mns_nul();
    return res;
}
*/
big_integer operator/(big_integer a, big_integer const& b)
{
    big_integer mod_a = a;
    big_integer mod_b = b;
    big_integer res;
    mod_a.sign = mod_b.sign = 0;
    if (mod_a < mod_b)
        return big_integer(0);

    if (mod_b.val.size() == 1)
    {
        res = mod_a;
        res.div_long_short(mod_b.val[0]);
    }
    else
    {
        long long d_tmp = (base / ((long long)mod_b.val[(int)mod_b.val.size() - 1] + 1LL));
        int d = (int)d_tmp;

        if (d == 1)
            mod_a.val.push_back(0);
        else
        {
            mod_a.mul_long_short(d);
            mod_b.mul_long_short(d);
        }

        int m = mod_a.val.size() - mod_b.val.size();
        int n = mod_b.val.size();

        res.val.resize(m + 1);

        big_integer tmp;
        tmp.val.resize(m + 1);
        tmp.val[m] = 1;
        big_integer tmp1 = tmp * mod_b;

        if (mod_a >= tmp1)
        {
            res.val[m] = 1;
            mod_a -= tmp1;
        }

        long long qj;
        int x, y;
        for (int j = m - 1; j >= 0; j--)
        {
            x = y = 0;
            if (n + j < mod_a.val.size())
                x = mod_a.val[n + j];
            if (n + j - 1 < mod_a.val.size())
                y = mod_a.val[n + j - 1];
            qj = (x * base + y) / mod_b.val[n - 1];
            qj = min(qj, base - 1);
            tmp1 >>= 31;
            tmp = tmp1;
            tmp.mul_long_short(qj);
            mod_a -= tmp;
            while (mod_a < big_integer(0))
            {
                qj--;
                mod_a += tmp1;
            }
            res.val[j] = qj;
        }
    }
    res.sign = a.sign ^ b.sign;
    res.del_nul();
    res.pls_mns_nul();
    return res;
}

big_integer operator%(big_integer a, big_integer const& b)
{
    big_integer res = a / b;
    big_integer res1 = a - (b * res);
    return res1;
}

//============================================================
big_integer& big_integer::operator++()
{
    *this += big_integer(1);
    return *this;
}

big_integer big_integer::operator++(int)
{
    big_integer res = *this;
    *this += big_integer(1);
    return res;
}

big_integer& big_integer::operator--()
{
    *this -= big_integer(1);
    return *this;
}

big_integer big_integer::operator--(int)
{
    big_integer res = *this;
    *this -= big_integer(1);
    return res;
}
//============================================================
big_integer to_code(big_integer a)
{
    if (a.sign == 1)
    {
        for (int i = 0; i < (int)a.val.size(); i++)
        {
            a.val[i] = ~a.val[i] + 1;
            a.val[i] = a.val[i] & ((1L << 30) - 1);
        }
    }
    return a;
}

big_integer operator&(big_integer a, big_integer const& b)
{
    big_integer x = b;
    sim_size(a, x);
    a = to_code(a);
    x = to_code(x);

    for (int i = 0; i < (int)a.val.size(); i++)
        a.val[i] = a.val[i] & x.val[i];
    a.sign = a.sign & x.sign;
    a = to_code(a);
    a.del_nul();
    a.pls_mns_nul();
    return a;
}

big_integer operator|(big_integer a, big_integer const& b)
{
    big_integer x = b;
    sim_size(a, x);
    a = to_code(a);
    x = to_code(x);

    for (int i = 0; i < (int)a.val.size(); i++)
        a.val[i] = a.val[i] | x.val[i];
    a.sign = a.sign | x.sign;
    a = to_code(a);
    a.del_nul();
    a.pls_mns_nul();
    return a;
}

big_integer operator^(big_integer a, big_integer const& b)
{
    big_integer x = b;
    sim_size(a, x);
    a = to_code(a);
    x = to_code(x);

    for (int i = 0; i < (int)a.val.size(); i++)
        a.val[i] = a.val[i] ^ x.val[i];
    a.sign = a.sign ^ x.sign;
    a = to_code(a);
    a.del_nul();
    a.pls_mns_nul();
    return a;
}

//============================================================
big_integer operator<<(big_integer a, int b)
{
    a = to_code(a);
    for (int i = a.val.size() - b / 31 - 1; i >= 0; i--)
        a.val[i + b / 31] = a.val[i];
    a.val[a.val.size() - 1] = a.val[a.val.size() - 1] << (b % 31);
    if ((a.val[a.val.size() - 1] & (1 << 31)) != 0)
        a.sign = 1;
    else
        a.sign = 0;
    a.val[a.val.size() - 1] = a.val[a.val.size() - 1] & ((1 << 31) - 1);
    for (int i = b / 31 - 1; i >= 0; i--)
        a.val[i] = 0;
    for (int i = a.val.size() - 1; i >= 0; i--)
        if (i - 1 >= 0)
        {
            a.val[i] = a.val[i] | (((((1 << (b % 31)) - 1) << (31 - b % 31)) & a.val[i - 1]) >> (31 - b % 31));
            a.val[i - 1] = a.val[i - 1] << (b % 31);
            a.val[i - 1] = (a.val[i - 1] & ((1 << 31) - 1));
        }
    a = to_code(a);
    a.del_nul();
    a.pls_mns_nul();
    return a;
}

big_integer operator>>(big_integer a, int b)
{
    a = to_code(a);
    for (int i = b / 31; i < (int)a.val.size(); i++)
        a.val[i - b / 31] = a.val[i];
    for (int i = b / 31; i > 0; i--)
    {
        if (a.sign == 1)
            a.val[a.val.size() - i] = ((1L << 30) - 1);
        else
            a.val[a.val.size() - i] = 0;
    }
    for (int i = 0; i < (int)a.val.size(); i++)
    {
        a.val[i] = a.val[i] >> (b % 31);
        if (i + 1 < (int)a.val.size())
            a.val[i] = a.val[i] | (((1 << (b % 31)) - 1) & a.val[i + 1]) << (30 - b % 31);
        else
            if (a.sign == 1)
                a.val[i] = a.val[i] | (((1 << (b % 31)) - 1) << (30 - b % 31));
    }
    a = to_code(a);
    a.del_nul();
    a.pls_mns_nul();
    return a;
}
//============================================================

bool big_integer:: operator==(big_integer const& b) const {
    if (this->val.size() != b.val.size() || this->sign != b.sign)
        return false;
    for (int i = 0; i < (int)b.val.size(); i++)
        if (this->val[i] != b.val[i])
            return false;
    return true;
}

bool big_integer:: operator!=(big_integer const& b) const {
    return !(*this == b);
}

bool big_integer:: operator<(big_integer const& b) const {
    if (this->sign == 1 && b.sign == 0)
        return true;
    if (this->sign == 0 && b.sign == 1)
        return false;
    if (this->val.size() < b.val.size())
    {
        if (this->sign == 0)
            return true;
        else
            return false;
    }
    else if (this->val.size() > b.val.size())
    {
        if (this->sign == 1)
            return true;
        else
            return false;
    }
    else {
        for(int i = (int)this->val.size() - 1; i >= 0; i--) {
            if (this->val[i] < b.val[i])
            {
                if (this->sign == 0)
                    return true;
                else
                    return false;
            }
            if (this->val[i] > b.val[i])
            {
                if (this->sign == 1)
                    return true;
                else
                    return false;
            }
        }
        return false;
    }
}

bool big_integer:: operator>(big_integer const& b) const {
    if (*this != b && !(*this < b))
        return true;
    else
        return false;
}

bool big_integer:: operator<=(big_integer const& b) const {
    return (!(*this > b));
}

bool big_integer:: operator>=(big_integer const& b) const {
    if (!(*this < b))
        return true;
    else
        return false;
}



