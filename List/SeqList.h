#ifndef SEQLIST_H
#define SEQLIST_H
#include "List.h"
#include "Exception/Exception.h"

namespace DataStLib
{
template<typename T>
class SeqList : public List<T>
{
protected:
	T* m_array;		//˳��洢�ռ䣬�����������
    int m_length;	//��ǰ���Ա���
public:
	bool insert(int i, const T& e)		//ʱ�临�Ӷ�O(n)
	{
		bool ret = (i >= 0) && (i <= m_length);
		ret = ret && ( (m_length+1) <= capacity() );		//ȷ������һ��Ԫ�غ󣬳���С��������
		if( ret )	//retΪ1����˴β�������Ҫ��
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
	bool insert(const T & e)		//���ز��뺯����Ŀ�ģ�ֱ�������Ա�β������Ԫ��
	{
		return insert(m_length, e);
	}
    bool remove(int i)		//ʱ�临�Ӷ�O(n)
	{
		bool ret = (i >= 0) && (i < m_length);
		if( ret )	//retΪ1����˴β�������Ҫ��
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
    bool set(int i, const T& e)		//ʱ�临�Ӷ�O(1)
    {
		bool ret = (i >= 0) && (i < m_length);
		if( ret )	//retΪ1����˴β�������Ҫ��
		{
			m_array[i] = e;
		}
		return ret;
	}
    bool get(int i, T& e)const		//ʱ�临�Ӷ�O(1)
    {
		bool ret = (i >= 0) && (i < m_length);
		if( ret )
		{
			e = m_array[i];
		}
		return ret;
	}
    int length() const		//ʱ�临�Ӷ�O(1)
    {
		return m_length;
    }
    int find(const T& e)const		//ʱ�临�Ӷ�O(n)
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
    void clear()		//ʱ�临�Ӷ�O(1)
    {
		m_length = 0;
	}
	//����[]��������ʹ���������鷽ʽ����˳��洢���Ա�
	//�˴��������������һ����const����ͷ�const����
	//��ʹ��[]�����������������Ա��Ѿ����ڡ�Ҳ����[]ֻ��������ȡ���ݣ���i=array[n]��������������д�����ݣ���array[n]=i��
	T& operator[](int i)		//ʱ�临�Ӷ�O(1)
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
	T operator[](int i)const		//ʱ�临�Ӷ�O(1)
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
		
		//��T& operator[](int i)ʵ����ȫһ�£��˴����븴��
		return (const_cast<SeqList<T>&>(*this))[i];
		
	}
	//˳��洢�ռ����������������������ɣ����Դ˴�Ϊ���麯��
    virtual int capacity()const = 0;
};	
}

#endif // SEQLIST_H

