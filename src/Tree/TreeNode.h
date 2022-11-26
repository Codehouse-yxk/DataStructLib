#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace DataStLib {
    template<typename T>
    class TreeNode : public Object {
    protected:
        bool m_flag;

        TreeNode(const TreeNode<T> &) = default; //将拷贝构造和赋值设置为保护，禁止拷贝操作
        TreeNode<T> &operator=(const TreeNode<T> &) = default;

        void *operator new(size_t size) noexcept {
            return Object::operator new(size);
        }

    public:
        TreeNode() {
            m_flag = false;
            parent = NULL;
        }

        bool flag() { return m_flag; }

        virtual ~TreeNode() = 0;

    public:
        T value;             //结点中的数据
        TreeNode<T> *parent; //指向父节点的指针
    };

    template<typename T>
    TreeNode<T>::~TreeNode() {}
}

#endif // TREENODE_H
