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

namespace DataStLib {
    class Test {
    public:
        static void BTreeTest();

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
