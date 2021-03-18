#ifndef _STATICQUEUE_
#define _STATICQUEUE_

#include "Queue.h"
#include "Exception/Exception.h"
#include "Array/StaticArray.h"

/*
    静态队列
*/

namespace DataStLib
{
template <typename T, int N>
class StaticQueue : public Queue<T>
{
protected:
    //StaticArray<T,N> m_space;   //原生数组：T m_space[N]
    T m_space[N];
    int m_front;
    int m_real;
    int m_length;
public:
    StaticQueue()       //O(1)
    {
        m_front = 0;
        m_real = 0;
        m_length = 0;
    }
    int capacity()const     //O(1)
    {
        return N;
    }
    void add(const T& e)         //O(1)
    {
        if( m_length <= N && N > 0)
        {
            m_space[m_real] = e;
            m_real = (m_real+1)%N;
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException," The StaticQueue no enough memory... ");
        }

    }
    void remove()        //O(1)
    {
        if( m_length > 0 )
        {
            m_front = (m_front+1)%N;
            m_length--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException," The StaticQueue no element... ");
        }
    }
    bool isEmerty()      //O(1)
    {
        return ( (m_length == 0) && (m_front == m_real));
    }

    bool isFull()        //O(1)
    {
        return ( (m_length == N) && (m_front == m_real));
    }

    T front()const       //O(1)
    {
        if( m_length >0 )
        {
            return m_space[m_front];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException," The StaticQueue no element... ");
        }
    }
    void clear()         //O(1)
    {
        m_length = 0;
        m_front = 0;
        m_real = 0;
    }
    int length()const        //O(1)
    {
        return m_length;
    }

};
}

#endif // _STATICQUEUE_

