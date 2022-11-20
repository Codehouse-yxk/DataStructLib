#ifndef DYNAMICARRAY
#define DYNAMICARRAY
#include <iostream>
#include "Array.h"
#include "Exception.h"
namespace DataStLib
{
template <typename T>
class DynamicArray : public Array<T>
{
protected:
	int m_length;

	/*
		重复代码逻辑抽象
		1. init—对象构造时的初始化操作
		2. copy—在堆空间中申请新的内存，并执行拷贝操作
		3. update—将指定的堆空间作为内部存储数组使用
	*/
	T* copy(T* array, int len, int newlen)		//时间复杂度O(n)
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
	void update(T* array, int length)			//时间复杂度O(1)
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
	void init(T* array, int length)		//时间复杂度O(1)
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
	DynamicArray(int length)			//时间复杂度O(1)
	{
		init(new T[length], length);
	}
	DynamicArray(const DynamicArray<T>& obj)			//时间复杂度O(n)
	{
        init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
	}
	DynamicArray<T>& operator= (const DynamicArray<T>& obj)			//时间复杂度O(n)
	{
		if(this != &obj)
		{
            update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
		}
		return *this;
	}
	int length()const			//时间复杂度O(1)
	{
		return m_length;
	}
	void resize(int length)			//时间复杂度O(n)
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
	~DynamicArray()			//时间复杂度O(1)
	{
		delete[] this->m_array;
	}
};
}


#endif // DYNAMICARRAY

