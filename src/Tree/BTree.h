#ifndef _BTREE_
#define _BTREE_

#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"
#include "DynamicArray.h"

namespace DataStLib
{
enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT
};
enum BTTraversal
{
    PreOrder,   //前序
    InOrder,    //中序
    PostOrder,  //后序
    LeverOrder  //层次遍历
};
template<typename T>
class BTree : public Tree<T>
{
protected:
    LinkQueue<BTreeNode<T>*> m_queue; 
    BTreeNode<T>* find(BTreeNode<T>* node, const T& value)const
    {
        BTreeNode<T>* ret = NULL;
        if( node != NULL )
        {
            if(node->value == value)
            {
                ret = node;
            }
            else
            {
                if(ret == NULL)
                {
                    ret = find(node->left, value);
                }
                if(ret == NULL)
                {
                    ret = find(node->right, value);
                }
            }
        }
        return ret;
    }
    BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T>* obj)const
    {
        BTreeNode<T>* ret = NULL;
        if( node != NULL )
        {
            if(node == obj)
            {
                ret = node;
            }
            else
            {
                if(ret == NULL)
                {
                    ret = find(node->left, obj);
                }
                if(ret == NULL)
                {
                    ret = find(node->right, obj);
                }
            }
        }
        return ret;
    }
    bool insert(BTreeNode<T>* n, BTreeNode<T>* np, BTNodePos pos)
    {
        bool ret = true;
        if(pos == ANY)
        {
            if(np->left == NULL)
            {
                np->left = n;
            }
            else if(np->right == NULL)
            {
                np->right = n;
            }
            else
            {
                ret = false;
            }           
        }
        else if(pos == LEFT)
        {
            if(np->left == NULL)
            {
                np->left = n;
            }
            else
            {
                ret = false;
            }
        }
        else if(pos == RIGHT)
        {
            if(np->right == NULL)
            {
                np->right = n;
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = false;
        }
        
        return ret;        
    }
    void remove(BTreeNode<T>* node, BTree<T>*& ret)
    {
        ret = new BTree<T>();

        if( ret == NULL )
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat new tree");
        }
        else
        {
            if( root() == node )    //如果是根节点，则直接将二叉树清空
            {
                this->m_root = NULL;
            }
            else        //完善处理父节点和子节点的关系
            {
                BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);

                if(node == parent->left)
                {
                    parent->left = NULL;
                }
                else if(node == parent->right)
                {
                    parent->right = NULL;
                }
                node->parent = NULL;
            }
            ret->m_root = node;
        }
        ret->m_root = node;     //作为子树返回
    }
    void free(BTreeNode<T>* node)
    {
        if(node != NULL)
        {
            free(node->left);
            free(node->right);

            if( node->flag() )  //真：表示结点在堆中申请
            {
                delete node;
            }
        }
    }
    int count(BTreeNode<T>* node)const
    {
        int ret = 0;
        if( node != NULL)
        {
            ret +=count(node->left) + count(node->right) + 1;
        }
        return ret;
    }
    int height(BTreeNode<T>* node)const			//树的高度
    {
        int ret = 0;
        if( node != NULL)
        {
            int l = height(node->left);
            int r = height(node->right);
            ret = ((l > r) ? l : r) + 1;
        }
        return ret;
    }
    int degree(BTreeNode<T>* node)const			//树的度
    {
        int ret = 0;
        if( node != NULL)
        {
            BTreeNode<T>* arrayTreeNode[] = {node->left, node->right};
            ret = (!!node->left + !!node->right);       //!!:将非零值转换为1或0

            for(int i=0; (i<sizeof(arrayTreeNode)/sizeof(BTreeNode<T>*)) && ret<2; i++)
            {
                int d = degree(arrayTreeNode[i]);
                if(ret < d)
                {
                    ret = d;
                }
            }
        }
        return ret;
    }

    void preOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue) //先序遍历
    {
        if(node != NULL)
        {
            queue.add(node);
            preOrderTraversal(node->left, queue);
            preOrderTraversal(node->right, queue);
        }
    }
    void inOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue) //中序遍历
    {
        if(node != NULL)
        {
            inOrderTraversal(node->left, queue);
            queue.add(node);
            inOrderTraversal(node->right, queue);
        }
    }
    void postOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue) //后序遍历
    {
        if(node != NULL)
        {
            postOrderTraversal(node->left, queue);
            postOrderTraversal(node->right, queue);
            queue.add(node);
        }
    }

    void levelOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)   //层次遍历，并将遍历结果保存在队列中
    {
        if(node != NULL)
        {
            LinkQueue<BTreeNode<T>*> tmp;

            tmp.add(node);

            while (tmp.length() > 0)
            {
                BTreeNode<T>* n = tmp.front();

                if(n->left != NULL)
                {
                    tmp.add(n->left);
                }
                if(n->right != NULL)
                {
                    tmp.add(n->right);
                }

                tmp.remove();

                queue.add(n);
            }
        }
    }

    BTreeNode<T>* clone(BTreeNode<T>* node)const
    {
        BTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            ret = BTreeNode<T>::NewNode();

            if(node != NULL)
            {
                ret->value = node->value;
                ret->left = clone(node->left);
                ret->right = clone(node->right);

                if(ret->left != NULL)   //指定父子关系
                {
                    ret->left->parent = ret;
                }
                if(ret->right != NULL)
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to creat node...");
            }
        }
        return ret;
    }
    bool equal(BTreeNode<T>* lh, BTreeNode<T>* rh)const
    {
        bool ret = true;
        if(lh == rh)
        {
            ret = true; 
        }
        else if((lh != NULL) && (rh != NULL))
        {
            ret =  ((lh->value == rh->value) && equal(lh->left,rh->left) && equal(lh->right, rh->right));
        }
        else
        {
            ret = false; 
        }
        return ret;
    }
    BTreeNode<T>* add(BTreeNode<T>* lh, BTreeNode<T>* rh)const
    {
        BTreeNode<T>* ret = NULL;

        if((lh != NULL) && (rh == NULL))
        {
            ret = clone(lh);
        }
        else if((lh == NULL) && (rh != NULL))
        {
            ret = clone(rh);
        }  
        else if((lh != NULL) && (rh != NULL))
        {
            ret = BTreeNode<T>::NewNode();

            if( ret != NULL )
            {
                ret->value = lh->value + rh->value;

                ret->left = add(lh->left, rh->left);
                ret->right = add(lh->right, rh->right);
                if( ret->left != NULL )
                {
                    ret->left->parent = ret;
                }
                if( ret->right != NULL )
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to creat node...");
            }
            
        }
        return ret;
    }
    void traversal(BTTraversal order, LinkQueue<BTreeNode<T>*>& queue)
    {
        switch(order)
        {
            case PreOrder:
                preOrderTraversal(root(), queue);
                break;
            case InOrder:
                inOrderTraversal(root(), queue);
                break;
            case PostOrder:
                postOrderTraversal(root(), queue);
                break;
            case LeverOrder:
                levelOrderTraversal(root(), queue);
				break;
            default:
                THROW_EXCEPTION(InvalidParameterException, "Paramenter order is invalid...");
                break;
        }
    }

    BTreeNode<T>* connect(LinkQueue<BTreeNode<T>*>& queue)  //线索--连接函数
    {
        BTreeNode<T>* ret = NULL;

        if(queue.length() > 0)
        {
            ret = queue.front();
            BTreeNode<T>* slider = queue.front();
            queue.remove();
            slider->left = NULL;   //链表头节点左指针为NULL

            while (queue.length() > 0)
            {
                slider->right = queue.front();
                queue.front()->left = slider;
                slider = queue.front();
                queue.remove();
            }
            slider->right = NULL;
        }
        return ret;
    }
