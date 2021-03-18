#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

namespace DataStLib
{
template<typename T, int N>
class StaticLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;	//由于父类Node类型中含有T型成员，所以不能在子类中直接使用Node定义对象，
    											//而要改为"typename LinkList<T>::Node xxx"。typename LinkList<T>::Node是类型
    struct SNode : public Node  //Node的子类，只是为了重载new操作符，以便在指定地址创建对象
    {
        void* operator new(unsigned int size, void* loc)
        {
            (void)size;     //C语言中暴力处理方式
            return loc;
        }
    };
    unsigned char m_space[N * sizeof(SNode)];
    int m_used[N];

    Node* Creat()
    {
        SNode* ret = NULL;
        for(int i=0; i<N; i++)		//遍历内存，找到可用空间
        {
            if( !m_used[i] )
            {
                ret = reinterpret_cast<SNode*>(m_space) + i;    //找到空闲内存
                ret = new(ret)SNode();	//在这片空间上调用构造函数（SNode类的构造函数），产生Node对象
                m_used[i] = 1;
                break;
            }
        }
        return ret;
    }
    void destroy(Node* pn)
    {
        SNode* space = reinterpret_cast<SNode*>(m_space);//进行指针运算，所以先强制转换
        SNode* psn = dynamic_cast<SNode*>(pn);
        for(int i=0; i<N; i++)
        {
            if(psn == space +i)
            {
                m_used[i] = 0;
                psn->~SNode();//由于指定了对象创建空间，所以需要显示的调用析构函数
				break;
            }
        }
    }
public:
    StaticLinkList()
    {
        for(int i=0; i<N; i++)  //标记每个内存空间可用
        {
            m_used[i] = 0;
        }
    }
    int capacity()
    {
        return N;
    }
    ~StaticLinkList()
    {
        this->clear();	//StaticLinkList构造函数中并没有申请新的资源，本可以不实现析构函数
        				//此处实现析构函数目的是用来调用子类实现的destroy，destroy在clear中被调用
        				//构造函数和析构函数中不会发生多态，所以父类中调用clear并不能正确释放资源
    }

};

}






#endif // STATICLINKLIST_H

