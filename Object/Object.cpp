#include "Object.h"
#include <iostream>
#include <cstdlib>

namespace DataStLib
{

void* Object::operator new(unsigned int size) throw()		//new�����ڴ�ʧ��ʱ��ȷ���������׳��쳣�����Ƿ���NULL
{
    //cout << "operator new(unsigned int size)" << size << endl;
    return malloc(size);
}

void Object::operator delete(void* p)
{
    //cout << "operator delete(void* p)" << endl;
    free (p);
}

void* Object::operator new[](unsigned int size) throw()		//new�����ڴ�ʧ��ʱ��ȷ���������׳��쳣�����Ƿ���NULL
{
    //cout << "operator new[](unsigned int size)" << endl;
    return malloc(size);
}

void Object::operator delete[](void* p)
{
    //cout << "operator delete[](void* p)" << endl;
    free (p);
}

bool Object::operator ==(const Object& obj)		//Ĭ��ͨ����ַ���бȽ�
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
