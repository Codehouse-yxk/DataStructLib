#ifndef GRAPH_H
#define GRAPH_H

#include "Object.h"
#include "Array.h"
#include "SharedPointer.h"
#include "LinkQueue.h"
#include "LinkStack.h"

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

        /* 以顶点i为起点进行广度优先遍历BFS */
        SharedPointer <Array<int>> BFS(int i) {
            DynamicArray<int> *ret = NULL;

            if ((0 <= i) && (i < vCount())) {
                LinkQueue<int> tmp;
                LinkQueue<int> result;
                DynamicArray<bool> isVisited(vCount());
                for (int j = 0; j < vCount(); j++) {
                    isVisited.set(j, false);
                }

                tmp.add(i);

                while (tmp.length() > 0) {
                    int v = tmp.front();
                    tmp.remove();
                    if (!isVisited[v]) {
                        SharedPointer<Array<int>> aj = getAdjacent(v);
                        for (int j = 0; j < aj->length(); j++) {
                            tmp.add((*aj)[j]);
                        }

                        result.add(v);
                        isVisited[v] = true;
                    }
                }
                ret = queue2Array(result);
            } else {
                THROW_EXCEPTION(InvalidParameterException, "Invalid value of i...");
            }
            return ret;
        }

        /* 以顶点i为起点进行深度优先遍历DFS */
        SharedPointer <Array<int>> DFS(int i) {
            DynamicArray<int> *ret = NULL;

            if ((0 <= i) && (i < vCount())) {
                LinkStack<int> tmp;
                LinkQueue<int> result;
                DynamicArray<bool> isVisited(vCount());
                for (int j = 0; j < vCount(); j++) {
                    isVisited.set(j, false);
                }

                tmp.push(i);

                while (tmp.size() > 0) {
                    int v = tmp.top();
                    tmp.pop();
                    if (!isVisited[v]) {
                        SharedPointer<Array<int>> aj = getAdjacent(v);
                        for (int j = aj->length() - 1; j >= 0; j--) {
                            tmp.push((*aj)[j]);
                        }

                        result.add(v);
                        isVisited[v] = true;
                    }
                }
                ret = queue2Array(result);
            } else {
                THROW_EXCEPTION(InvalidParameterException, "Invalid value of i...");
            }

            return ret;
        }

        /* 以顶点i为起点进行深度优先遍历DFS【递归版本】 */
        SharedPointer <Array<int>> DFSByRecursive(int i) {
            LinkQueue<int> result;
            DynamicArray<bool> isVisited(vCount());

            for (int j = 0; j < vCount(); j++) {
                isVisited.set(j, false);
            }

            DFSByRecursive(i, isVisited, result);

            return queue2Array(result);
        }

    protected:
        template<class T>
        DynamicArray <T> *queue2Array(LinkQueue <T> &queue) {
            DynamicArray<int> *ret = new DynamicArray<int>(queue.length());
            if (ret != NULL) {
                for (int i = 0; i < ret->length(); i++) {
                    ret->set(i, queue.front());
                    queue.remove();
                }
            } else {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough mem to new array...");
            }
            return ret;
        }

        void DFSByRecursive(int i, DynamicArray<bool> &isVisited, LinkQueue<int> &result) {
            if ((0 <= i) && (i < vCount())) {
                result.add(i);
                isVisited[i] = true;

                SharedPointer<Array<int>> aj = getAdjacent(i);
                for (int j = 0; j < aj->length(); j++) {    //有邻接顶点，继续递归遍历；无邻接顶点，则退出；
                    if (!isVisited[(*aj)[j]]) {
                        isVisited[(*aj)[j]] = true;
                        DFSByRecursive((*aj)[j], isVisited, result);
                    }
                }
            } else {
                THROW_EXCEPTION(InvalidParameterException, "Invalid value of i...");
            }
        }
    };
}

#endif //GRAPH_H
