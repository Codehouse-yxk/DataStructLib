#ifndef LIST_H
#define LIST_H
#include "Object/Object.h"

namespace DataStLib
{
template <typename T>
class List : public Object
{
protected:
	List(const List&);			//为了禁止拷贝构造和赋值操作，此处声明为protected（容器不能复制，如果复制，两个指针指向同一个地址，会出现问题）
	List& operator= (const List&);
public:
	List(){}		//由于实现了拷贝构造函数，所以编译器不再生成默认构造函数，需要手工声明
    virtual bool insert(int i, const T& e) = 0;
    virtual bool remove(int i) = 0;
    virtual bool set(int i, const T& e) = 0;
    virtual bool get(int i, T& e)const = 0;
    virtual int find(const T& e)const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
};
}

#endif // LIST_H
