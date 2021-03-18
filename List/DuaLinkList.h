#ifndef DUALINKLIST
#define DUALINKLIST

#include "List.h"
#include "Exception/Exception.h"

namespace DataStLib
{
template <typename T>
class DuaLinkList : public List<T>
{
protected:
	
#pragma pack(4)
	struct Node : public Object		//�̳�object��ԭ������ΪҪʹ��Node��New����
	{
		T value;
		Node* next;
		Node* pre;
    };
    //mutable Node m_header;		//mutable�ؼ���ͻ��const�����ƣ���mutable���εı���������Զ���ڿɱ��״̬����ʹ��һ��const������
    mutable struct : public Object   //����дΪ�˷�ֹTΪ������ʱ���ù��캯�����ⲿ��Ĺ��캯�����ܻ�������⣩����T value��
    {
        char reserve[sizeof(T)];    //Ϊ��ռ�ڴ棺����ҲҪ�̳�Object��ȷ��ͷ�ڵ�������ڵ���ڴ�ռ�һ�£���ֹ��������ͷ�ڵ���������ʱ�����ڴ治һ�£����¸�ֵ����BUG��
        Node* next;
        Node* pre;
    }m_header;		//mutable�ؼ���ͻ��const�����ƣ���mutable���εı���������Զ���ڿɱ��״̬����ʹ��һ��const������

	int m_length;

	//�α����
	int m_step;		
	Node* m_current;
	
#pragma pack()

    Node* position(int i)const  //��λ�ڵ�
	{
        Node* ret = reinterpret_cast<Node*> (&m_header);
		for(int n=0; n<i; n++)
		{
			ret = ret->next;
		}
		return ret;
	}
	virtual Node* Creat()
    {
		return new Node();
	}
    virtual void destroy(Node* p)
	{
		delete p;
	}
public:
	DuaLinkList()
	{
        m_header.next = NULL;
        m_header.pre = NULL;
		m_length = 0;
		m_step = 1;
        m_current = NULL;
	}
	bool insert(const T& e)
	{
		return insert(m_length, e);
	}
	bool insert(int i, const T& e)
	{
		bool ret = ((i>=0) && (i<=m_length));
		if( ret )
		{
			Node* newnode = Creat();
			if(newnode != NULL)
			{
				Node* current = position(i);
                Node* next = current->next;

				newnode->value = e;
                newnode->next = next;
                current->next = newnode;
				if(current != reinterpret_cast<Node*>(&m_header))   //����㲻��ͷ�ڵ�
                {
                    newnode->pre = current;
                }
                else
                {
                    newnode->pre = NULL;
                }
                if(next != NULL)       //����㲻��β���
                {
                    next->pre = newnode;
                }

				m_length++;
			}
			else
			{
                THROW_EXCEPTION(NoEnoughMemoryException, "NO memory in Node* newnode = new Node()");
			}
		}
		return ret;
	}
    bool remove(int i)
	{
		bool ret = ((i>=0) && (i<m_length));
		if( ret )
		{
			Node* current = position(i);
			Node* toDel = current->next;
            Node* next = toDel->next;
            if(m_current == toDel)      //�ж��α����ڽڵ��ǲ���Ҫɾ���Ľڵ�
			{
                m_current = next;
			}
			
            current->next = next;

            if(next != NULL)    //�ж�ɾ���ڵ㲻��β���
            {
                next->pre = toDel->pre;
            }
			m_length--;
			destroy(toDel);
		}
		return ret;
	}
    bool set(int i, const T& e)
    {
		bool ret = ((i>=0) && (i<m_length));
		if( ret )
		{
			Node* current = position(i);
			current->next->value = e;
		}
		return ret;
	}
	virtual T get(int i)const
    {
		T ret;
		if(get(i, ret))
		{
            return ret;
		}
		else
		{
            THROW_EXCEPTION(IndexOutOfBoundsException, "out of at T get(int i)const");
		}
	}
	bool get(int i, T& e)const
    {
		bool ret = ((i>=0) && (i<m_length));
		if( ret )
		{
            Node* current = position(i);
            e = current->next->value;
		}
		return ret;
    }
	virtual int find(const T& e)const
    {
		int ret = -1;
        int n=0;
		Node* node = m_header.next;
        while(node)
        {
            if(node->value == e)
			{
                ret = n;
                break;
			}
            else
            {
                node = node->next;
                n++;
            }
		}
        return ret;
    }
    int length() const
    {
		return m_length;
	}
    void clear()
    {
        while(m_length>0)
        {
            remove(0);
        }
	}
    virtual bool move(int i, int step = 1)      //���α궨λ��Ŀ��λ��
    {
        bool ret = (i>=0) && (i<m_length) && (step>0);
        if( ret )
        {
            m_current = position(i)->next;
            m_step = step;
        }
        return ret;
	}
    virtual bool end()      //�α��Ƿ񵽴�β�����Ƿ�Ϊ�գ�
    {
        return (m_current == NULL);
    }
    virtual T current()     //��ȡ�α���ָ�������Ԫ��
    {
        if( !end() )
        {
            return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"No val at current position in  T current()");
        }
    }
    virtual bool next()     //�ƶ��α�
    {
        int i=0;
        while((i<m_step) && !end())
        {
            m_current = m_current->next;
            i++;
        }
        return (i == m_step);
    }
    virtual bool pre()
    {
        int i=0;
        while((i<m_step) && !end())
        {
            m_current = m_current->pre;
            i++;
        }
        return (i == m_step);
    }

    ~DuaLinkList()
    {
		clear();
	}
};
}


#endif // DUALINKLIST

