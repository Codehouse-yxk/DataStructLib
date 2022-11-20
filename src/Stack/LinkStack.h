#ifndef LINKSTACK
#define LINKSTACK

#include "Stack.h"
#include "linklist.h"
namespace DataStLib
{
template <typename T>
class LinkStack : public Stack<T>
{
protected:
    LinkList<T> m_list;
public:
    void push(const T& e)       //O(1)
    {
        m_list.insert(0,e);
    }

    void pop()          //O(1)
    {

        if(m_list.length() > 0)
        {
            m_list.remove(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"No element in current stack...");
        }
    }
    T top() const        //O(1)
    {

        if(m_list.length() > 0)
        {
            return m_list.get(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"No element in current stack...");
        }
    }
    void clear()        //O(n)
    {
        m_list.clear();
    }
    int size() const        //O(1)
    {
        return m_list.length();
    }
};

}

#endif // LINKSTACK

