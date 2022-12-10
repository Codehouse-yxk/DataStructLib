//
// Created by 20218 on 2022/12/8.
//

#ifndef DUALLINKQUEUE_H
#define DUALLINKQUEUE_H

#include "LinkQueue.h"

namespace DataStLib {
    template<typename T>
    class DualLinkQueue : public LinkQueue<T> {
    private:
        typedef typename LinkQueue<T>::Node Node;
    public:
        void add_front(const T &e) {
            Node *node = new Node();

            if (node != NULL) {
                node->value = e;
                list_add(&node->head, &this->m_header);
                this->m_length++;
            } else {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to new node...");
            }
        }

        void remove_back() {
            if (this->m_length > 0) {
                list_head *toDel = this->m_header.prev;
                list_del(toDel);
                this->m_length--;
                list_entry(toDel, Node, head);
            } else {
                THROW_EXCEPTION(InvalidOperationException, "The DualQueue no element...");
            }
        }

        T back() const {
            if (this->m_length > 0) {
                return list_entry(this->m_header.prev, Node, head)->value;
            } else {
                THROW_EXCEPTION(InvalidOperationException, " The DualQueue no element... ");
            }
        }
    };
}

#endif //DUALLINKQUEUE_H
