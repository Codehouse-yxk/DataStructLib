#ifndef DUASTATICLINKLIST
#define DUASTATICLINKLIST

#include "DuaLinkList.h"

namespace DataStLib {
    template<typename T, int N>
    class DuaStaticLinkList : public DuaLinkList<T> {
    protected:
        typedef typename DuaLinkList<T>::Node Node;

        struct SNode : public Node {
            void *operator new(size_t size, void *loc) {
                (void) size;
                return loc;
            }
        };

        unsigned char m_space[N * sizeof(SNode)];       //预留空间的大小
        int m_used[N];

        Node *Creat() {
            SNode *ret = NULL;
            for (int i = 0; i < N; i++) {
                if (!m_used[i]) {
                    ret = reinterpret_cast<SNode *>(m_space) + i;
                    ret = new(ret)SNode();
                    m_used[i] = 1;
                    break;
                }
            }
            return ret;
        }

        void destroy(Node *pn) {
            SNode *space = reinterpret_cast<SNode *>(m_space);
            SNode *psn = dynamic_cast<SNode *>(pn);

            for (int i = 0; i < N; i++) {
                if (psn == space + i) {
                    m_used[i] = 0;
                    psn->~SNode();
                    break;
                }
            }
        }

    public:
        DuaStaticLinkList() {
            for (int i = 0; i < N; i++) {
                m_used[i] = 0;
            }
        }

        int capacity() {
            return N;
        }

        ~DuaStaticLinkList() {
            this->clear();
        }
    };
}


#endif // DUASTATICLINKLIST

