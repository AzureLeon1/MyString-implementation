//Assignment 2 Problem 1 Test
#include<iostream>
#include"mystring.h"
using namespace std;

int main()
{

	MyString mystr;
	MyString mystr2("a_string");
	MyString mystr3(mystr2);

	cout << mystr.size() << endl;
	cout << mystr2.size() << endl;

	cout << mystr3 << endl;

	mystr3[1] = ' ';
	cout << mystr3 << endl;

	mystr3[2] = 'b';
	cout << mystr3 << endl;
	
	cout << mystr2[1] << endl;

	mystr.append("foobar");
	cout << mystr.size() << endl;

	mystr2.append("_boxboz");
	cout << mystr2 << endl;

	mystr2.append(mystr3);
	cout << mystr2 << endl;

	cout << mystr3 << endl;

	cout << (MyString("abc") == MyString("abc")) << endl;
	cout << (MyString("abc") <= MyString("abc")) << endl;
	cout << (MyString("abd") == MyString("abc")) << endl;
	cout << (MyString("abc") != MyString("abc")) << endl;
	cout << (MyString("abd") != MyString("abc")) << endl;
	cout << (MyString("ab0") < MyString("ab1")) << endl;
	cout << (MyString("ab0") > MyString("ab1")) << endl;
	cout << (MyString("ab0") >= MyString("ab1")) << endl;
	cout << (MyString("15") < MyString("3")) << endl;

	const MyString cstr("a constant string");
	cout << cstr.size()<<endl;
	cout << cstr[2] << endl;
	cout << cstr << endl;

	//Problem 2

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
