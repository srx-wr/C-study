#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 
#include<iostream>
#include<cstring>
#include<string>
#include<assert.h>

using namespace std;

namespace wr
{
	class string
	{
		friend ostream& operator << (ostream& _cout, const wr::string& s);
		friend istream& operator >> (istream& _cin, wr::string& s);
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
	public:
		string(const char* str = "")
			:_size(strlen(str)) //
			,_capacity(_size)
		{
			_str = new char[_capacity + 1]; // 多的一个空间用来存储'\0'
			strcpy(_str, str);// 把str的值拷贝给当前类的_str
		}
		// 拷贝构造  现代写法
		string(const string& s)
			:_str(nullptr)
		{
			string tmp(s._str); // 调用传参构造进行构造
			swap(tmp);     
		}
		// 赋值重载的现代写法 
		// 讲解：
		string& operator=(string s)
		{
			this->swap(s);
			return *this;
		}
		// 前面将 iterator 重命名 其实他就是char* 
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size; // 指向末尾位置
		}
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str + _size;
		}
		void push_back(char c)
		{
			// 扩容
			if (_size >= _capacity)
			{
				size_t newCapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newCapacity);
			}
			_str[_size] = c;
			_size++;
			_str[_size] = '\0';

		}
		string& operator +=(char c)
		{
			push_back(c);
			return *this;
		}
		// 尾插一个字符串
		void append(const char* str)
		{
			size_t len = strlen(str);

			// 扩容
			if (len + _size >= _capacity)
			{
				reserve(len + _size);
			}
			strcpy(_str + _size, str); // 在_str 后面拷贝一个str
			_str = _str + len; //这里考虑一下边界，是没错的
		}
		// 扩容
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}
		}

		string& operator += (const char* str)
		{
			append(str);
			return *this;
		}


		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}

		void swap(string& s)
		{
			::swap(_str, s._str);
			::swap(_capacity, s._capacity);
			::swap(_size, s._size);
		}
		const char* c_str() const
		{
			return _str;
		}

		size_t capacity() const
		{
			return _capacity;
		}
		bool empty() const
		{
			return _size == 0;
		}
		// 当需要修改的时候
		char& operator[] (size_t index)
		{
			assert(index < _size);
			return _str[index];
		}
		// 不需要修改的时候
		const char& operator[] (size_t index) const
		{
			assert(index < _size);
			return _str[index];
		}
		bool operator == (const string& s)
		{
			return strcmp(s._str, _str) == 0;
		}
		bool operator < (const string& s)
		{
			return strcmp(s._str, _str) > 0;
		}
		bool operator <= (const string& s)
		{
			return strcmp(s._str, _str) >= 0;
		}

		bool operator > (const string& s)
		{
			return strcmp(s._str, _str) < 0;
		}		
		bool operator >= (const string& s)
		{
			return strcmp(s._str, _str) <= 0;
		}
		bool operator != (const string& s)
		{
			return strcmp(s._str, _str) != 0;
		}

		// 返回c在string中第一次出现的位置
		size_t find(char c, size_t pos = 0) const
		{
			assert(!empty());
			for (int i = 0; i < _size; i++)
			{
				if (_str[i] == c)
				{
					pos = i;
					break;

				}
			}
			return pos;
		}
		// 返回字串 s 在string 中第一次出现的位置
		size_t find(const char* s, size_t pos = 0) const
		{
			assert(s);
			// const 在前值不能变指向可以改变
			const char* str1 = nullptr;
			const char* str2 = nullptr;
			const char* p = _str; // p指向 _str的初始位置
			while (*p)
			{
				str1 = p;
				str2 = s;
				while ((*str1 == *str2) && str1 && str2)
				{
					str1++;
					str2++;

				}
				// 如果子串走完
				if (*str2 == '\0')
				{
					pos = find(s[0]);
					break;
				}
				// p向后走
				++p;
			}
		}
		// 在pos位置插入 char c
		string& insert(size_t pos, char c)
		{
			assert(pos >= 0 && pos <= _size);
			if (_size == _capacity)
			{
				size_t newCapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newCapacity);// 扩容
			}
			size_t end = _size + 1;
			while (end > pos)
			{
				_str[end] = _str[end - 1];
				end--;
			}
			_str[pos] = c;
			_size++;
			return *this;

		}
		// 在pos位置插入字符串s
		string& insert(size_t pos, const char* s)
		{
			assert(pos >= 0 && pos <= _size);
			int len = strlen(s);
			if (len == 0)
			{
				return *this;
			}
			if (len + _size > _capacity)
			{
				reserve(len + _size);
			}
			size_t end = len + _size;
			while (end >= pos + len)
			{
				_str[end] = _str[end - len];
				end--;
			}
			for (size_t i = 0; i < len; i++)
			{
				_str[pos + i] = s[i];
			}
			_size += len;
			return *this;
		}
		// 删除pos位置上的元素（从pos开始删除len个元素），并返回该元素的下一个位置
		string& erase(size_t pos,size_t len = npos)
		{
			//‘\0不能删呗’
			assert(pos < _size);
			// 超过了
			if (len == npos || pos + len > _size)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
			return *this;
		}

		~string()
		{
			delete[] _str;
			_str = nullptr;
		}

	private:
		char* _str; //	装元素指针
		size_t _size;//  大小
		size_t _capacity;// 容量
		static const size_t npos;
	};
	ostream& operator << (ostream& cout, const wr::string& s)
	{
		for (size_t i = 0; i < s._size; i++)
		{
			cout << s[i];
		}
		return cout;
	}
	istream& operator >> (istream& cout, wr::string& s)
	{
		for (size_t i = 0; i < s._size; i++)
		{
			cin >> s[i];
		}
		return cin;
	}
	const size_t string::npos = -1;


	//ostream& operator << (ostream& _cout, const wr::string& s)
	//{
	//	for (size_t i = 0; i < s._size; i++)
	//	{
	//		_cout << s[i];
	//	}
	//	return _cout;
	//}


	void test()
	{
		string s1 = "ancdefh";
		string s2 = s1;
		s2.push_back('c');
	}
}