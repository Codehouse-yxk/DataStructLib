#include <iostream>
#include "SmartPointer/SmartPointer.h"
#include "Exception/Exception.h"
#include "Object/Object.h"
#include "List/List.h"
#include "List/SeqList.h"
#include "List/StaticList.h"
#include "List/DynamicList.h"
#include "List/LinkList.h"
#include "Array/StaticArray.h"
#include "Array/DynamicArray.h"
#include "List/StaticLinkList.h"
#include "SmartPointer/SharedPointer.h"
#include "List/CircleList.h"
#include "List/DuaLinkList.h"
#include "List/DuaStaticLinkList.h"
#include "List/DuaCircleLinkList.h"
#include "List/LinuxList.h"
#include "Stack/StaticStack.h"
#include "Queue/StaticQueue.h"
#include "Queue/LinkQueue.h"
#include "Stack/LinkStack.h"
#include "String/String.h"
#include "Sort/Sort.h"
#include "Tree/GTreeNode.h"
#include "Tree/GTree.h"
#include "Tree/BTreeNode.h"
#include "Tree/BTree.h"
#include <cstring>

using namespace std;
using namespace DataStLib;

void josephus(int n, int s, int m)
{
	CircleList<int> cl;
	for(int i=1; i<=n; i++)
	{
		cl.insert(i);
	}
	cl.move(s-1, m-1);
	while( cl.length() > 0 )
	{
		cl.next();

		cout << cl.current() << endl;

        cl.remove(cl.find(cl.current()));
	}
}

/*
    栈实现队列(时间复杂度较高)
*/

template <typename T>
class StacktoQueue : public Queue<T>
{
protected:
    mutable LinkStack<T> m_stack_in;
    mutable LinkStack<T> m_stack_out;
    void move()const    //O(n)    //const函数中只能调用const函数
    {
        if( m_stack_out.size() == 0 )
        {
            while( m_stack_in.size() > 0 )
            {
                m_stack_out.push(m_stack_in.top());
                m_stack_in.pop();
            }
        }
    }
public:
    StacktoQueue()       //O(1)
    {

    }
    void add(const T& e)         //O(1)
    {
        m_stack_in.push(e);
    }
    void remove()        //O(n)
    {
        move();
        if( m_stack_out.size() > 0)
        {
            m_stack_out.pop();
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException," The StacktoQueue no element... ");
        }
    }
    T front()const       //O(n)
    {
        move();

        if( m_stack_out.size() > 0)
        {
            return m_stack_out.top();
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException," The StacktoQueue no element... ");
        }
    }
    void clear()         //O(n)
    {
        m_stack_in.clear();
        m_stack_out.clear();
    }
    int length()const        //O(1)
    {
        return ( m_stack_in.size()+m_stack_out.size() );
    }
    ~StacktoQueue()        //O(1)
    {
        clear();
    }
};


/*
    使用队列实现栈
*/

template <typename T>
class QueuetoStack : public Stack<T>
{
protected:
    LinkQueue<T> m_queue_1;
    LinkQueue<T> m_queue_2;
    LinkQueue<T>* m_pIn;
    LinkQueue<T>* m_pOut;

    void move()const //将进队列中的元素转移到出队列      //O(n)
    {
        int n = m_pIn->length()-1;
        for(int i=0; i<n; i++)
        {
            m_pOut->add(m_pIn->front());
            m_pIn->remove();
        }
    }
    void swap() //交换进出队列角色     //O(1)
    {
        LinkQueue<T>* temp = NULL;

        temp = m_pIn;
        m_pIn = m_pOut;
        m_pOut = temp;
    }
public:
    QueuetoStack()     //O(1)
    {
        m_pIn = &m_queue_1;
        m_pOut = &m_queue_2;
    }
    void push(const T& e)   //O(1)
    {
        m_pIn->add(e);
    }
    void pop()     //O(n)
    {
        if( m_pIn->length() > 0 )
        {
            move();
            m_pIn->remove();
            swap();
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException," The QueuetoStack no element... ");
        }
    }
    T top()const       //O(n)
    {
        if( m_pIn->length() > 0 )
        {
            move();
            return m_pIn->front();
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException," The QueuetoStack no element... ");
        }
    }
    void clear()       //O(n)
    {
        m_pIn->clear();
        m_pOut->clear();
    }
    int size()const     //O(1)
    {
        return ( m_pIn->length() + m_pOut->length() );
    }
    ~QueuetoStack()
    {

    }
};


class Test
{
public:
    Test()
    {
        cout << "Test()" << endl;
    }
    ~Test()
    {
        cout << "~Test()" << endl;
    }
};

int main()
{
    int arr[6] = {21,25,49,25,16,8};

    Sort::Shell(arr, 6);

    for(int i=0; i<6; i++)
        cout << arr[i] << endl;

    return 0;
}

