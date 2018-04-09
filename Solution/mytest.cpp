//用于自行设置样例进行调试
#include<iostream>
#include"mystring.h"
using namespace std;

int main()
{

	//MyString mystr;
	//MyString mystr2("a_string");
	//MyString mystr3(mystr2);


	//mystr3[2] = 'n';

	MyString* s1 =new MyString("hello");
	MyString* s2 = new MyString(*s1);
	MyString* s3 = new MyString(*s1);
	s1->append(" world");

	delete s1;
	delete s2;
	delete s3;


	/*std::string str1 = "kakawater";
	std::string str3 = str1;
	std::string str2 = "kakawater";
	std::cout << "sizeof(str1) = " << sizeof(str1) << std::endl;
	std::cout << "sizeof(str2) = " << sizeof(str2) << std::endl;
	std::cout << "sizeof(str3) = " << sizeof(str3) << std::endl;


	printf("str1 address = %p\n", str1.c_str());
	printf("str2 address = %p\n", str2.c_str());
	printf("str3 address = %p\n\n", str3.c_str());

	str3[0] = 'K';

	printf("str1 address = %p\n", str1.c_str());
	printf("str2 address = %p\n", str2.c_str());
	printf("str3 address = %p\n", str3.c_str());*/



	return 0;
}
