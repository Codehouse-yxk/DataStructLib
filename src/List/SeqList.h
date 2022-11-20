#ifndef SEQLIST_H
#define SEQLIST_H
#include "List.h"
#include "Exception.h"

namespace DataStLib
{
template<typename T>
class SeqList : public List<T>
{
protected:
	T* m_array;		//顺序存储空间，在子类中完成
    int m_length;	//当前线性表长度
public:
	bool insert(int i, const T& e)		//时间复杂度O(n)
	{
		bool ret = (i >= 0) && (i <= m_length);
		ret = ret && ( (m_length+1) <= capacity() );		//确保插入一个元素后，长度小于总容量
		if( ret )	//ret为1代表此次操作符合要求
		{
			for(int p=m_length-1; p>=i; p--)
			{
				m_array[p+1] = m_array[p];
			}
			m_array[i] = e;
			m_length++;
		}
		return ret;
	}
	bool insert(const T & e)		//重载插入函数，目的：直接在线性表尾部插入元素
	{
		return insert(m_length, e);
	}
    bool remove(int i)		//时间复杂度O(n)
	{
		bool ret = (i >= 0) && (i < m_length);
		if( ret )	//ret为1代表此次操作符合要求
		{
			for(int p=i; i<m_length-1; i++)
			{
				m_array[p] = m_array[p+1];
				p++;
			}
			m_length--;
		}
		return ret;
	}
    bool set(int i, const T& e)		//时间复杂度O(1)
    {
		bool ret = (i >= 0) && (i < m_length);
		if( ret )	//ret为1代表此次操作符合要求
		{
			m_array[i] = e;
		}
		return ret;
	}
    bool get(int i, T& e)const		//时间复杂度O(1)
    {
		bool ret = (i >= 0) && (i < m_length);
		if( ret )
		{
			e = m_array[i];
		}
		return ret;
	}
    int length() const		//时间复杂度O(1)
    {
		return m_length;
    }
    int find(const T& e)const		//时间复杂度O(n)
    {
		int ret = -1;
		for(int i=0; i<m_length; i++)
		{
			if(m_array[i] == e)
			{
				ret = i;
				break;
			}
		}
		return ret;
    }
    void clear()		//时间复杂度O(1)
    {
		m_length = 0;
	}
	//重载[]操作符，使可以用数组方式访问顺序存储线性表
	//此处考虑两种情况：一种是const对象和非const对象
	//若使用[]操作符，必须是线性表已经存在。也就是[]只能用作获取数据（如i=array[n]），而不能用来写入数据（如array[n]=i）
	T& operator[](int i)		//时间复杂度O(1)
    {
		bool ret = (i >= 0) && (i < m_length);
		if( ret )
		{
			return m_array[i];
		}
		else
		{
			THROW_EXCEPTION(IndexOutOfBoundsException, "Parament i is invalid in 'T& operator[](int i)'");
		}
	}
	T operator[](int i)const		//时间复杂度O(1)
	{
		/*
		bool ret = (i >= 0) && (i < m_length);
		if( ret )
		{
			return m_array[i];
		}
		else
		{
			THROW_EXCEPTION(IndexOutOfBoundsException, "Parament i is invalid in 'T operator[](int i)const'");
		}
		*/
		
		//与T& operator[](int i)实现完全一致，此处代码复用
		return (const_cast<SeqList<T>&>(*this))[i];
		
	}
	//顺序存储空间的容量，其是由子类来完成，所以此处为纯虚函数
    virtual int capacity()const = 0;
};	
}

#endif // SEQLIST_H

