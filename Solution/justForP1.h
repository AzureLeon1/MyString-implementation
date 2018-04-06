#include<iostream>
#include<cstring>
using namespace std;

class MyString
{

private:
	
	char* pstr = NULL;
	int len = 0;


public:

	MyString(){}

	MyString(const char str[])
	{
		
		len = strlen(str);
		//要使用strcpy，而strcpy会将字符串结尾的'\0'一起拷贝，此处若new的大小没有对len加1，
		//则strcpy过程会越界，且最后delete无法顺利完成
		pstr = new char [len+1];   
		pstr = strcpy(pstr, str);
	}

	MyString(const MyString &str)
	{
		len = str.size();
		pstr = new char[len+1];
		pstr = strcpy(this->pstr, str.pstr);
	}

	int size() const
	{
		return len;
	}
	
	void display(ostream& os) const
	{
		for (int i = 0; i < len; i++)
		{
			os << *(pstr + i);
		}
	}

	//类中定义下标运算符，一般会定义两个版本
	//一个返回普通引用，另一个是类的常量成员并返回常量引用
	//防止下标越界
	char& operator[](size_t n)
	{
		if (n >= len)
		{
			//越界处理
		}
		return pstr[n];
	}
	const char& operator[] (size_t n) const
	{
		if (n >= len)
		{
			//越界处理
		}
		return pstr[n];
	}

	void append(const char str[])
	{
		if (len == 0)
		{
			len = strlen(str);
			pstr = new char[len+1];
			pstr = strcpy(pstr, str);
		}
		else
		{
			len = len + strlen(str);
			char* p2 = new char [len+1];
			p2 = strcpy(p2, pstr);           
			p2 = strcat(p2, str);
			delete[] pstr;    //若之前进行strcpy前的new的大小不是len+1而是len，则此处delete出错
			pstr = p2;
		}
		
	}
	void append(const MyString str)
	{
		if (len == 0)
		{
			len = str.size();
			if (len == 0)
			{ }
			else
			{
				pstr = new char[len + 1];
				pstr = strcpy(this->pstr, str.pstr);
			}
		}
		else
		{
			len = len + str.size();
			char* p2 = new char[len + 1];
			p2 = strcpy(p2, pstr);
			p2 = strcat(p2, str.pstr);
			delete[] pstr;    //若之前进行strcpy前的new的大小不是len+1而是len，则此处delete出错
			pstr = p2;
		}
	}

	bool operator==(const MyString& str)
	{
		if (!strcmp(this->pstr, str.pstr))
			return true;
		else
			return false;
	}
	bool operator!=(const MyString& str)
	{
		return !(*this == str);
	}

	bool operator>(const MyString& str)
	{
		if (strcmp(this->pstr, str.pstr)>0)
			return true;
		else
			return false;
	}
	bool operator<(const MyString& str)
	{
		return !(*this > str);
	}
	
	//关系运算符中==与!=,>与<可以写出其中一个的代码，继而表示另一个
	//但>=与<=不行，因为这两者不是完全对立的
	bool operator>=(const MyString& str)
	{
		if (strcmp(this->pstr, str.pstr)>=0)
			return true;
		else
			return false;
	}
	bool operator<=(const MyString& str)
	{
		if (strcmp(this->pstr, str.pstr) <= 0)
			return true;
		else
			return false;
	}


	//char* copy(const char s[], char* p)
	//{
	//	for (int i = 0; i < len; i++)
	//	{
	//		*(p + i) = s[i];
	//	}
	//	return p;
	//}


};

//一、输入、输出运算符都必须是非成员函数。否则，他们的左侧运算对象将是我们的类的一个对象。
//二、要访问类中的私有成员：
//    方法1：把该函数声明为友元函数
//    方法2：调用MyString类中提供的public member function
ostream& operator<<(ostream& os, const MyString &str)
{
	str.display(os);
	return os;
}



