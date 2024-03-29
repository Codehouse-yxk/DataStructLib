#ifndef _LINKQUEUE_
#define _LINKQUEUE_

/*
    链式队列
*/

#include "Queue.h"
#include "Exception.h"
#include "StaticArray.h"
#include "LinuxList.h"

namespace DataStLib {
    template<typename T>
    class LinkQueue : public Queue<T> {
    protected:
        struct Node : public Object {
            list_head head;
            T value;
        };
        list_head m_header;
        int m_length;
    public:
        LinkQueue() {    //O(1)
            m_length = 0;
            INIT_LIST_HEAD(&m_header);
        }

        void add_back(const T &e) {       //O(1)
            Node *node = new Node();

            if (node != NULL) {
                node->value = e;
                list_add_tail(&node->head, &m_header);
                m_length++;
            } else {
                THROW_EXCEPTION(InvalidOperationException, " The StaticQueue no element... ");
            }
        }

        void remove_front() {      //O(1)
            if (m_length > 0) {
                list_head *toDel = m_header.next;

                list_del(toDel);

                m_length--;

                delete list_entry(toDel, Node, head);
            } else {
                THROW_EXCEPTION(InvalidOperationException, " The StaticQueue no element... ");
            }
        }

        T front() const {     //O(1)
            if (m_length > 0) {
                return list_entry(m_header.next, Node, head)->value;
            } else {
                THROW_EXCEPTION(InvalidOperationException, " The StaticQueue no element... ");
            }
        }

        void clear() {    //O(n)
            while (m_length > 0) {
                remove_front();
            }
        }

        int length() const {       //O(1)
            return m_length;
        }

        ~LinkQueue() {   //O(1)
            clear();
        }
    };
}


#endif // _LINKQUEUE_

