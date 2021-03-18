#ifndef STATICLIST
#define STATICLIST

#include "SeqList.h"

namespace DataStLib
{
template<typename T, int N>
class StaticList : public SeqList<T>
{
protected:
		T m_space[N];		//ʹ��ԭ��������Ϊ�洢�ռ�
public:
		StaticList()		//���캯����ָ�������Ա�ľ���ֵ����ʼ����
		{
			this->m_array = m_space;
			this->m_length = 0;
		}
		int capacity()const	//��ȡ��ǰ�ռ������
		{
			return N;
		}
};
}






#endif // STATICLIST

