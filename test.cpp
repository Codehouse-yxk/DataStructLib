//
// Created by 20218 on 2022/11/28.
//

#include "test.h"

namespace DataStLib {

    void Test::RangeArrayTest() {
        RangeArray<int> a(-5, 5);
        for (int i = -5; i <= 5; i++) {
            a[i] = i;
        }

        cout << "array length: " << a.length() << endl;
        cout << "array lower: " << a.lower() << endl;
        cout << "array upper: " << a.upper() << endl;

        for (int i = a.lower(); i <= a.upper(); i++) {
            cout << a[i] << " ";
        }
        cout << endl;

        RangeArray<int> b(0, 1);
        b = a;
        for (int i = b.lower(); i <= b.upper(); i++) {
            cout << b[i] << " ";
        }
        cout << endl;

        RangeArray<int> c(a);
        for (int i = c.lower(); i <= c.upper(); i++) {
            cout << c[i] << " ";
        }
        cout << endl;
    }

    void Test::DualLinkQueueTest() {
        DualLinkQueue<int> q;

        q.add_back(0);
        q.add_back(1);
        q.add_back(2);

        //0 1 2
//        while (q.length() > 0){
//            cout << q.front() << " ";
//            q.remove_front();
//        }

        //2 1 0
//        while (q.length() > 0){
//            cout << q.back() << " ";
//            q.remove_back();
//        }

        q.add_front(-1);
        q.add_front(-2);
        q.remove_back();
        //-2 -1 0 1
        while (q.length() > 0) {
            cout << q.front() << " ";
            q.remove_front();
        }
    }

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

    void Test::ListGraphTest() {
        /*
         * A --> B --> C --> D
         * A --> D
         * D --> B
         * */

        ListGraph<char, int> g;

        //添加顶点
        cout << "add vertex..." << endl;
        g.addVertex('A');
        g.addVertex('B');
        g.addVertex('C');
        g.addVertex('D');

        for (int i = 0; i < g.vCount(); i++) {
            cout << i << " : " << g.getVertex(i) << endl;
        }

        //移除一个顶点
        g.removeVertex();
        cout << "after remove vertex..." << endl;
        for (int i = 0; i < g.vCount(); i++) {
            cout << i << " : " << g.getVertex(i) << endl;
        }
        g.addVertex('D');

        cout << "set edge for vertex..." << endl;
        g.setEdge(0, 1, 5);
        g.setEdge(0, 3, 6);
        g.setEdge(1, 2, 8);
        g.setEdge(2, 3, 2);
        g.setEdge(3, 1, 9);

        cout << "0 -> 1: " << g.getEdge(0, 1) << endl;
        cout << "0 -> 3: " << g.getEdge(0, 3) << endl;
        cout << "1 -> 2: " << g.getEdge(1, 2) << endl;
        cout << "2 -> 3: " << g.getEdge(2, 3) << endl;
        cout << "3 -> 1: " << g.getEdge(3, 1) << endl;

        SharedPointer<Array<int>> arr = g.getAdjacent(3);
        cout << "node 0 adjacent node: [  ";
        for (int i = 0; i < arr->length(); i++) {
            cout << (*arr)[i] << "  ";
        }
        cout << "]" << endl;

        //结点入度
        cout << "point 0 in degraee : " << g.ID(0) << endl;
        cout << "point 1 in degraee : " << g.ID(1) << endl;
        cout << "point 2 in degraee : " << g.ID(2) << endl;
        cout << "point 3 in degraee : " << g.ID(3) << endl;

        //结点出度
        cout << "point 0 out degraee : " << g.OD(0) << endl;
        cout << "point 1 out degraee : " << g.OD(1) << endl;
        cout << "point 2 out degraee : " << g.OD(2) << endl;
        cout << "point 3 out degraee : " << g.OD(3) << endl;

        //结点总度
        cout << "point 0 total degraee : " << g.TD(0) << endl;
        cout << "point 1 total degraee : " << g.TD(1) << endl;
        cout << "point 2 total degraee : " << g.TD(2) << endl;
        cout << "point 3 total degraee : " << g.TD(3) << endl;

        cout << "egge total num: " << g.eCount() << endl;
        g.removeEdge(0, 1);
        g.removeEdge(2, 3);
        cout << "egge total num: " << g.eCount() << endl;
        g.removeEdge(3, 3); //边不存在，抛异常
    }

