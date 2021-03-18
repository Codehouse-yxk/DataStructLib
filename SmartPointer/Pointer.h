#ifndef POINTER_H
#define POINTER_H

#include "Object/Object.h"

namespace DataStLib
{
template <typename T>
class Pointer : public Object
{
protected:
    T* m_pointer;
public:
    Pointer(T* p = NULL)
    {
        m_pointer = p;
    }
    T* operator ->()
    {
        return m_pointer;
    }
    T& operator *()
    {
        return *m_pointer;
    }

    const T* operator ->()const
    {
        return m_pointer;
    }
    const T& operator *()const
    {
        return *m_pointer;
    }


    T* get()const
    {
        return m_pointer;
    }
    bool isNULL()const
    {
        return (m_pointer == NULL);
    }
};
}


#endif // POINTER_H

