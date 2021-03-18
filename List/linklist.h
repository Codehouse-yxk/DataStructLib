#ifndef LINKLIST
#define LINKLIST

#include "List.h"
#include "Exception/Exception.h"

namespace DataStLib
{
template <typename T>
class LinkList : public List<T>
{
protected:
	
#pragma pack(4)
	struct Node : public Object		//继承object的原因是因为要使用Node，New对象
	{
		T value;
		Node* next;
    };
    //mutable Node m_header;		//mutable关键字突破const的限制，被mutable修饰的变量，将永远处于可变的状态，即使在一个const函数中
    mutable struct : public Object   //这样写为了防止T为类类型时调用构造函数（外部类的构造函数可能会存在问题）——T value。
    {
        char reserve[sizeof(T)];    //为了占内存：并且也要继承Object，确保头节点和其他节点的内存空间一致，防止后续操作头节点和其他结点时由于内存不一致，导致赋值出现BUG。
        Node* next;
    }m_header;		//mutable关键字突破const的限制，被mutable修饰的变量，将永远处于可变的状态，即使在一个const函数中

	int m_length;

	//游标参数
	int m_step;		
	Node* m_current;
	
#pragma pack()

    Node* position(int i)const  //定位节点
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
	LinkList()
	{
        m_header.next = NULL;
		m_length = 0;
		m_step = 1;
        m_current = NULL;
		/*
		cout << "sizeof(Node)=" << sizeof(Node) << '\n'
             << "sizeof(m_header)=" << sizeof(m_header) << '\n'
             << "sizeof(T)="<< sizeof(T)<< endl;
		*/
	}
	bool insert(const T& e)		//在最后插入
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
				newnode->value = e;
				newnode->next = current->next;
				current->next = newnode;
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

			if(m_current == toDel)
			{
				m_current = toDel->next;
			}
			
			current->next = toDel->next;
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
        while(m_header.next)
        {
            Node* toDel = m_header.next;
            m_header.next = toDel->next;
            m_length--;
            destroy(toDel);
        }
		//m_length = 0;	//为了异常安全，使用m_length--;
    }
    virtual bool move(int i, int step = 1)      //将游标定位到目标位置
    {
        bool ret = (i>=0) && (i<m_length) && (step>0);
        if( ret )
        {
            m_current = position(i)->next;
            m_step = step;
        }
        return ret;
	}
    virtual bool end()      //游标是否到达尾部（是否为空）
    {
        return (m_current == NULL);
    }
    virtual T current()     //获取游标所指向的数据元素
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
    virtual bool next()     //移动游标
    {
        int i=0;
        while((i<m_step) && !end())
        {
            m_current = m_current->next;
            i++;
        }
        return (i == m_step);
    }

	~LinkList()
    {
		clear();
	}
};
}

#endif // LINKLIST

