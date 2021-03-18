#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"
#include "SmartPointer/SharedPointer.h"

namespace DataStLib
{
template <typename T>
class Tree : public Object
{
protected:
    TreeNode<T>* m_root;    //根节点

    Tree(const Tree<T>&);         //将拷贝构造和复制设置为保护，禁止拷贝操作
    Tree<T>& operator =(const Tree<T>&);
public:
    Tree(){ m_root = NULL; }
    virtual bool insert(TreeNode<T>* node) = 0;
    virtual bool insert(const T& value, TreeNode<T>* parrent) = 0;
    virtual SharedPointer< Tree<T> > remove(const T& value) = 0;
    virtual SharedPointer< Tree<T> > remove(TreeNode<T>* Node) = 0;
    virtual TreeNode<T>* find(const T& value)const = 0;
    virtual TreeNode<T>* find(TreeNode<T>* node) = 0;
    virtual TreeNode<T>* root() const = 0;  //访问树的根节点
    virtual int degree()const = 0;          //树的度
    virtual int count()const = 0;           //树的结点树
    virtual int height()const = 0;          //树的高度
    virtual void clear() = 0;               //清空树的结点

    virtual bool begin() = 0;
    virtual bool end() = 0;
    virtual bool next() = 0;
    virtual T current() = 0;
};
}

#endif // TREE_H

