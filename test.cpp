//
// Created by 20218 on 2022/11/28.
//

#include "test.h"

namespace DataStLib {

    void Test::BTreeTest() {
        /*
                    A
                B  |   C
                E   F|   M   N
            X   Y
            前序：ABEXYFCMN
            中序：XEYBFAMCN
            后续：XYEFBMNCA
        */
        BTree<char> btree;
        TreeNode<char> *bn = NULL; //根节点

        btree.insert('A', NULL);

        bn = btree.find('A');
        btree.insert('B', bn);
        btree.insert('C', bn);

        bn = btree.find('B');
        btree.insert('E', bn);
        btree.insert('F', bn);

        bn = btree.find('C');
        btree.insert('M', bn);
        btree.insert('N', bn);

        bn = btree.find('E');
        btree.insert('X', bn);
        btree.insert('Y', bn);

        SharedPointer<Array<char>> tr = btree.traversal(PreOrder);

        cout << "===============层次遍历================" << endl;
        for (int i = 0; i < (*tr).length(); i++) {
            cout << (*tr)[i];
        }
        cout << endl;

        cout << "===============序列化================" << endl;
        auto pp = btree.thread(PreOrder);
        while (pp != NULL) {
            cout << pp->value;
            pp = pp->right;
        }
        cout << endl;
    }


    void Test::MatrixGraphTest() {
        /*
         * 0 --> 1 --> 2
         * 0 <-- 1
         * */
        MatrixGraph<3, int, int> p;

        //设置顶点值
        p.setVertex(0, 1);
        p.setVertex(1, 2);
        p.setVertex(2, 3);

        //设置边的权值及连接关系
        p.setEdge(0, 1, 100);
        p.setEdge(1, 0, 90);
        p.setEdge(1, 2, 50);

        //结点入度
        cout << "point 0 in degraee : " << p.ID(0) << endl;
        cout << "point 1 in degraee : " << p.ID(1) << endl;
        cout << "point 2 in degraee : " << p.ID(2) << endl;

        //结点出度
        cout << "point 0 out degraee : " << p.OD(0) << endl;
        cout << "point 1 out degraee : " << p.OD(1) << endl;
        cout << "point 2 out degraee : " << p.OD(2) << endl;

        //结点总度
        cout << "point 0 total degraee : " << p.TD(0) << endl;
        cout << "point 1 total degraee : " << p.TD(1) << endl;
        cout << "point 2 total degraee : " << p.TD(2) << endl;

        //获取权值
        cout << "0 -> 1 weight : " << p.getEdge(0, 1) << endl;
        cout << "1 -> 0 weight : " << p.getEdge(1, 0) << endl;
        cout << "1 -> 2 weight : " << p.getEdge(1, 2) << endl;

        //图的结点数
        cout << "point total num: " << p.vCount() << endl;

        //图的总边数
        cout << "edge total num: " << p.eCount() << endl;

        //获取顶点数据
        cout << "point total num: " << p.getVertex(1) << endl;

        //获取顶点1的邻接顶点
        SharedPointer<Array<int>> t = p.getAdjacent(1);
        cout << "point 1 adjacent is: ";
        for (int i = 0; i < t->length(); i++) {
            cout << (*t)[i] << "  ";
        }
        cout << endl;

        //删除一条边
        p.removeEdge(1, 2);
        cout << "edge total num: " << p.eCount() << endl;

        cout << "before modify point 1 value: " << p.getVertex(1) << endl;
        p.setVertex(1, 10);
        cout << "after modify point 1 value: " << p.getVertex(1) << endl;
    }
}
