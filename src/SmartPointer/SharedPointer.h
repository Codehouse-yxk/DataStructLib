#ifndef SHAREDPOINTER
#define SHAREDPOINTER

#include "cstdlib"
#include "Pointer.h"
#include "Exception.h"

namespace DataStLib {
    template<typename T>
    class SharedPointer : public Pointer<T> {
    protected:
        int *m_ref;     //计数机制成员指针
        void assign(const SharedPointer<T> &obj) {
            this->m_ref = obj.m_ref;
            this->m_pointer = obj.m_pointer;

            if (this->m_ref) {
                (*this->m_ref)++;
            }
        }

    public:
        SharedPointer(T *p = NULL) : m_ref(NULL) {
            if (p) {
                this->m_ref = static_cast<int *>(std::malloc(sizeof(int)));
                if (this->m_ref) {
                    *(this->m_ref) = 1;
                    this->m_pointer = p;
                } else {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory in SharedPointer(T* p = NULL) : m_ref(NULL)");
                }
            }
        }

        SharedPointer(const SharedPointer<T> &obj) : Pointer<T>(NULL) {
            assign(obj);
        }

        SharedPointer<T> &operator=(const SharedPointer<T> &obj) {
            if (this != &obj) {
                clear();
                assign(obj);
            }
            return *this;
        }

        void clear() {
            T *toDel = this->m_pointer;
            int *ref = this->m_ref;
            this->m_pointer = NULL;
            this->m_ref = NULL;
            if (ref) {
                (*ref)--;
                if (*ref == 0) {
                    free(ref);
                    delete toDel;
                }
            }
        }

        const int getRef() const {   //获取当前指向同一块内存的指针数
            return *m_ref;
        }

        bool operator==(const SharedPointer<T> &obj) {
            return ((*this).m_pointer == obj.m_pointer);
        }

        bool operator!=(const SharedPointer<T> &obj) {
            return !(*this == obj);
        }

        ~SharedPointer() {
            clear();
        }
    };
}


#endif // SHAREDPOINTER