public:
    // BTree()
    // {

    // }
    bool insert(TreeNode<T>* node)
    {
        return insert(node, ANY);
    }
    virtual bool insert(TreeNode<T>* node, BTNodePos pos)
    {
        bool ret = true;
        if(node != NULL)
        {
            if(this->m_root == NULL)
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                BTreeNode<T>* np = dynamic_cast<BTreeNode<T>*>(node->parent);
                if(np != NULL)
                {
                    ret = insert(dynamic_cast<BTreeNode<T>*>(node), np, pos);
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "NewNode's parent is NULL...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Paramenter node can not be NULL...");
        }
        return ret;
    }
    bool insert(const T& value, TreeNode<T>* parrent)
    {
        return insert(value, parrent, ANY);
    }
    virtual bool insert(const T& value, TreeNode<T>* parrent, BTNodePos pos)
    {
        bool ret = true;
        BTreeNode<T>* newNode = BTreeNode<T>::NewNode();
        if(newNode != NULL)
        {
            newNode->parent = parrent;
            newNode->value = value;
            ret = insert(newNode, pos);
            if( !ret )
            {
                delete newNode;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to malloc for new node...");
        }

        return ret;    
    }
    SharedPointer< Tree<T> > remove(const T& value)
    {
        BTree<T>* ret = NULL;

        BTreeNode<T>* node = find(value);

        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid...");
        }
        else
        {
            remove(node, ret);
            m_queue.clear();
        }
        return ret;
    }
    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        BTree<T>* ret = NULL;

        node = find(node);

        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid...");
        }
        else
        {
            remove(dynamic_cast<BTreeNode<T>*>(node), ret);
            m_queue.clear();
        }
        return ret;
    }
    BTreeNode<T>* find(const T& value)const
    {
        return find(root(), value);
    }
    BTreeNode<T>* find(TreeNode<T>* node)
    {
        return find(root(), dynamic_cast<BTreeNode<T>*>(node));
    }
    BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
    }
    int degree()const
    {
        return degree(root());
    }
    int count()const
    {
        return count(root());
    }

    int height()const
    {
       return height(root());
    }
    void clear()
    {
        free(root());
        m_queue.clear();
        this->m_root = NULL;
    }


   bool begin()
    {
        bool ret = (root() != NULL);

        if( ret )
        {
            m_queue.clear();    //先清空，防止上一次的遍历残留
            m_queue.add(root());
        }
        return ret;
    }

    bool end()  //判断遍历是否结束
    {
        return (m_queue.length() == 0);     //队列为空表示遍历完毕
    }

    bool next()
    {
        bool ret = (m_queue.length() > 0);  //有元素才移动

        if( ret )
        {
            BTreeNode<T>* node = m_queue.front();   //指向队列的首节点

            m_queue.remove();   //将首节点删除,移动了游标

            if(node->left != NULL)
            {
                m_queue.add(node->left);
            }
            if(node->right != NULL)
            {
                m_queue.add(node->right);
            }
        }
        return ret;
    }

    T current()
    {
        if( !end() )
        {
            return m_queue.front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "NO value at current position ...");
        }
    }

    //经典遍历方式
    SharedPointer< Array<T> > traversal(BTTraversal order)
    {
        DynamicArray<T>* ret = NULL;
        LinkQueue<BTreeNode<T>*> queue;

        traversal(order, queue);

        ret = new DynamicArray<T>(queue.length());
        if( ret != NULL )
        {
            for(int i=0; i<ret->length(); i++)
            {
                ret->set(i,queue.front()->value);
                queue.remove();
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "NoEnough memory to crear DynamicArray...");
        }
        return ret;
    }
    SharedPointer< BTree<T> > clone()const
    {
        BTree<T>* ret = new BTree<T>();

        if(ret != NULL)
        {
            ret->m_root = clone(root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat node...");
        }
        return ret;
    }
    bool operator == (const BTree<T>& btree)
    {
        return equal(root(), btree.root());
    }
    bool operator != (const BTree<T>& btree)
    {
        return !(*this == btree);
    }
    SharedPointer< BTree<T> > add(const BTree<T>& btree)const
    {
        BTree<T>* ret = new BTree<T>();

        if( ret != NULL )
        {
            ret->m_root = add(root(), btree.root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to creat node...");
        }
        return ret;
    }

    BTreeNode<T>* thread(BTTraversal order)
    {
        BTreeNode<T>* ret = NULL;

        LinkQueue<BTreeNode<T>*> queue;

        traversal(order, queue);    //排序，并保存在队列中

        ret = connect(queue);     //将队列连接为双向链表

        this->m_root = NULL;    //线索化后，二叉树将不存在，变为双向链表

        m_queue.clear();     //清空，树发生了改变，m_queue不清空会导致4个遍历函数出现问题（begin、end）

        return ret;
    }
    ~BTree()
    {
        clear();
    }
};
}



#endif // BTREE

