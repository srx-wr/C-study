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
			_str = new char[_capacity + 1]; // ���һ���ռ������洢'\0'
			strcpy(_str, str);// ��str��ֵ��������ǰ���_str
		}
		// ��������  �ִ�д��
		string(const string& s)
			:_str(nullptr)
		{
			string tmp(s._str); // ���ô��ι�����й���
			swap(tmp);     
		}
		// ��ֵ���ص��ִ�д�� 
		// ���⣺
		string& operator=(string s)
		{
			this->swap(s);
			return *this;
		}
		// ǰ�潫 iterator ������ ��ʵ������char* 
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size; // ָ��ĩβλ��
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
			// ����
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
		// β��һ���ַ���
		void append(const char* str)
		{
			size_t len = strlen(str);

			// ����
			if (len + _size >= _capacity)
			{
				reserve(len + _size);
			}
			strcpy(_str + _size, str); // ��_str ���濽��һ��str
			_str = _str + len; //���￼��һ�±߽磬��û���
		}
		// ����
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
		// ����Ҫ�޸ĵ�ʱ��
		char& operator[] (size_t index)
		{
			assert(index < _size);
			return _str[index];
		}
		// ����Ҫ�޸ĵ�ʱ��
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

		// ����c��string�е�һ�γ��ֵ�λ��
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
		// �����ִ� s ��string �е�һ�γ��ֵ�λ��
		size_t find(const char* s, size_t pos = 0) const
		{
			assert(s);
			// const ��ǰֵ���ܱ�ָ����Ըı�
			const char* str1 = nullptr;
			const char* str2 = nullptr;
			const char* p = _str; // pָ�� _str�ĳ�ʼλ��
			while (*p)
			{
				str1 = p;
				str2 = s;
				while ((*str1 == *str2) && str1 && str2)
				{
					str1++;
					str2++;

				}
				// ����Ӵ�����
				if (*str2 == '\0')
				{
					pos = find(s[0]);
					break;
				}
				// p�����
				++p;
			}
		}
		// ��posλ�ò��� char c
		string& insert(size_t pos, char c)
		{
			assert(pos >= 0 && pos <= _size);
			if (_size == _capacity)
			{
				size_t newCapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newCapacity);// ����
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
		// ��posλ�ò����ַ���s
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
		// ɾ��posλ���ϵ�Ԫ�أ���pos��ʼɾ��len��Ԫ�أ��������ظ�Ԫ�ص���һ��λ��
		string& erase(size_t pos,size_t len = npos)
		{
			//��\0����ɾ�¡�
			assert(pos < _size);
			// ������
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
		char* _str; //	װԪ��ָ��
		size_t _size;//  ��С
		size_t _capacity;// ����
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