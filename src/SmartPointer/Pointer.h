#ifndef POINTER_H
#define POINTER_H

#include "Object.h"

namespace DataStLib {
    template<typename T>
    class Pointer : public Object {
    public:
        Pointer(T *p = NULL) {
            m_pointer = p;
        }

        T *operator->() {
            return m_pointer;
        }

        T &operator*() {
            return *m_pointer;
        }

        const T *operator->() const {
            return m_pointer;
        }

        const T &operator*() const {
            return *m_pointer;
        }

        T *get() const {
            return m_pointer;
        }

        bool isNULL() const {
            return (m_pointer == NULL);
        }

    protected:
        T *m_pointer;

    };
}


#endif // POINTER_H

