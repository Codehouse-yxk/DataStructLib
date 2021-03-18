#ifndef GTREENODE_H
#define GTREENODE_H

#include "TreeNode.h"
#include "List/linklist.h"

namespace DataStLib
{
template<typename T>
class GTreeNode : public TreeNode<T>
{

public:
    LinkList<GTreeNode<T>*> child;  //ÿ��������и�������Ÿ��ڵ㼰�ӽڵ��ַ

    static GTreeNode<T>* NewNode()  //����ģʽ�����ⲿ����ʹ�øú�������node
    {
        GTreeNode<T>* ret = new GTreeNode<T>();		//����TreeNode��new����Ϊprotect�����������ⲿ������new�½ڵ�
        if(ret != NULL)
        {
            ret->m_flag = true;		//������ǿռ�Ϊ�ѿռ䣬����delete�ж�
        }
        return ret;
    }

    ~GTreeNode()
    {
        
    }
};
}

#endif // GTREENODE_H

