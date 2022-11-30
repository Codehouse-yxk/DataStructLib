#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "Graph.h"

namespace DataStLib {
    template<typename E>
    struct Edge : public Object {
        int begin;  //起点
        int end;    //终点
        E data;     //权值

        Edge(int i = -1, int j = -1) {
            begin = i;
            end = j;
        }

        Edge(int i, int j, const E &value) {
            begin = i;
            end = j;
            data = value;
        }

        bool operator==(const Edge<E> &obj) {
            return (begin == obj.begin) && (end == obj.end);
        }

        bool operator!=(const Edge<E> &obj) {
            return !(*this == obj);
        }
    };

    template<typename V, typename E>
    class ListGraph : public Graph<V, E> {
    protected:
        struct Vertex : public Object {
            V *data;
            LinkList <Edge<E>> edge;

            Vertex() {
                data = NULL;
            }
        };

        LinkList<Vertex *> m_list;

    public:
        ListGraph(unsigned int n = 0) {
            for (int i = 0; i < n; i++) {
                addVertex();
            }
        }

        ~ListGraph() {
            while (m_list.length() > 0) {
                Vertex *toDel = m_list.get(0);
                m_list.remove(0);

                delete toDel->data;
                delete toDel;
            }
        }

        /* 添加顶点并返回顶点编号 */
        int addVertex() {
            int ret = -1;
            Vertex *v = new Vertex();

            if (v != NULL) {
                m_list.insert(v);
                ret = m_list.length() - 1;
            } else {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to new vertex...");
            }

            return ret;
        }

        /* 添加顶点并返回顶点编号，同时设置顶点的值 */
        int addVertex(const V &value) {
            int ret = addVertex();

            if (ret != -1) {
                setVertex(ret, value);
            }

            return ret;
        }

        V getVertex(int i) {
            V ret;

            if (!getVertex(i, ret)) {
                THROW_EXCEPTION(InvalidParameterException, "Index i is invalid...");
            }

            return ret;
        }

        bool getVertex(int i, V &value) {
            bool ret = (0 <= i) && (i < vCount());

            if (ret) {
                V *data = m_list.get(i)->data;

                if (data != NULL) {
                    value = *data;
                } else {
                    THROW_EXCEPTION(InvalidOperationException, "No value at this vertex...");
                }
            }

            return ret;
        }

        bool setVertex(int i, const V &value) {
            bool ret = (0 <= i) && (i < vCount());

            if (ret) {
                Vertex *node = m_list.get(i);
                V *data = node->data;

                if (data == NULL) {
                    data = new V();
                }

                if (data != NULL) {
                    *data = value;
                    node->data = data;
                } else {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to new vertex's data...");
                }
            }

            return ret;
        }

        /* 删除一个顶点【链表中最后一个】 */
        void removeVertex() {
            if (m_list.length() > 0) {
                int nodeIndex = m_list.length() - 1;
                Vertex *v = m_list.get(nodeIndex);

                //删除一个顶点，需要删除所有与该顶点相关的边
                if (m_list.remove(nodeIndex)) {
                    for (int i = (m_list.move(0), 0); !m_list.end(); m_list.next(), i++) {
                        int pos = m_list.current()->edge.find(Edge<E>(i, nodeIndex));
                        if (pos >= 0) {    //找到目标,索引为pos
                            m_list.current()->edge.remove(pos); //删除与顶点nodeIndex相关的边
                        }
                    }
                }
                delete v->data;
                delete v;
            } else {
                THROW_EXCEPTION(InvalidOperationException, "No vertex in current graph...");
            }
        }

        SharedPointer <Array<int>> getAdjacent(int i) {
            DynamicArray<int> *ret = NULL;

            if ((0 <= i) && (i < vCount())) {
                LinkList<Edge<E>> &e = m_list.get(i)->edge;
                ret = new DynamicArray<int>(e.length());
                if (ret != NULL) {
                    auto oo = *ret;
                    for (int n = (e.move(0), 0); !e.end(); e.next(), n++) {
                        ret->set(n, e.current().end);
                    }
                } else {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to new array...");
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
                LinkList<Edge<E>> &e = m_list.get(i)->edge;
                int pos = e.find(Edge<E>(i, j));
                if (pos >= 0) {
                    value = e.get(pos).data;
                } else {
                    THROW_EXCEPTION(InvalidOperationException, "No value create on this edge...");
                }
            }

            return ret;
        }

        bool setEdge(int i, int j, const E &value) {
            int ret = ((0 <= i) && (i < vCount())) && ((0 <= j) && (j < vCount()));

            if (ret) {
                LinkList<Edge<E>> &e = m_list.get(i)->edge;
                int pos = e.find(Edge<E>(i, j));
                if (pos >= 0) {   //存在目标边
                    ret = e.set(pos, Edge<E>(i, j, value));
                } else {  //不存在目标边
                    ret = e.insert(0, Edge<E>(i, j, value));
                }
            }

            return ret;
        }

        bool removeEdge(int i, int j) {
            int ret = ((0 <= i) && (i < vCount())) && ((0 <= j) && (j < vCount()));

            if (ret) {
                LinkList<Edge<E>> &e = m_list.get(i)->edge;
                int pos = e.find(Edge<E>(i, j));
                if (pos >= 0) {
                    ret = e.remove(pos);
                } else {
                    THROW_EXCEPTION(InvalidOperationException, "not find [i, j] edge...");
                }
            }

            return ret;
        }

        int vCount() {
            return m_list.length();
        }

        int eCount() {
            int ret = 0;

            for (m_list.move(0); !m_list.end(); m_list.next()) {
                ret += m_list.current()->edge.length();
            }

            return ret;
        }

        int OD(int i) {
            int ret = 0;

            if ((0 <= i) && (i < vCount())) {
                ret = m_list.get(i)->edge.length();
            } else {
                THROW_EXCEPTION(InvalidParameterException, "Index i is invalid...");
            }

            return ret;
        }

        int ID(int i) {
            int ret = 0;

            if ((0 <= i) && (i < vCount())) {
                for (m_list.move(0); !m_list.end(); m_list.next()) {
                    LinkList<Edge<E>> &e = m_list.current()->edge;
                    for (e.move(0); !e.end(); e.next()) {
                        if (e.current().end == i) {
                            ret++;
                            break;
                        }
                    }
                }
            } else {
                THROW_EXCEPTION(InvalidParameterException, "Index i is invalid...");
            }

            return ret;
        }
    };
}

#endif //LISTGRAPH_H
