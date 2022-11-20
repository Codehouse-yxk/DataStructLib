#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <cstdlib>

#include "Pointer.h"

namespace DataStLib
{
template <typename T>
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* p = NULL) : Pointer<T>(p)
    {
    }

    SmartPointer(const SmartPointer<T>& obj):Pointer<T>(NULL)
    {
        this->m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
    }

    SmartPointer<T>& operator= (const SmartPointer<T>& obj)
    {
        if(this != &obj)
        {
            T* p = this->m_pointer;
            this->m_pointer = obj.m_pointer;
            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
            delete p;
        }
        return *this;
    }
    ~SmartPointer()
    {
        delete this->m_pointer;
    }

};


class SmartPointTest
{
public:
    SmartPointTest()
    {
        std::cout << "SmartPointTest()" << std::endl;
    }
    ~SmartPointTest()
    {
        std::cout << "~SmartPointTest()" << std::endl;
    }
};

   void SmartPtrTest(void);
}

#endif // SMARTPOINTER_H

