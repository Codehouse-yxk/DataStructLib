#ifndef GTREE_H
#define GTREE_H

#include "Exception.h"
#include "GTreeNode.h"
#include "LinkQueue.h"
#include "Tree.h"

namespace DataStLib {
    template<typename T>
    class GTree : public Tree<T> {
    protected:
        LinkQueue<GTreeNode<T> *> m_queue;

        GTreeNode<T> *find(GTreeNode<T> *node, const T &value) const {
            GTreeNode<T> *ret = NULL;
            if (node != NULL) {
                if (node->value == value) {
                    ret = node;
                } else {
                    for (node->child.move(0); (!node->child.end()) && (ret == NULL); node->child.next()) { //遍历每一颗子树
                        ret = find(node->child.current(), value);                                          //在下一个子节点中查找值为value的成员
                    }
                }
            }
            return ret;
        }

        GTreeNode<T> *find(GTreeNode<T> *node, GTreeNode<T> *obj) const {
            GTreeNode<T> *ret = NULL;

            if (node == obj) {
                ret = node;
            } else {
                if (node != NULL) {
                    for (node->child.move(0); (!node->child.end()) && (ret == NULL); node->child.next()) { //遍历每一颗子树
                        ret = find(node->child.current(), obj);                                            //在下一个子节点中查找obj结点
                    }
                }
            }
            return ret;
        }

        void remove(GTreeNode<T> *node, GTree<T> *&ret) {
            ret = new GTree<T>();

            if (ret == NULL) {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree");
            } else {
                if (root() == node) {
                    this->m_root = NULL;
                } else { //完善处理父节点和子节点的关系
                    LinkList<GTreeNode<T> *> &child = (dynamic_cast<GTreeNode<T> *>(node->parent))->child;

                    child.remove(child.find(node));

                    node->parent = NULL;
                }
                ret->m_root = node;
            }
        }

        int count(GTreeNode<T> *node) const {
            int ret = 0;
            if (node != NULL) {
                ret = 1;
                for (node->child.move(0); !node->child.end(); node->child.next()) {
                    ret += count(node->child.current());
                }
            }
            return ret;
        }

        int height(GTreeNode<T> *node) const {
            int ret = 0;
            if (node != NULL) {
                for (node->child.move(0); !node->child.end(); node->child.next()) {
                    int h = height(node->child.current());

                    if (ret < h) {
                        ret = h;
                    }
                }
                ret += 1; //加上根节点
            }
            return ret;
        }

        int degree(GTreeNode<T> *node) const {
            int ret = 0;
            if (node != NULL) {
                ret = node->child.length();
                for (node->child.move(0); !node->child.end(); node->child.next()) {
                    int l = degree(node->child.current());

                    if (ret < l) {
                        ret = l;
                    }
                }
            }
            return ret;
        }

    public:
        bool insert(TreeNode<T> *node) {
            bool ret = true;
            if (node != NULL) {
                if (this->m_root == NULL) //若为空树，那么插入的新节点作为根节点
                {
                    node->parent = NULL;
                    this->m_root = node;
                } else {
                    GTreeNode<T> *pn = find(node->parent);
                    if (pn != NULL) {
                        GTreeNode<T> *n = dynamic_cast<GTreeNode<T> *>(node);
                        if (pn->child.find(n) < 0) { //已经确定了目标结点的父节点，所以直接看父节点的子节点是否已经存在目标结点，若存在，则不需要插入
                            //小于0，说明目前树中没有目标结点。待插入
                            pn->child.insert(n);
                        }
                    } else {
                        THROW_EXCEPTION(InvalidParameterException, "paraments is error in bool insert(TreeNode<T>* node)");
                    }
                }
            } else {
                THROW_EXCEPTION(InvalidParameterException, "paraments is error in bool insert(TreeNode<T>* node)");
            }

            return ret;
        }

        bool insert(const T &value, TreeNode<T> *parrent) {//在给定的父节点插入元素
            bool ret = true;

            GTreeNode<T> *newNode = GTreeNode<T>::NewNode();

            if (newNode != NULL) {
                newNode->value = value;
                newNode->parent = parrent;
                insert(dynamic_cast<TreeNode<T> *>(newNode));
            } else {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree node...");
            }

            return ret;
        }

        SharedPointer<Tree<T>> remove(const T &value) {
            GTree<T> *ret = NULL;
            GTreeNode<T> *node = find(value);

            if (node == NULL) {
                THROW_EXCEPTION(InvalidParameterException, "Can not find the node via parameter value...");
            } else {
                remove(node, ret);
                m_queue.clear();
            }
            return ret;
        }

        SharedPointer<Tree<T>> remove(TreeNode<T> *node) {
            GTree<T> *ret = NULL;
            node = find(node);

            if (node == NULL) {
                THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid...");
            } else {
                remove(dynamic_cast<GTreeNode<T> *>(node), ret);
                m_queue.clear(); //删除结点为什么需要将遍历时的队列清空
            }
            return ret;
        }

        TreeNode<T> *find(const T &value) const   //查找操作最终返回目标数据地址
        {
            return find(root(), value);
        }

        TreeNode<T> *find(TreeNode<T> *node)   //查找操作最终返回目标结点地址
        {
            return find(root(), dynamic_cast<GTreeNode<T> *>(node));
        }

        void free(GTreeNode<T> *node) {
            if (node != NULL) {
                for (node->child.move(0); !node->child.end(); node->child.next()) {
                    free(node->child.current());
                }
                if (node->flag() == true) {
                    delete node;
                }
            }
        }

        GTreeNode<T> *root() const {
            return (dynamic_cast<GTreeNode<T> *>(this->m_root));
        }

        int degree() const {
            return degree(root());
        }

        int count() const {
            return count(root());
        }

        int height() const {
            return height(root());
        }

        void clear() { //销毁树，但没有释放每个结点
            free(root());
            this->m_root = NULL;

            m_queue.clear();
        }

        /*============ 层次遍历（根节点开始，每行从左到右遍历），使用游标思想 ==========*/
        bool begin() {
            bool ret = (root() != NULL);

            if (ret) {
                m_queue.clear(); //先清空，防止上一次的遍历残留
                m_queue.add(root());
            }
            return ret;
        }

        bool end() {//判断遍历是否结束
            return (m_queue.length() == 0); //队列为空表示遍历完毕
        }

        bool next() {
            bool ret = (m_queue.length() > 0); //有元素才移动

            if (ret) {
                GTreeNode<T> *node = m_queue.front(); //指向队列的首节点

                m_queue.remove(); //将首节点删除,移动了游标

                for (node->child.move(0); !node->child.end(); node->child.next()) //将删除结点的孩子结点全部推入队列
                {
                    m_queue.add(node->child.current()); //孩子结点中的链表的每个元素的类型为GTreeNode<T>*，所以其value值为一个指向GTreeNode<T>的指针
                }
            }
            return ret;
        }

        T current() {
            if (!end()) {
                return m_queue.front()->value;
            } else {
                THROW_EXCEPTION(InvalidOperationException, "NO value at current position ...");
            }
        }

        ~GTree() {
            clear();
        }
    };
}

#endif // GTREE_H