    void Test::MatrixGraphBFSTest() {
        MatrixGraph<9, char, int> g;
        const char *D = "ABEDCGFHI";
        for (int i = 0; i < 9; i++) {
            g.setVertex(i, D[i]);
        }

        //无向图用有向图表示——>对称设置边
        g.setEdge(0, 1, 0);
        g.setEdge(1, 0, 0);

        g.setEdge(0, 3, 0);
        g.setEdge(3, 0, 0);

        g.setEdge(0, 4, 0);
        g.setEdge(4, 0, 0);

        g.setEdge(1, 2, 0);
        g.setEdge(2, 1, 0);

        g.setEdge(1, 4, 0);
        g.setEdge(4, 1, 0);

        g.setEdge(2, 5, 0);
        g.setEdge(5, 2, 0);

        g.setEdge(3, 6, 0);
        g.setEdge(6, 3, 0);

        g.setEdge(4, 6, 0);
        g.setEdge(6, 4, 0);

        g.setEdge(7, 6, 0);
        g.setEdge(6, 7, 0);

        g.setEdge(8, 7, 0);
        g.setEdge(7, 8, 0);

        SharedPointer<Array<int>> bfs = g.BFS(0);
        cout << "matrix graph bfs result: [ ";
        for (int i = 0; i < bfs->length(); i++) {
            cout << (*bfs)[i] << " ";
        }
        cout << "]" << endl;

        cout << "matrix graph bfs result: [ ";
        for (int i = 0; i < bfs->length(); i++) {
            cout << g.getVertex((*bfs)[i]) << " ";
        }
        cout << "]" << endl;
    }

    void Test::ListGraphBFSTest() {
        ListGraph<char, int> g;
        const char *D = "ABEDCGFHI";
        for (int i = 0; i < 9; i++) {
            g.addVertex(D[i]);
        }

        //无向图用有向图表示——>对称设置边
        g.setEdge(0, 1, 0);
        g.setEdge(1, 0, 0);

        g.setEdge(0, 3, 0);
        g.setEdge(3, 0, 0);

        g.setEdge(0, 4, 0);
        g.setEdge(4, 0, 0);

        g.setEdge(1, 2, 0);
        g.setEdge(2, 1, 0);

        g.setEdge(1, 4, 0);
        g.setEdge(4, 1, 0);

        g.setEdge(2, 5, 0);
        g.setEdge(5, 2, 0);

        g.setEdge(3, 6, 0);
        g.setEdge(6, 3, 0);

        g.setEdge(4, 6, 0);
        g.setEdge(6, 4, 0);

        g.setEdge(7, 6, 0);
        g.setEdge(6, 7, 0);

        g.setEdge(8, 7, 0);
        g.setEdge(7, 8, 0);

        SharedPointer<Array<int>> bfs = g.BFS(0);
        cout << "list graph bfs result: [ ";
        for (int i = 0; i < bfs->length(); i++) {
            cout << (*bfs)[i] << " ";
        }
        cout << "]" << endl;

        cout << "list graph bfs result: [ ";
        for (int i = 0; i < bfs->length(); i++) {
            cout << g.getVertex((*bfs)[i]) << " ";
        }
        cout << "]" << endl;
    }

    void Test::MatrixGraphDFSTest() {
        MatrixGraph<9, char, int> g;
        const char *D = "ABEDCGFHI";
        for (int i = 0; i < 9; i++) {
            g.setVertex(i, D[i]);
        }

        //无向图用有向图表示——>对称设置边
        g.setEdge(0, 1, 0);
        g.setEdge(1, 0, 0);

        g.setEdge(0, 3, 0);
        g.setEdge(3, 0, 0);

        g.setEdge(0, 4, 0);
        g.setEdge(4, 0, 0);

        g.setEdge(1, 2, 0);
        g.setEdge(2, 1, 0);

        g.setEdge(1, 4, 0);
        g.setEdge(4, 1, 0);

        g.setEdge(2, 5, 0);
        g.setEdge(5, 2, 0);

        g.setEdge(3, 6, 0);
        g.setEdge(6, 3, 0);

        g.setEdge(4, 6, 0);
        g.setEdge(6, 4, 0);

        g.setEdge(7, 6, 0);
        g.setEdge(6, 7, 0);

        g.setEdge(8, 7, 0);
        g.setEdge(7, 8, 0);

        SharedPointer<Array<int>> dfs = g.DFS(0);
        cout << "matrix graph dfs result: [ ";
        for (int i = 0; i < dfs->length(); i++) {
            cout << (*dfs)[i] << " ";
        }
        cout << "]" << endl;

        cout << "matrix graph dfs result: [ ";
        for (int i = 0; i < dfs->length(); i++) {
            cout << g.getVertex((*dfs)[i]) << " ";
        }
        cout << "]" << endl;
    }

