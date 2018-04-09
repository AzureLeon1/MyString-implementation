/*
Assignment 2 MyString
*/
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

class MyString
{

private:

	char* pstr = NULL;
	size_t len = 0;
	int* refCount = NULL;    //引用计数，用于COW


public:
	const char* getp() {return pstr; }

	MyString() {}

	MyString(const char str[])
	{

		len = strlen(str);
		//要使用strcpy，而strcpy会将字符串结尾的'\0'一起拷贝，此处若new的大小没有对len加1，
		//则strcpy过程会越界，且最后delete无法顺利完成
		pstr = new char[len + 1];
		pstr = strcpy(pstr, str);
		refCount = new int(1);
	}

	MyString(const MyString &str)
	{
		this->len = str.len;
		pstr = str.pstr;
		this->refCount = str.refCount;
		(*refCount)++;
	}

	~MyString()
	{
		if (refCount != NULL)
		{
			if ((*refCount) == 1)
			{
				delete[] pstr;
				delete refCount;    //引用计数不要忘记delete
			}
			else if ((*refCount) > 1)
			{
				(*refCount)--;
			}
		}

	}

	size_t size() const
	{
		return len;
	}

	//类中定义下标运算符，一般会定义两个版本
	//一个返回普通引用，另一个是类的常量成员并返回常量引用
	//在返回普通引用的版本函数中考虑COW
	//防止下标越界
	char& operator[](size_t n)
	{
		if (n >= len)
		{
			//越界处理
		}
		if ((*refCount) == 1)
		{
			return pstr[n];
		}
		else
		{
			(*refCount)--;
			char* tmp = new char[len + 1];
			pstr = myStrCpy(tmp, pstr, len);
			refCount = new int(1);
			return pstr[n];
		}

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
			pstr = new char[len + 1];
			pstr = strcpy(pstr, str);
			refCount = new int(1);
		}
		else
		{
			size_t oldLen = len;
			len = len + strlen(str);
			char* p2 = new char[len + 1];
			p2 = myStrCpy(p2, pstr, oldLen);

			if ((*refCount) == 1)
			{
				delete[] pstr;    //若之前进行strcpy前的new的大小不是len+1而是len，则此处delete出错
				pstr = myStrCat(p2, oldLen, str, strlen(str));
			}
			else
			{
				pstr = myStrCat(p2, oldLen, str, strlen(str));
				//对引用计数的处理
				(*refCount)--;
				refCount = new int(1);
			}

		}

	}
	void append(const MyString& str)
	{
		if (len == 0)
		{
			len = str.size();
			if (!len)
			{
				pstr = new char[len + 1];
				pstr = myStrCpy(this->pstr, str);
				refCount = new int(1);
			}
		}
		else
		{
			size_t oldLen = len;
			len = len + str.size();
			char* p2 = new char[len + 1];
			p2 = myStrCpy(p2, pstr, oldLen);

			if ((*refCount) == 1)
			{
				delete[] pstr;    //若之前进行strcpy前的new的大小不是len+1而是len，则此处delete出错
				pstr = p2;
				pstr = myStrCat(pstr, oldLen, str);
			}
			else
			{
				pstr = p2;
				pstr = myStrCat(pstr, oldLen, str);
				(*refCount)--;
				refCount = new int(1);
			}
		}
	}

	//6个关系运算符的重载函数
	//关系运算符中==与!=可以写出其中一个的代码，继而表示另一个
	//但>与<,>=与<=不行，因为这两者不是完全对立的
	bool operator==(const MyString& str)
	{
		for (size_t i = 0; i < max(this->len, str.len); i++)
		{
			if (this->pstr[i] != str.pstr[i])
			{
				return false;
			}
		}
		return true;
	}
	bool operator!=(const MyString& str)
	{
		return !(*this == str);
	}

	bool operator>(const MyString& str)
	{
		for (size_t i = 0; i < max(this->len, str.len); i++)
		{
			if (this->pstr[i] > str.pstr[i])
			{
				return true;
			}
			else if (this->pstr[i] < str.pstr[i])
			{
				return false;
			}
		}
		return false;
	}
	bool operator<(const MyString& str)
	{
		for (size_t i = 0; i < max(this->len, str.len); i++)
		{
			if (this->pstr[i] < str.pstr[i])
			{
				return true;
			}
			else if (this->pstr[i] > str.pstr[i])
			{
				return false;
			}
		}
		return false;
	}

	bool operator>=(const MyString& str)
	{
		for (size_t i = 0; i < max(this->len, str.len); i++)
		{
			if (this->pstr[i] > str.pstr[i])
			{
				return true;
			}
			else if (this->pstr[i] < str.pstr[i])
			{
				return false;
			}
		}
		return true;
	}
	bool operator<=(const MyString& str)
	{
		for (size_t i = 0; i < max(this->len, str.len); i++)
		{
			if (this->pstr[i] < str.pstr[i])
			{
				return true;
			}
			else if (this->pstr[i] > str.pstr[i])
			{
				return false;
			}
		}
		return true;
	}

	//自己编写的strcpy()可以处理字符串中存在'\0'的情况
	char* myStrCpy(char* p1, const MyString& str)
	{
		for (size_t i = 0; i < str.len; i++)
		{
			p1[i] = str.pstr[i];
		}
		p1[str.len] = '\0';
		return p1;
	}

	char* myStrCpy(char* p1, char* p2, size_t l)
	{
		for (size_t i = 0; i < l; i++)
		{
			p1[i] = p2[i];
		}
		p1[l] = '\0';
		return p1;
	}

	//自己编写的strcat()可以处理字符串中存在'\0'的情况
	char* myStrCat(char* p1, size_t l, const MyString& str2)
	{
		for (size_t i = 0; i < str2.len; i++)
		{
			p1[l + i] = str2.pstr[i];
		}
		p1[l + str2.len] = '\0';
		return p1;
	}

	char* myStrCat(char* p1, size_t l, const char* ps, size_t l2)
	{
		for (size_t i = 0; i < l2; i++)
		{
			p1[l + i] = ps[i];
		}
		p1[l + l2] = '\0';
		return p1;
	}

	//提供public member function用于输出运算符<<的重载
	void display(ostream& os) const
	{
		for (int i = 0; i < len; i++)
		{
			if (*(pstr + i) == 0)
			{
				os << '?';
			}
			else
			{
				os << *(pstr + i);
			}
		}
	}
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


