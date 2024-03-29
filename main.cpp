#include "test.h"

using namespace std;
using namespace DataStLib;

/*
    栈实现队列
*/

template<typename T>
class StacktoQueue : public Queue<T> {
protected:
    mutable LinkStack<T> m_stack_in;
    mutable LinkStack<T> m_stack_out;

    void move() const // O(n)    //const函数中只能调用const函数
    {
        if (m_stack_out.size() == 0) {
            while (m_stack_in.size() > 0) {
                m_stack_out.push(m_stack_in.top());
                m_stack_in.pop();
            }
        }
    }

public:
    StacktoQueue() // O(1)
    {
    }

    void add(const T &e) // O(1)
    {
        m_stack_in.push(e);
    }

    void remove() // O(n)
    {
        move();
        if (m_stack_out.size() > 0) {
            m_stack_out.pop();
        } else {
            THROW_EXCEPTION(InvalidOperationException, " The StacktoQueue no element... ");
        }
    }

    T front() const // O(n)
    {
        move();

        if (m_stack_out.size() > 0) {
            return m_stack_out.top();
        } else {
            THROW_EXCEPTION(InvalidOperationException, " The StacktoQueue no element... ");
        }
    }

    void clear() // O(n)
    {
        m_stack_in.clear();
        m_stack_out.clear();
    }

    int length() const // O(1)
    {
        return (m_stack_in.size() + m_stack_out.size());
    }

    ~StacktoQueue() // O(1)
    {
        clear();
    }
};

/*
    使用队列实现栈
*/

template<typename T>
class QueuetoStack : public Stack<T> {
protected:
    LinkQueue<T> m_queue_1;
    LinkQueue<T> m_queue_2;
    LinkQueue<T> *m_pIn;
    LinkQueue<T> *m_pOut;

    void move() const //将进队列中的元素转移到出队列      //O(n)
    {
        int n = m_pIn->length() - 1;
        for (int i = 0; i < n; i++) {
            m_pOut->add(m_pIn->front());
            m_pIn->remove();
        }
    }

    void swap() //交换进出队列角色     //O(1)
    {
        LinkQueue<T> *temp = NULL;

        temp = m_pIn;
        m_pIn = m_pOut;
        m_pOut = temp;
    }

public:
    QueuetoStack() // O(1)
    {
        m_pIn = &m_queue_1;
        m_pOut = &m_queue_2;
    }

    void push(const T &e) // O(1)
    {
        m_pIn->add(e);
    }

    void pop() // O(n)
    {
        if (m_pIn->length() > 0) {
            move();
            m_pIn->remove();
            swap();
        } else {
            THROW_EXCEPTION(InvalidOperationException, " The QueuetoStack no element... ");
        }
    }

    T top() const // O(n)
    {
        if (m_pIn->length() > 0) {
            move();
            return m_pIn->front();
        } else {
            THROW_EXCEPTION(InvalidOperationException, " The QueuetoStack no element... ");
        }
    }

    void clear() // O(n)
    {
        m_pIn->clear();
        m_pOut->clear();
    }

    int size() const // O(1)
    {
        return (m_pIn->length() + m_pOut->length());
    }

    ~QueuetoStack() {
    }
};

int main() {

    try {
//        Test::RangeArrayTest();
        Test::DualLinkQueueTest();
//        Test::BTreeTest();
//        Test::MatrixGraphTest();
//        Test::ListGraphTest();
//        Test::MatrixGraphBFSTest();
//        Test::ListGraphBFSTest();
        Test::MatrixGraphDFSTest();
        Test::ListGraphDFSTest();
        Test::MatrixGraphDFSByRecursiveTest();
        Test::ListGraphDFSByRecursiveTest();
    } catch (Exception &e) {
        cout << "catch a exception info: " << e.message() << " at " << e.location() << endl;
    }

    return 0;
}
