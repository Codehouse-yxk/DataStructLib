#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"

namespace DataStLib {
    template<typename T>
    class DynamicList : public SeqList<T> {
    protected:
        int m_capacity;        //顺序存储空间的大小
    public:
        DynamicList(int capacity) {
            this->m_array = new T[capacity];
            if (this->m_array != NULL) {
                this->m_length = 0;
                this->m_capacity = capacity;
            } else {
                THROW_EXCEPTION(NoEnoughMemoryException, "In DynamicList(int capacity), the memory is applied failed");
            }
        }

        int capacity() const {
            return m_capacity;
        }

        void resize(int capacity) {     //重新设置顺序存储空间的大小
            if (capacity < 0) {
                THROW_EXCEPTION(InvalidParameterException, "error in void resize(int capacity)");
                return;
            }
            if (m_capacity != capacity) {
                T *array = new T[capacity];        //目的：为了下面for循环复制操作，保证内存中的数据不变。
                if (array != NULL) {
                    int length = ((this->m_length < capacity) ? this->m_length : capacity);
                    for (int i = 0; i < length; i++) {
                        array[i] = this->m_array[i];    //猜想情况：array的类型T是泛指类型，若对=进行了重载，此处=操作可能会发生异常，
                        //但是此时并没有修改线性表，说明此时的线性表依旧是合法可用的。
                    }
                    T *temp = this->m_array;    //若不使用临时变量：直接使用delete[] this->m_array会调用析构函数，而如果此时析构函数由于意外抛出异常出现异常，
                    //函数从此处就会返回，导致下面的赋值无法执行。resize函数异常返回后，无法保证此线性表安全可用，说明此函数不安全。

                    this->m_array = array;
                    this->m_length = length;
                    this->m_capacity = capacity;
                    delete[] temp;                //猜想情况：即时此处异常返回，但是此时已经保证此线性表正常可用。
                } else {
                    THROW_EXCEPTION(NoEnoughMemoryException, "Exception In void DynamicList::resize(int capacity)");
                }
            }

        }

        ~DynamicList() {
            delete[] this->m_array;
        }
    };
}


#endif // DYNAMICLIST_H

