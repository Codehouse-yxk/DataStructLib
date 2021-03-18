#ifndef DUACIRCLELINKLIST
#define DUACIRCLELINKLIST

#include "DuaLinkList.h"
#include "LinuxList.h"
#include "Exception/Exception.h"

namespace DataStLib
{
template <typename T>
class DuaCircleLinkList : public DuaLinkList<T>
{
protected:
    struct Node : public Object
    {
      list_head head;
      T value;
    };
    list_head m_header;
    list_head* m_current;

    list_head* position(int i)const
    {
        list_head* ret = const_cast<list_head*>(&m_header);	//在const函数中不能直接取用非const成员地址

        for(int p=0; p<i; p++)
        {
            ret = ret->next;
        }
        return ret;
    }

    int mod(int i)const		//O(1)
    {
        return (this->m_length==0) ? 0 : (i % this->m_length);
    }

public:
    DuaCircleLinkList()
    {
        m_current = NULL;
        this->m_step = 1;
        this->m_length = 0;
        INIT_LIST_HEAD(&m_header);
    }
    bool insert(const T& e)			//O(n)
    {
        return insert(this->m_length,e);
    }
    bool insert(int i, const T & e)		//O(n)
    {
        bool ret = true;
        Node* node = new Node();
        i = i % (this->m_length + 1);	//O(1)

        if( node != NULL)
        {
            node->value = e;
            list_add_tail(&node->head,position(i)->next);
            this->m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No memory in DuaCircleLinkList()");
        }
        return ret;
    }
    bool remove(int i)		//O(n)
    {
        bool ret = true;
        i = mod(i);
        ret = ((i>=0) && (i<this->m_length));

        if(ret)
        {
            list_head* toDel = position(i)->next;
            if(m_current == toDel)
            {
                m_current = toDel->next;
            }
            list_del(toDel);
            this->m_length--;
            delete list_entry(toDel,Node,head);
        }
        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = true;
        i = mod(i);
        ret = ((i>=0) && (i<this->m_length));
        if( ret )
        {
            list_entry(position(i)->next,Node,head)->value = e;
        }
        return ret;
    }
    T get(int i)const
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
        bool ret = true;
        i = mod(i);
        ret = ((i>=0) && (i<this->m_length));
        if( ret )
        {
            e =list_entry(position(i)->next,Node,head)->value;
        }
        return ret;
    }
    int find(const T& e)const
    {
        int ret = -1;
        int i = 0;
        list_head* slider = NULL;

        list_for_each(slider,&m_header)
        {
            if(list_entry(slider,Node,head)->value == e)
            {
                ret = i;
                break;
            }
            i++;
        }
        return ret;
    }
    int length()const
    {
        return this->m_length;
    }
    void clear()		//O(n)
    {
        while( this->m_length > 0 )	//O(n)
        {
            remove(0);			   //O(1)
        }
    }

    bool move(int i, int step = 1)      	//将游标定位到目标位置
                                            //O(n)
    {
        bool ret = (step > 0);
        i = mod(i);
        ret = ret && (i>=0) && (i<this->m_length);
        if(ret)
        {
            m_current = position(i)->next;
            this->m_step = step;
        }
        return ret;
    }
    bool end()      //游标是否到达尾部（是否为空）
                    //O(1)
    {
        return ((m_current == NULL) || (this->m_length == 0 ));
    }
    T current()     //获取游标所指向的数据元素
    {
        if( !end() )
        {
            return list_entry(m_current,Node,head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"No val at current position in  T current()");
        }
    }
    bool next()     //移动游标
    {
        int i=0;
        while((i < this->m_step) && !end())
        {
            if(m_current != &m_header)  //Linux循环链表中，头节点也是链表中的一员，为了满足StLib的通用设计，此处需对头节点进行跳过处理。
            {
                m_current = m_current->next;
                i++;
            }
            else
            {
                m_current = m_current->next;
            }
        }
        if(m_current == &m_header)  //如果停在头节点，跳过
        {
            m_current = m_current->next;
        }
        return (i == this->m_step);
    }
    bool pre()     //移动游标
    {
        int i=0;
        while((i<this->m_step) && !end())
        {
            if(m_current != &m_header)
            {
                m_current = m_current->prev;
                i++;
            }
            else
            {
                m_current = m_current->prev;
            }
        }
        if(m_current == &m_header)
        {
            m_current = m_current->prev;
        }
        return (i == this->m_step);
    }

    ~DuaCircleLinkList()		//O(n)
    {
        clear();
    }

};
}



#endif // DUACIRCLELINKLIST

