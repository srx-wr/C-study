#pragma once
#include<iostream>
#include<algorithm>
#include<assert.h>
using namespace std;

namespace wr
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		iterator begin()
		{
			return _start;
		}
		const_iterator begin() const
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}
		const_iterator end() const
		{
			return _finish;
		}
		size_t  size() const 
		{
			return _finish - _start;
		}

		size_t  capacity() const 
		{
			return _endofstorage - _start;
		}

		~vector()
		{
			delete[] _start;
			_start = _finish = _endofstorage = nullptr;
		}
		

		// 扩容不初始化  +  有bug版本，
		//void reserve(size_t n)
		////{
		////	if (n > capacity())
		////	{
		////		size_t sz = size();  // 记录数据的数量
		////		T* tmp = new T[n];
		////		memcpy(tmp, _start, sizeof(T) * sz);
		////		delete[] _start;
		////		_start = tmp;
		////		_finish = _start + sz;
		////		_endofstorage = _start + n;
		////	}
		////}
		//修复bug版本
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t sz = size();  // 记录数据的数量
				T* tmp = new T[n];
				if (_start)
				{
					for (size_t i = 0; i < sz; i++)
					{
						tmp[i] = _start[i];
					}
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + sz;
				_endofstorage = _start + n;
			}
		}

		// 扩容+ 初始化
		void resize(size_t n, const T& val = T())
		{
			if (n <= size())
			{
				_finish = _start + n;
			}
			else // 需要扩容的情况
			{
				if (n > capacity())
				{
					reserve(n);
				}
				while (_finish < _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
		}
		void push_back(const T& x)
		{
			// 容量不足需要扩容
			if (_finish == _endofstorage)
			{
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
			}
			*_finish = x;
			++_finish;
		}
		
		T& operator[](size_t i)
		{
			assert(i < size());
			return _start[i];
		}
		const T& operator[](size_t i) const 
		{
			assert(i < size());
			return _start[i];
		}

		void pop_back()
		{
			assert(_start < _finish);
			--_finish;

		}
		// 再pos位置插入x
		iterator insert(iterator pos, const T& x)
		{
			assert(pos >= _start && pos <= _finish);
			if (_finish >= _endofstorage)
			{
				size_t len = pos - _start;// 防止扩容之后pos的位置没有改变
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
				pos = _start + len; // 回到新的区间内
			}

			iterator end = _finish - 1; // 指向最后一个
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = x;
			_finish++;
			return pos;
		}
		// 删除pos位置的值
		iterator erase(iterator pos)
		{
			assert(pos >= _start && pos < _finish);
			iterator it = pos + 1;
			//while (it < _finish)// 会溢出
			//{
			//	*it = *(it + 1);
			//	it++;
			//}
			while (it < _finish)
			{
				*(it - 1) = *it;
				it++;
			}
			_finish--;
			return pos;

		}
		vector<T> operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}
		void swap(vector<T>& v)
		{
			std::swap(v._start, _start);
			std::swap(v._finish, _finish);
			std::swap(v._endofstorage, _endofstorage);
		}

		vector(const vector<T>& v)
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{
			reserve(v.capacity());
			for (auto e : v)
			{
				push_back(e);
			}
		}

		vector()	
		:_start(nullptr)
		,_finish(nullptr)
		,_endofstorage(nullptr)
		{}
		
		

	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};

	void test01()
	{
		//vector<int> v1;
		//v1.push_back(1);
		//v1.reserve(10);
		//vector<int>::iterator it = v1.begin();
		//while (it < v1.end())
		//{
		//	cout << *it << " ";
		//	it++;
		//}

		//vector<int> v2(v1);
		//vector<int>::iterator it1 = v1.begin();
		//while (it1 < v1.end())
		//{
		//	cout << *it1 << " ";
		//	it1++;
		//}
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);
		vector<int>::iterator it1 = v1.begin();
		while (it1 < v1.end())
		{
			cout << *it1 << " ";
			it1++;
		}

		v1.insert(find(v1.begin(), v1.end(), 2), 20);
		vector<int>::iterator it2 = v1.begin();
		while (it2 < v1.end())
		{
			cout << *it2 << " ";
			it2++;
		}
		v1.erase(v1.begin() + 1);
		vector<int>::iterator it3 = v1.begin();
		while (it3 < v1.end())
		{
			cout << *it3 << " ";
			it3++;
		}
	}
}