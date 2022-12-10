#ifndef _QUEUE_
#define _QUEUE_

/*
    队列的抽象父类
*/

#include "Object.h"

namespace DataStLib {
    template<typename T>
    class Queue : public Object {
    public:
        virtual void add_back(const T &e) = 0;

        virtual void remove_front() = 0;

        virtual T front() const = 0;

        virtual void clear() = 0;

        virtual int length() const = 0;
    };
}

#endif // _QUEUE_

