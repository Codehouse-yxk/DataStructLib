#ifndef GRAPH_H
#define GRAPH_H

#include "Object.h"
#include "Array.h"
#include "SharedPointer.h"

namespace DataStLib {
    /* V: 与顶点关联的数据元素的类型， E: 与边关联的数据元素的类型【即权值类型】 */
    template<typename V, typename E>
    class Graph : public Object {
    public:
        /* 获取顶点i中元素的值 */
        virtual V getVertex(int i) = 0;

        /* 获取顶点i中元素的值 */
        virtual bool getVertex(int i, V &value) = 0;

        /* 设置目标顶点的值 */
        virtual bool setVertex(int i, const V &value) = 0;

        /* 获取邻接顶点集合 */
        virtual SharedPointer <Array<int>> getAdjacent(int i) = 0;

        /* 获取顶点i到顶点j的边上的权值 */
        virtual E getEdge(int i, int j) = 0;

        /* 获取顶点i到顶点j的边上的权值 */
        virtual bool getEdge(int i, int j, E &value) = 0;

        /* 设置i到j的边的权值 */
        virtual bool setEdge(int i, int j, const E &value) = 0;

        /* 删除i到j的边 */
        virtual bool removeEdge(int i, int j) = 0;

        /* 获取图中顶点总数 */
        virtual int vCount() = 0;

        /* 获取图中边的总数 */
        virtual int eCount() = 0;

        /* 获取目标顶点的出度 */
        virtual int OD(int i) = 0;

        /* 获取目标顶点的入度 */
        virtual int ID(int i) = 0;

        /* 获取目标顶点的度 */
        int TD(int i) {
            return OD(i) + ID(i);
        }
    };
}

#endif //GRAPH_H
