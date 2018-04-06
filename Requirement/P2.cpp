//Assignment 2 Problem 2 Test
#include<iostream>
#include"mystring.h"
using namespace std;

int main()
{

	MyString mystr("abc123");
	cout << mystr.size() << endl;

	mystr[2] = '\0';
	cout << mystr.size() << endl;

	MyString mystr2(mystr);
	cout << mystr2.size() << endl;

	MyString mystr3("foo");
	mystr3.append(mystr);
	cout << mystr3.size() << endl;

	cout << mystr3 << endl;

	return 0;
}
