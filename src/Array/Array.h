#ifndef ARRAY_H
#define ARRAY_H

#include "Object.h"
#include "Exception.h"

namespace DataStLib
{
template <typename T>
class Array : public Object
{
protected:
	T* m_array;
public:
	virtual bool set(int i, const T& e)		//时间复杂度O(1)
	{
        bool ret = ((i >= 0) && (i < length()));
		if( ret )
		{
			m_array[i] = e;
		}
		return ret;
	}
	virtual bool get(int i,  T& e)const		//时间复杂度O(1)
	{
        bool ret = ((i >= 0) && (i < length()));
		if( ret )
		{
			e = m_array[i];
		}
		return ret;
	}
	T& operator[] (int i)		//时间复杂度O(1)
	{
        bool ret = ((i >= 0) && (i < length()));
		if( ret )
		{
			return m_array[i];
		}
		else
		{
            THROW_EXCEPTION(IndexOutOfBoundsException, "error in Array::operator[] (int i)");
		}
	}

	T operator[] (int i)const		//时间复杂度O(1)
	{
		return (const_cast<Array<T> &>(*this))[i];
	}

	T* array()
	{
		return m_array;
	}

    virtual int length()const = 0;
	
};
}



#endif // ARRAY_H

