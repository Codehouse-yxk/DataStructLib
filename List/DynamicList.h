#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"

namespace DataStLib
{
template<typename T>
class DynamicList : public SeqList<T>
{
protected:
	int m_capacity;		//˳��洢�ռ�Ĵ�С
public:
	DynamicList(int capacity)
	{
		this->m_array = new T[capacity];
		if(this->m_array != NULL)
		{
			this->m_length = 0;
			this->m_capacity = capacity;
		}
		else
		{
			THROW_EXCEPTION(NoEnoughMemoryException, "In DynamicList(int capacity), the memory is applied failed");
		}
	}
	int capacity()const
	{
		return m_capacity;
	}

	void resize(int capacity)		//��������˳��洢�ռ�Ĵ�С
	{
		 if(capacity < 0)
		{
			THROW_EXCEPTION(InvalidParameterException, "error in void resize(int capacity)");
			return;
        }
		if(m_capacity != capacity)
		{
			T* array = new T[capacity];		//Ŀ�ģ�Ϊ������forѭ�����Ʋ�������֤�ڴ��е����ݲ��䡣
			if(array != NULL)
			{
				int length = ((this->m_length < capacity) ? this->m_length : capacity);
				for(int i=0; i<length; i++)
				{
					array[i] = this->m_array[i];	//���������array������T�Ƿ�ָ���ͣ�����=���������أ��˴�=�������ܻᷢ���쳣��
													//���Ǵ�ʱ��û���޸����Ա�˵����ʱ�����Ա������ǺϷ����õġ�
				}
                T* temp = this->m_array;	//����ʹ����ʱ������ֱ��ʹ��delete[] this->m_array����������������������ʱ�����������������׳��쳣�����쳣��
                							//�����Ӵ˴��ͻ᷵�أ���������ĸ�ֵ�޷�ִ�С�resize�����쳣���غ��޷���֤�����Ա�ȫ���ã�˵���˺�������ȫ��		
                							

                this->m_array = array;
				this->m_length = length;
				this->m_capacity = capacity;
				delete[] temp;				//�����������ʱ�˴��쳣���أ����Ǵ�ʱ�Ѿ���֤�����Ա��������á�
			}
			else
			{
	            THROW_EXCEPTION(NoEnoughMemoryException, "Exception In void DynamicList::resize(int capacity)");
			}
		}

	}
	~DynamicList()
	{
		delete[] this->m_array;
	}
};
}



#endif // DYNAMICLIST_H

