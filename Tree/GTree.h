#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"
#include "Exception/Exception.h"
#include "Queue/LinkQueue.h"

namespace DataStLib
{
template <typename T>
class GTree : public Tree<T>
{
protected:
    LinkQueue<GTreeNode<T>*> m_queue;

    GTreeNode<T>* find(GTreeNode<T>* node, const T& value)const
    {
        GTreeNode<T>* ret = NULL;
        if( node != NULL )
        {
            if(node->value == value)
            {
                ret = node;
            }
            else
            {
                for(node->child.move(0); (!node->child.end()) && (ret == NULL); node->child.next()) //����ÿһ������
                {
                    ret = find(node->child.current(), value);   //����һ���ӽڵ��в���ֵΪvalue�ĳ�Ա
                }
            }
        }
        return ret;
    }
    GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj)const
    {
        GTreeNode<T>* ret = NULL;

        if(node == obj)
        {
            ret = node;
        }
        else
        {
            if(node != NULL)
            {
                for(node->child.move(0); (!node->child.end()) && (ret == NULL); node->child.next()) //����ÿһ������
                {
                    ret = find(node->child.current(), obj);   //����һ���ӽڵ��в���obj���
                }
            }
        }
        return ret;
    }
    void remove(GTreeNode<T>* node, GTree<T>*& ret)
    {
        ret = new GTree<T>();

        if( ret == NULL )
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat new tree");
        }
        else
        {
            if( root() == node )
            {
                this->m_root = NULL;
            }
            else        //���ƴ����ڵ���ӽڵ�Ĺ�ϵ
            {
                LinkList<GTreeNode<T>*>& child = (dynamic_cast<GTreeNode<T>*>(node->parent))->child;

                child.remove(child.find(node));

                node->parent = NULL;
            }
            ret->m_root = node;
        }
    }

    int count(GTreeNode<T>* node)const
    {
        int ret = 0;
        if( node != NULL)
        {
            ret = 1;
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                ret += count(node->child.current());
            }
        }
        return ret;
    }

    int height(GTreeNode<T>* node)const
    {
        int ret = 0;
        if(node != NULL)
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                int h = height(node->child.current());

                if( ret < h )
                {
                    ret = h;
                }
            }
            ret += 1;   //���ϸ��ڵ�
        }
        return ret;
    }

    int degree(GTreeNode<T>* node)const
    {
        int ret = 0;
        if(node != NULL)
        {
            ret = node->child.length();
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                int l = degree(node->child.current());
                
                if( ret < l )
                {
                    ret = l;
                }
            }
        }
        return ret;
    }
public:
    GTree()
    {

    }
    bool insert(TreeNode<T>* node)
    {
        bool ret = true;
        if( node != NULL)
        {
            if( this->m_root == NULL )  //��Ϊ��������ô������½ڵ���Ϊ���ڵ�
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                GTreeNode<T>* pn = find(node->parent);
                if( pn!= NULL )
                {
                    GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);    
                    if( pn->child.find(n) < 0 )     //�Ѿ�ȷ����Ŀ����ĸ��ڵ㣬����ֱ�ӿ����ڵ���ӽڵ��Ƿ��Ѿ�����Ŀ���㣬�����ڣ�����Ҫ����
                    {
                        //С��0��˵��Ŀǰ����û��Ŀ���㡣������
                        pn->child.insert(n);
                    }
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "paraments is error in bool insert(TreeNode<T>* node)");
                }
                
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "paraments is error in bool insert(TreeNode<T>* node)");
        }
        
        return ret;
    }
    bool insert(const T& value, TreeNode<T>* parrent)   //�ڸ����ĸ��ڵ����Ԫ��
    {
        bool ret = true;

        GTreeNode<T>* newNode = GTreeNode<T>::NewNode();

        if( newNode != NULL )
        {
            newNode->value = value;
            newNode->parent = parrent;
            insert(dynamic_cast<TreeNode<T>*>(newNode));
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat new tree node...");
        }
        

        return ret;
    }
    SharedPointer< Tree<T> > remove(const T& value)     //ɾ��������Ŀ����������������Ƴ�
    {
        GTree<T>* ret = NULL;
        GTreeNode<T>* node = find(value);

        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the node via parameter value...");
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
        GTree<T>* ret = NULL;
        node = find(node);

        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid...");
        }
        else
        {
            remove(dynamic_cast<GTreeNode<T>*>(node), ret);
            m_queue.clear();        //ɾ�����Ϊʲô��Ҫ������ʱ�Ķ������
        }
        return ret;
    }
    GTreeNode<T>* find(const T& value)const //���Ҳ������շ���Ŀ�����ݵ�ַ
    {
        return find(root(), value);
    }
    GTreeNode<T>* find(TreeNode<T>* node)   //���Ҳ������շ���Ŀ�����ַ
    {
        return find(root(), dynamic_cast< GTreeNode<T>* >(node));
    }

    void free(GTreeNode<T>* node)
    {
        if( node != NULL )
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                free(node->child.current());
            }
            if( node->flag() == true )
            {
                delete node;
            }
        }
    }

    GTreeNode<T>* root() const
    {
        return (dynamic_cast< GTreeNode<T>* >(this->m_root));
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
    void clear()    //����������û���ͷ�ÿ�����
    {
        free(root());
        this->m_root = NULL;

        m_queue.clear();
    }


    /*============ ��α��������ڵ㿪ʼ��ÿ�д����ұ�������ʹ���α�˼�� ==========*/
    bool begin()
    {
        bool ret = (root() != NULL);

        if( ret )
        {
            m_queue.clear();    //����գ���ֹ��һ�εı�������
            m_queue.add(root());
        }
        return ret;
    }

    bool end()  //�жϱ����Ƿ����
    {
        return (m_queue.length() == 0);     //����Ϊ�ձ�ʾ�������
    }

    bool next()
    {
        bool ret = (m_queue.length() > 0);  //��Ԫ�ز��ƶ�

        if( ret )
        {
            GTreeNode<T>* node = m_queue.front();   //ָ����е��׽ڵ�

            m_queue.remove();   //���׽ڵ�ɾ��,�ƶ����α�

            for(node->child.move(0); !node->child.end(); node->child.next())     //��ɾ�����ĺ��ӽ��ȫ���������
            {
                m_queue.add(node->child.current());     //���ӽ���е������ÿ��Ԫ�ص�����ΪGTreeNode<T>*��������valueֵΪһ��ָ��GTreeNode<T>��ָ��
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
	~GTree()
    {
        clear();
    }
};
}


#endif // GTREE_H

