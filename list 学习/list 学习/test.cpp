#include<iostream>
#include<list>

using namespace std;

int main()
{
	list<int> l1;
	list<int> l2(5, 3);
	list<int> l3(l1);
	list<int>::iterator it = l2.begin();
	while (it != l2.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
	for (auto li : l2)
	{
		cout << li << " ";
	}


	return 0;
}