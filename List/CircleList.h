#ifndef CIRCLELIST
#define CIRCLELIST

#include "LinkList.h"

namespace DataStLib
{
template <typename T>
class CircleList : public LinkList<T>
{
protected:
	typedef typename LinkList<T>::Node Node;
	Node* last()const			//O(n)
	{
		return this->position(this->m_length-1)->next;
	}

    void last_to_first()const		//O(n)
	{
		last()->next = this->m_header.next;
	}
	int mod(int i)const		//O(1)
	{
		return (this->m_length==0) ? 0 : (i % this->m_length);
	}

public:
	bool insert(const T& e)			//O(n)
	{
		return insert(this->m_length,e);
	}
	bool insert(int i, const T & e)		//O(n)
	{
        bool ret = true;
        i = i % (this->m_length + 1);	//O(1)
        ret = LinkList<T>::insert(i,e);	//O(n)
		if( ret && (i==0))
		{
			last_to_first();			//O(n)
		}
		return ret;
	}
	bool remove(int i)		//O(n)
	{
        bool ret = true;
		i = mod(i);

		if( i==0 )		//ɾ���׽ڵ�
		{
			Node* toDel = this->m_header.next;

			if(toDel != NULL)
			{
				this->m_header.next = toDel->next;
				this->m_length--;
				if( this->m_length > 0 )
				{
					last_to_first();		//O(n)
					if(this->m_current == toDel)
					{
						this->m_current = toDel->next;
					}
				}
				else
				{
					this->m_header.next = NULL;
					this->m_current = NULL;
				}
				this->destroy(toDel);		//���һ�����ٽڵ㣬Ŀ�ģ��쳣��ȫ
			}
			else
			{
                return false;
			}
			
		}
		else
		{
			ret = LinkList<T>::remove(mod(i));		//O(n)
		}
        return ret;
	}
	
    bool set(int i, const T& e)		//O(n)
	{
		return LinkList<T>::set(mod(i),e);
	}

	T get(int i)const		//O(n)
	{
		return LinkList<T>::get(mod(i));
	}

	bool get(int i,const T & e)const	//O(n)
	{
        return LinkList<T>::get(mod(i), e);
	}
	int find(const T& e)const	//O(n)
	{
		int ret = -1;
		Node* slider = this->m_header.next;
        for(int i=0; i<this->m_length; i++)
		{
			if(slider->value == e)
			{
				ret = i;
				break;
			}
			slider = slider->next;
		}
		return ret;
	}
	void clear()		//O(n)
	{
		while( this->m_length > 1 )	//O(n)
		{
			remove(1);			//�˴����Ե���remove(0)������remove(0)ÿ�λ����last_to_first(),��Ӱ��Ч�ʣ�
								//O(1)
		}
		if( this->m_length == 1 )	//O(1)
		{
			Node* toDel = this->m_header.next;

			this->m_header.next = NULL;
			this->m_length = 0;
			this->m_current = NULL;

			this->destroy(toDel);
		}
	}

	bool move(int i, int step = 1)      	//���α궨λ��Ŀ��λ��
    										//O(n)
    {
        return LinkList<T>::move(mod(i), step);
	}
	bool end()      //�α��Ƿ񵽴�β�����Ƿ�Ϊ�գ�
    				//O(1)
    {
        return ((this->m_current == NULL) || (this->m_length == 0 ));
    }

	
	~CircleList()		//O(n)
	{
		clear();
	}
	
};
}

#endif // CIRCLELIST

