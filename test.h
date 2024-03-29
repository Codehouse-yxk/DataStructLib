#ifndef TEST_H
#define TEST_H

#include "BTree.h"
#include "BTreeNode.h"
#include "CircleList.h"
#include "DuaCircleLinkList.h"
#include "DuaLinkList.h"
#include "DuaStaticLinkList.h"
#include "DynamicArray.h"
#include "DynamicList.h"
#include "Exception.h"
#include "GTree.h"
#include "GTreeNode.h"
#include "LinkList.h"
#include "LinkQueue.h"
#include "LinkStack.h"
#include "LinuxList.h"
#include "List.h"
#include "Object.h"
#include "SeqList.h"
#include "SharedPointer.h"
#include "SmartPointer.h"
#include "Sort.h"
#include "StaticArray.h"
#include "StaticLinkList.h"
#include "StaticList.h"
#include "StaticQueue.h"
#include "StaticStack.h"
#include "String.h"
#include "Graph.h"
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "RangeArray.h"
#include "DualLinkQueue.h"

namespace DataStLib {
    class Test {
    public:
        /*******************数组-测试*****************/
        static void RangeArrayTest();

        /*******************双端队列-测试*****************/
        static void DualLinkQueueTest();

        /*******************树-测试*****************/
        static void BTreeTest();

        /*******************图-测试*****************/
        static void MatrixGraphTest();

        static void ListGraphTest();

        static void MatrixGraphBFSTest();

        static void ListGraphBFSTest();

        static void MatrixGraphDFSTest();

        static void ListGraphDFSTest();

        static void MatrixGraphDFSByRecursiveTest();

        static void ListGraphDFSByRecursiveTest();
    };
}

#endif //TEST_H