    void Test::ListGraphDFSTest() {
        ListGraph<char, int> g;
        const char *D = "ABEDCGFHI";
        for (int i = 0; i < 9; i++) {
            g.addVertex(D[i]);
        }

        //无向图用有向图表示——>对称设置边
        g.setEdge(0, 1, 0);
        g.setEdge(1, 0, 0);

        g.setEdge(0, 3, 0);
        g.setEdge(3, 0, 0);

        g.setEdge(0, 4, 0);
        g.setEdge(4, 0, 0);

        g.setEdge(1, 2, 0);
        g.setEdge(2, 1, 0);

        g.setEdge(1, 4, 0);
        g.setEdge(4, 1, 0);

        g.setEdge(2, 5, 0);
        g.setEdge(5, 2, 0);

        g.setEdge(3, 6, 0);
        g.setEdge(6, 3, 0);

        g.setEdge(4, 6, 0);
        g.setEdge(6, 4, 0);

        g.setEdge(7, 6, 0);
        g.setEdge(6, 7, 0);

        g.setEdge(8, 7, 0);
        g.setEdge(7, 8, 0);

        SharedPointer<Array<int>> dfs = g.DFS(0);
        cout << "list graph dfs result: [ ";
        for (int i = 0; i < dfs->length(); i++) {
            cout << (*dfs)[i] << " ";
        }
        cout << "]" << endl;

        cout << "list graph bfs result: [ ";
        for (int i = 0; i < dfs->length(); i++) {
            cout << g.getVertex((*dfs)[i]) << " ";
        }
        cout << "]" << endl;
    }

    void Test::MatrixGraphDFSByRecursiveTest() {
        MatrixGraph<9, char, int> g;
        const char *D = "ABEDCGFHI";
        for (int i = 0; i < 9; i++) {
            g.setVertex(i, D[i]);
        }

        //无向图用有向图表示——>对称设置边
        g.setEdge(0, 1, 0);
        g.setEdge(1, 0, 0);

        g.setEdge(0, 3, 0);
        g.setEdge(3, 0, 0);

        g.setEdge(0, 4, 0);
        g.setEdge(4, 0, 0);

        g.setEdge(1, 2, 0);
        g.setEdge(2, 1, 0);

        g.setEdge(1, 4, 0);
        g.setEdge(4, 1, 0);

        g.setEdge(2, 5, 0);
        g.setEdge(5, 2, 0);

        g.setEdge(3, 6, 0);
        g.setEdge(6, 3, 0);

        g.setEdge(4, 6, 0);
        g.setEdge(6, 4, 0);

        g.setEdge(7, 6, 0);
        g.setEdge(6, 7, 0);

        g.setEdge(8, 7, 0);
        g.setEdge(7, 8, 0);

        SharedPointer<Array<int>> dfs = g.DFSByRecursive(0);
        cout << "matrix graph dfs result: [ ";
        for (int i = 0; i < dfs->length(); i++) {
            cout << (*dfs)[i] << " ";
        }
        cout << "]" << endl;

        cout << "matrix graph dfs result: [ ";
        for (int i = 0; i < dfs->length(); i++) {
            cout << g.getVertex((*dfs)[i]) << " ";
        }
        cout << "]" << endl;
    }

    void Test::ListGraphDFSByRecursiveTest() {
        ListGraph<char, int> g;
        const char *D = "ABEDCGFHI";
        for (int i = 0; i < 9; i++) {
            g.addVertex(D[i]);
        }

        //无向图用有向图表示——>对称设置边
        g.setEdge(0, 1, 0);
        g.setEdge(1, 0, 0);

        g.setEdge(0, 3, 0);
        g.setEdge(3, 0, 0);

        g.setEdge(0, 4, 0);
        g.setEdge(4, 0, 0);

        g.setEdge(1, 2, 0);
        g.setEdge(2, 1, 0);

        g.setEdge(1, 4, 0);
        g.setEdge(4, 1, 0);

        g.setEdge(2, 5, 0);
        g.setEdge(5, 2, 0);

        g.setEdge(3, 6, 0);
        g.setEdge(6, 3, 0);

        g.setEdge(4, 6, 0);
        g.setEdge(6, 4, 0);

        g.setEdge(7, 6, 0);
        g.setEdge(6, 7, 0);

        g.setEdge(8, 7, 0);
        g.setEdge(7, 8, 0);

        SharedPointer<Array<int>> dfs = g.DFSByRecursive(0);
        cout << "list graph dfs result: [ ";
        for (int i = 0; i < dfs->length(); i++) {
            cout << (*dfs)[i] << " ";
        }
        cout << "]" << endl;

        cout << "list graph bfs result: [ ";
        for (int i = 0; i < dfs->length(); i++) {
            cout << g.getVertex((*dfs)[i]) << " ";
        }
        cout << "]" << endl;
    }
}
