#ifndef TREENODE_H
#define TREENODE_H

#include "Object/Object.h"

namespace DataStLib
{
template <typename T>
class TreeNode : public Object
{
protected:
    bool m_flag;

    TreeNode(const TreeNode<T>&);         //����������͸�ֵ����Ϊ��������ֹ��������
    TreeNode<T>& operator = (const TreeNode<T>&);

    void* operator new(unsigned int size)throw()
    {
        return Object::operator new(size);
    }
public:
    T value;                //����е�����
    TreeNode<T>* parent;    //ָ�򸸽ڵ��ָ��
    TreeNode()
    {
        m_flag = false;
        parent = NULL;
    }
    bool flag()
    {
        return m_flag;
    }

    virtual ~TreeNode() = 0;
};
template <typename T>
TreeNode<T> :: ~TreeNode()
{

}
}

#endif // TREENODE_H

