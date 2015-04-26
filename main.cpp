#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include "list.h"

using namespace std;

void test1() 
{
	cout << "Test 1 " << endl;
	list a;
	list::iterator i = a.end();
	a.push_back(5);
	--i;
	assert(*i == 5);
	cout << "Test 1 is finished" << endl << endl;
}

void test2() 
{
	cout << "Test 2 " << endl;
	list a;
	a.push_back(1); a.print();
	a.push_back(2); a.print();
	a.pop_front(); a.print();
	a.push_front(0); a.print();
	a.pop_front(); a.print();
	a.pop_back(); a.print();
	cout << "Test 2 is finished" << endl << endl;
}

void test3() 
{
	cout << "Test 3 " << endl;
	list a;
	a.push_back(1); a.print();
	a.push_back(2); a.print();
	a.push_back(3); a.print();
	a.push_back(4); a.print();
	a.push_back(5); a.print();
	a.pop_front(); a.print();
	list::iterator it = a.begin();
	it++; it++;
	a.erase(it); a.print();
	a.pop_back(); a.print();
	cout << "Test 3 is finished" << endl << endl;
}

void test4() 
{
	cout << "Test 4 " << endl;
	list a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5); a.print();
	list::iterator it = a.begin();
	it++;
	it++;
	a.erase(it++); a.print();
	it = a.begin();
	it++;
	a.erase(++it); a.print();
	cout << "Test 4 is finished" << endl << endl;
}

void test5() 
{
	cout << "Test 5 " << endl;
	list a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);

	list b;
	b.push_back(1);
	b.push_back(2);
	b.push_back(3);
	b.push_back(4);
	b.push_back(5);

	list::iterator it = a.begin();
	it++; it++;
	list::iterator it1 = b.begin(); it1++;
	list::iterator it2 = b.end();
	it2--;
	a.splice(it, b, it1, it2);
	a.print();
	b.print();

	cout << "Test 5 is finished" << endl << endl;
}

void test6() 
{
	cout << "Test 6 " << endl;
	list a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);

	list b;
	b.push_back(1);
	b.push_back(2);
	b.push_back(3);
	b.push_back(4);
	b.push_back(5);

	list::iterator it = a.end();
	list::iterator it1 = b.begin();
	list::iterator it2 = b.end();
	a.splice(it, b, it1, it2);
	a.print();
	b.print();

	cout << "Test 6 is finished" << endl << endl;
}

void test7() 
{
	cout << "Test 7 " << endl;
	list a;
	a.push_back(1);
	a.push_back(2);

	list b;
	b.push_back(3);
	a.print();
	try {
		a = b;
	}
	catch (...) {}
	a.print();
	b.push_front(-123);
	a = b;
	a.print();

	cout << "Test 7 is finished" << endl << endl;
}

void test8() 
{
	cout << "Test 8 " << endl;
	list a;
	a.push_back(1);
	a.push_back(2);

	list b(a);
	b.print();
	list c = a;
	c.print();

	cout << "Test 8 is finished" << endl << endl;
}

void test9()
{
	cout << "Test 9 " << endl;
	int n = 10;
	list a;
	for (int i = 0; i < n; i++)
		a.push_back(rand() % 10);
	a.print();
	for (list::iterator it = a.begin(); it != a.end(); it++)
		cout << *it << ' ';
	cout << endl;
	for (list::reverse_iterator it = a.rbegin(); it != a.rend(); it++)
		cout << *it << ' ';
	cout << endl;

	cout << "Test 9 is finished" << endl << endl;
}

int main() 
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();

	int a = 5;
}
