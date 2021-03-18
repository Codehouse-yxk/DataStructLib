#ifndef STATICLIST
#define STATICLIST

#include "SeqList.h"

namespace DataStLib
{
template<typename T, int N>
class StaticList : public SeqList<T>
{
protected:
		T m_space[N];		//使用原生数组作为存储空间
public:
		StaticList()		//构造函数：指定父类成员的具体值（初始化）
		{
			this->m_array = m_space;
			this->m_length = 0;
		}
		int capacity()const	//获取当前空间的容量
		{
			return N;
		}
};
}






#endif // STATICLIST

