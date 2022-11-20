#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreeNode.h"
#include "linklist.h"

namespace DataStLib
{
template<typename T>
class GTreeNode : public TreeNode<T>
{

public:
    LinkList<GTreeNode<T>*> child;  //每个结点中有个链表，存放父节点及子节点地址

    static GTreeNode<T>* NewNode()  //工厂模式，在外部可以使用该函数创建node
    {
        GTreeNode<T>* ret = new GTreeNode<T>();		//父类TreeNode将new重载为protect，这样在类外部，不能new新节点
        if(ret != NULL)
        {
            ret->m_flag = true;		//用来标记空间为堆空间，进行delete判断
        }
        return ret;
    }

    ~GTreeNode()
    {
        
    }
};
}

#endif // GTREENODE_H

