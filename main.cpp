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

/*
    ջʵ�ֶ���
*/

template <typename T>
class StacktoQueue : public Queue<T>
{
protected:
    mutable LinkStack<T> m_stack_in;
    mutable LinkStack<T> m_stack_out;
    void move()const    //O(n)    //const������ֻ�ܵ���const����
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
    ʹ�ö���ʵ��ջ
*/

template <typename T>
class QueuetoStack : public Stack<T>
{
protected:
    LinkQueue<T> m_queue_1;
    LinkQueue<T> m_queue_2;
    LinkQueue<T>* m_pIn;
    LinkQueue<T>* m_pOut;

    void move()const //���������е�Ԫ��ת�Ƶ�������      //O(n)
    {
        int n = m_pIn->length()-1;
        for(int i=0; i<n; i++)
        {
            m_pOut->add(m_pIn->front());
            m_pIn->remove();
        }
    }
    void swap() //�����������н�ɫ     //O(1)
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


int main()
{
    /*
                A
            B  |   C
            E   F|   M   N
        X   Y
        ǰ��ABEXYFCMN
        ����XEYBFAMCN
        ������XYEFBMNCA
    */
    BTree<char> btree;
    BTreeNode<char>* bn = NULL;     //���ڵ�

    btree.insert('A',NULL);

    bn = btree.find('A');
    btree.insert('B', bn);
    btree.insert('C', bn);

    bn = btree.find('B');
    btree.insert('E', bn);
    btree.insert('F', bn);

    bn = btree.find('C');
    btree.insert('M', bn);
    btree.insert('N', bn);

    bn = btree.find('E');
    btree.insert('X', bn);
    btree.insert('Y', bn);


    SharedPointer< Array<char> > tr = btree.traversal(LeverOrder);

    cout << "===============��α���================" << endl;
    for(int i=0; i<(*tr).length(); i++)
    {
        cout << (*tr)[i];
    }
    cout << endl;

    return 0;
}

