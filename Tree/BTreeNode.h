#ifndef _BTREENODE_
#define _BTREENODE_

#include "TreeNode.h"

namespace DataStLib
{
template<typename T>
class BTreeNode : public TreeNode<T>
{
public:
    BTreeNode<T>* left;
    BTreeNode<T>* right;

    static BTreeNode<T>* NewNode()  //工厂模式
    {
        BTreeNode<T>* ret = new BTreeNode<T>();
        if(ret != NULL)
        {
            ret->m_flag = true;
        }
        return ret;
    }
};
}




#endif // BTREENODE

