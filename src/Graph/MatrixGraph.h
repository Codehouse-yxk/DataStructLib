
#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"
#include "Exception.h"
#include "DynamicArray.h"

/* 邻接矩阵法 */
namespace DataStLib {
    /* N: 顶点个数, V: 与顶点关联的数据元素的类型, E: 与边关联的数据元素的类型【即权值类型】 */
    template<int N, typename V, typename E>
    class MatrixGraph : public Graph<V, E> {
    protected:
        V *m_vertexes[N];   //顶点数组
        E *m_edges[N][N];   //二维邻接矩阵
        int m_eCount;       //记录图中边的总数

    public:
        MatrixGraph() {
            m_eCount = 0;
            for (int i = 0; i < vCount(); i++) {
                m_vertexes[i] = NULL;
                for (int j = 0; j < vCount(); j++) {
                    m_edges[i][j] = NULL;
                }
            }
        }

        ~MatrixGraph() {
            for (int i = 0; i < vCount(); i++) {
                for (int j = 0; j < vCount(); j++) {
                    delete m_edges[i][j];
                }
                delete m_vertexes[i];
            }
            m_eCount = 0;
        }

        V getVertex(int i) {
            V ret;

            if (!getVertex(i, ret)) {
                THROW_EXCEPTION(InvalidParameterException, "Index i is invalid...");
            }

            return ret;
        }

        bool getVertex(int i, V &value) {
            int ret = (0 <= i) && (i < vCount());
            if (ret) {
                if (m_vertexes[i] != NULL) {
                    value = *(m_vertexes[i]);
                } else {
                    THROW_EXCEPTION(InvalidOperationException, "No value create on this vertex...");
                }
            }
            return ret;
        }

        bool setVertex(int i, const V &value) {
            int ret = (0 <= i) && (i < vCount());
            if (ret) {
                //通过data来满足异常安全性
                V *data = m_vertexes[i];
                if (data == NULL) {
                    data = new V();
                }

                if (data != NULL) {
                    *data = value;
                    m_vertexes[i] = data;
                } else {
                    THROW_EXCEPTION(InvalidOperationException, "No memory to store new vertex...");
                }
            }
            return ret;
        }

        SharedPointer <Array<int>> getAdjacent(int i) {
            DynamicArray<int> *ret = NULL;

            if ((0 <= i) && (i < vCount())) {
                //统计与顶点i相关联的顶点个数
                int n = 0;
                for (int j = 0; j < vCount(); j++) {
                    if (m_edges[i][j] != NULL) {
                        n++;
                    }
                }

                ret = new DynamicArray<int>(n);

                if (ret != NULL) {
                    for (int j = 0, k = 0; j < vCount(); j++) {
                        if (m_edges[i][j] != NULL) {
                            ret->set(k++, j);
                        }
                    }
                } else {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret array...");
                }
            } else {
                THROW_EXCEPTION(InvalidParameterException, "Index i is invalid...");
            }

            return ret;
        }

        E getEdge(int i, int j) {
            E ret;
            if (!getEdge(i, j, ret)) {
                THROW_EXCEPTION(InvalidParameterException, "Index [i,j] is invalid...");
            }
            return ret;
        }

        bool getEdge(int i, int j, E &value) {
            int ret = ((0 <= i) && (i < vCount())) && ((0 <= j) && (j < vCount()));
            if (ret) {
                if (m_edges[i][j] != NULL) {
                    value = *(m_edges[i][j]);
                } else {
                    THROW_EXCEPTION(InvalidOperationException, "No value create on this edge...");
                }
            }
            return ret;
        }

        bool setEdge(int i, int j, const E &value) {
            int ret = ((0 <= i) && (i < vCount())) && ((0 <= j) && (j < vCount()));
            if (ret) {
                //通过data来满足异常安全性
                E *data = m_edges[i][j];
                if (data == NULL) {
                    data = new E();
                    if (data != NULL) {
                        *data = value;
                        m_edges[i][j] = data;
                        m_eCount++;
                    } else {
                        THROW_EXCEPTION(InvalidOperationException, "No memory to store new edge...");
                    }
                } else {
                    *data = value;
                }
            }

            return ret;
        }

        bool removeEdge(int i, int j) {
            int ret = ((0 <= i) && (i < vCount())) && ((0 <= j) && (j < vCount()));
            if (ret) {
                E *toDel = m_edges[i][j];
                m_edges[i][j] = NULL;
                if (toDel != NULL) {
                    m_eCount--;
                    delete toDel;
                }
            }
            return ret;
        }

        int vCount() {
            return N;
        }

        int eCount() {
            return m_eCount;
        }

        int OD(int i) {
            int ret = 0;

            if ((0 <= i) && (i < vCount())) {
                for (int j = 0; j < vCount(); j++) {
                    if (m_edges[i][j] != NULL) {
                        ret++;
                    }
                }
            } else {
                THROW_EXCEPTION(InvalidParameterException, "Index i is invalid...");
            }

            return ret;
        }

        int ID(int i) {
            int ret = 0;

            if ((0 <= i) && (i < vCount())) {
                for (int j = 0; j < vCount(); j++) {
                    if (m_edges[j][i] != NULL) {
                        ret++;
                    }
                }
            } else {
                THROW_EXCEPTION(InvalidParameterException, "Index i is invalid...");
            }
            return ret;
        }
    };


}

#endif //MATRIXGRAPH_H
