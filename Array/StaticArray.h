#ifndef STATICARRAY_H
#define STATICARRAY_H

#include "Array.h"
namespace DataStLib
{
template <typename T, int N>
class StaticArray : public Array<T>
{
protected:
	T m_space[N];
public:
	StaticArray()			//ʱ�临�Ӷ�O(1)
	{
		this->m_array = m_space;
        cout << "StaticArray" << endl;
	}
	StaticArray(const StaticArray<T, N>& obj)			//ʱ�临�Ӷ�O(n)
	{
		this->m_array = m_space;
		for(int i=0; i<N; i++)
		{
			m_space[i] = obj.m_space[i];
		}
	}
	StaticArray<T, N>& operator= (const StaticArray<T, N>& obj)			//ʱ�临�Ӷ�O(n)
	{
		if(this != &obj)
		{
			for(int i=0; i<N; i++)
			{
				m_space[i] = obj.m_space[i];
			}
		}
		return *this;
	}

	int length()	const			//ʱ�临�Ӷ�O(1)
	{
		return N;
	}
};
}

#endif // STATICARRAY_H

