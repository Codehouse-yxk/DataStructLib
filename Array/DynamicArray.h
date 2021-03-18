#ifndef DYNAMICARRAY
#define DYNAMICARRAY
#include <iostream>
#include "Array.h"
#include "Exception/Exception.h"
namespace DataStLib
{
template <typename T>
class DynamicArray : public Array<T>
{
protected:
	int m_length;

	/*
		�ظ������߼�����
		1. init��������ʱ�ĳ�ʼ������
		2. copy���ڶѿռ��������µ��ڴ棬��ִ�п�������
		3. update����ָ���Ķѿռ���Ϊ�ڲ��洢����ʹ��
	*/
	T* copy(T* array, int len, int newlen)		//ʱ�临�Ӷ�O(n)
	{
		T* ret = new T[newlen];

		if(ret != NULL)
		{
			int size = (newlen > len) ? len : newlen;
			for(int i=0; i<size; i++)
			{
				ret[i] = array[i];
			}
		}
		return ret;
	}
	void update(T* array, int length)			//ʱ�临�Ӷ�O(1)
	{
		if(array != NULL)
		{
			T* temp = this->m_array;

			this->m_array = array;
			this->m_length = length;

			delete[] temp;
		}
		else
		{
			THROW_EXCEPTION(NoEnoughMemoryException, "error in void updata(T* array, int length)");
		}
	}
	void init(T* array, int length)		//ʱ�临�Ӷ�O(1)
	{
		if(array != NULL)
		{
			this->m_array = array;
			this->m_length = length;
		}
		else
		{
			THROW_EXCEPTION(NoEnoughMemoryException, "error in void init(T* array, int length)");
		}
	}
public:
	DynamicArray(int length)			//ʱ�临�Ӷ�O(1)
	{
		init(new T[length], length);
	}
	DynamicArray(const DynamicArray<T>& obj)			//ʱ�临�Ӷ�O(n)
	{
        init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
	}
	DynamicArray<T>& operator= (const DynamicArray<T>& obj)			//ʱ�临�Ӷ�O(n)
	{
		if(this != &obj)
		{
            update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
		}
		return *this;
	}
	int length()const			//ʱ�临�Ӷ�O(1)
	{
		return m_length;
	}
	void resize(int length)			//ʱ�临�Ӷ�O(n)
	{
        if(length < 0)
		{
			THROW_EXCEPTION(InvalidParameterException, "error in void resize(int length)");
			return;
        }
		
		if(m_length != length)
		{
			update(copy(this->m_array, m_length, length), length);	
		}
	}
	~DynamicArray()			//ʱ�临�Ӷ�O(1)
	{
		delete[] this->m_array;
	}
};
}


#endif // DYNAMICARRAY

