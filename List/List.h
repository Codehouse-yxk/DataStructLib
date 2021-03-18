#ifndef LIST_H
#define LIST_H
#include "Object/Object.h"

namespace DataStLib
{
template <typename T>
class List : public Object
{
protected:
	List(const List&);			//Ϊ�˽�ֹ��������͸�ֵ�������˴�����Ϊprotected���������ܸ��ƣ�������ƣ�����ָ��ָ��ͬһ����ַ����������⣩
	List& operator= (const List&);
public:
	List(){}		//����ʵ���˿������캯�������Ա�������������Ĭ�Ϲ��캯������Ҫ�ֹ�����
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
