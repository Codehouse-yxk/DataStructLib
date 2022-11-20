#include "Object.h"
#include <iostream>
#include <cstdlib>

namespace DataStLib
{

void* Object::operator new(size_t size) throw()		//new申请内存失败时，确保函数不抛出异常，而是返回NULL
{
    //cout << "operator new(unsigned int size)" << size << endl;
    return malloc(size);
}

void Object::operator delete(void* p)
{
    //cout << "operator delete(void* p)" << endl;
    free (p);
}

void* Object::operator new[](size_t size) throw()		//new申请内存失败时，确保函数不抛出异常，而是返回NULL
{
    //cout << "operator new[](unsigned int size)" << endl;
    return malloc(size);
}

void Object::operator delete[](void* p)
{
    //cout << "operator delete[](void* p)" << endl;
    free (p);
}

bool Object::operator ==(const Object& obj)		//默认通过地址进行比较
{
	//cout << "operator ==" << endl;
    return (this == &obj);
}

bool Object::operator !=(const Object& obj)
{
	//cout << "operator !=" << endl;
    return (this != &obj);
}


Object::~Object()
{

}

}
