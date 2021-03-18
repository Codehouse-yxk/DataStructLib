#ifndef _SORT_H_
#define _SORT_H_

#include "Object/Object.h"
#include "Array/StaticArray.h"

namespace DataStLib
{
enum MODESELECT
{
    LOW2HIGH,
    HIGH2LOW,
};
class Sort : public Object
{
private:
	//�����಻���ж���
    Sort();
    Sort(const Sort&);
    Sort& operator = (const Sort&);
    template < typename T >
    static void Swap(T& a, T& b)
    {
        T c(a);
        a = b;
        b = c;
    }

    template < typename T >
    static void Merge(T src[], T helper[], int begin, int mid, int end, MODESELECT mode = LOW2HIGH)     //�鲢����
    {
        int leftBegin = begin;
        int rightBegin = mid+1;
        int helperBegin = begin;

        while( (leftBegin <= mid) && (rightBegin <= end))
        {
            if( (mode == LOW2HIGH) ? (src[leftBegin] < src[rightBegin]) : (src[leftBegin] > src[rightBegin]))
            {
                helper[helperBegin++] = src[leftBegin++];
            }
            else
            {
                helper[helperBegin++] = src[rightBegin++];
            }
        }
        /* �����������ʣ���Ԫ�أ�ȫ��һ���Կ��� */
        while ( leftBegin <= mid)
        {
            helper[helperBegin++] = src[leftBegin++];
        }
        while( rightBegin <= end)
        {
            helper[helperBegin++] = src[rightBegin++];
        }
        for(int i=begin; i<=end; i++)
        {
            src[i] = helper[i];
        }
    }
    template < typename T >
    static void Merge(T src[], T helper[], int begin, int end, MODESELECT mode = LOW2HIGH)     //�鲢����
    {
        if( begin < end )
        {
            int mid = (begin + end) / 2;

            Merge(src, helper, begin, mid, mode);
            Merge(src, helper, mid+1, end, mode);
            Merge(src, helper, begin, mid, end, mode);
        }
    }

    template <typename T>
    static int Partition(T array[], int begin, int end, MODESELECT mode = LOW2HIGH)     //���ţ����ֺ���
    {
        T pval = array[begin];

        while( begin < end )       //�������򣬲��ҵ���׼ֵ
        {
            while ( ((mode == LOW2HIGH) ? (array[end] > pval) : (array[end] < pval)) && (begin < end ))
            {
                end--;
            }
            Swap(array[begin], array[end]);

            while ( ((mode == LOW2HIGH) ? (array[begin] <= pval) : (array[begin] >= pval)) && (begin < end ))
            {
                begin++;
            }
            Swap(array[begin], array[end]);
        }

        array[begin] = pval;    //ȷ����׼ֵ���ڴ�λ��֮ǰ�����ڴ�λ��֮������
        return begin;
    }

    template < typename T >
    static void Quick(T array[], int begin, int end, MODESELECT mode = LOW2HIGH)     //��������
    {
        if( begin < end )
        {
            int pval = Partition(array, begin, end, mode);
            Quick(array, begin, pval-1, mode);
            Quick(array, pval+1, end, mode);
        }
    }



public:
    /*
    *   ѡ������ ��������δ�����������ҵ���С���󣩣��������ʼλ�ã�
    *             ���ٴ�ʣ��δ����Ԫ���м���Ѱ����С����Ԫ�أ���������������ĩβ��
    * 
    *   ʱ�临�Ӷ�O(n^2)
    */
    template < typename T >
    static void Select(T array[], int len, MODESELECT mode = LOW2HIGH)     //ѡ�����򣨲��ȶ���
    {
        for(int i=0; i<len; i++)
        {
            int min = i;
            for(int j=i+1; j<len; j++)
            {
                if( (mode==LOW2HIGH) ? (array[j] < array[min]) : (array[j] > array[min]))
                {
                    min = j;
                }
            }
            if(min != i)
            {
                Swap(array[i], array[min]);
            }
        }
    }
    /*
    *   �������� ͨ�������������У�����δ�������ݣ��������������дӺ���ǰɨ�裬�ҵ���Ӧλ�ò����롣
    * 
    *   ʱ�临�Ӷ�O(n^2)
    */
    template < typename T >
    static void Insert(T array[], int len, MODESELECT mode = LOW2HIGH)     //���������ȶ���
    {
        for(int i=1; i<len; i++)    //��һ��Ԫ�ؿ��Բ����бȽϣ����Դ�1��ʼ
        {
           int k = i;
           T e = array[i];

           for(int j=i-1; (j>=0) && ((mode == LOW2HIGH) ? (e < array[j]) : (e > array[j])); j--)
           {
                array[j+1] = array[j];   //���������Ԫ������ƶ�
                k = j;
           }
           if( k != i )
           {
                array[k] = e;
           }
        }
    }
    /*
    *   ð������ �Ӻ�ʼ�����Ƚϣ��������Ԫ��С��ǰ���Ԫ�أ����н���������������ȥ����С��Ԫ�ػḡ��ˮ�棨ð�ݣ�
    * 
    *   ʱ�临�Ӷ�O(n^2)
    * 
    *   exchange�ǽ�����ǣ�����ð�������Ż���
    */
    template < typename T >
    static void Bubble(T array[], int len, MODESELECT mode = LOW2HIGH)     //ð�������ȶ���
    {
        bool exchange = true;

        for( int i=0; (i<len) && (exchange); i++)
        {
            exchange = false;
            for(int j=len-1; j>i; j--)
            {
                if((mode == LOW2HIGH) ? (array[j] < array[j-1]) : (array[j] > array[j-1]))
                {
                    Swap(array[j], array[j-1]);
                    exchange = true;
                }
            }
        }
    }

    /*
    *   ϣ��������С�������򣩣� ��������Ľ��棬�����а�����ϵ�����з��飬�Ը�����в�������
    * 
    *   ʱ�临�Ӷ�O(n^1.3)
    */
    template < typename T >
    static void Shell(T array[], int len, MODESELECT mode = LOW2HIGH)     //ϣ�����򣨲��ȶ���
    {
        int d = len;
        do
        {
            d = d / 3 + 1;

            for(int i=d; i<len; i+=d)   //��������  i��ʾ���������Ԫ�صĽǱ꣬��Ϊÿһ��Ƚ����ݵ����һ��һ��Ԫ�ؽǱ�
            {
                int k = i;
                T e = array[i];
                cout << "ex �� d = " << d << "       i = " << i << endl;

                for(int j=i-d; (j>=0) && (mode == LOW2HIGH) ? (e < array[j]) : (e > array[j]); j-=d)
                {   
                    cout << "in �� d = " << d << "       i = " << i << "       j = " << j << "   array[i] = " << array[i]  << "    array[j] = " << array[j] <<endl;
                    //j��ʾ��iͬһ�������Ԫ�ؽǱ�
                    array[j+d] = array[j];   //���������Ԫ������ƶ�
                    k = j;

                }
                if( k != i )
                {
                    array[k] = e;
                }
            }
        } while ( d > 1 );
    }

    /*
    *   �鲢���򣨷��η�������������(�鲢)�������кϲ����õ���ȫ��������С���ʹÿ��������������ʹ�����жμ�����
    * 
    *   ʱ�临�Ӷ�O(nLogn)   �ռ临�Ӷ�O(n)
    */
    template < typename T >
    static void Merge(T array[], int len, MODESELECT mode = LOW2HIGH)     //�鲢�����ȶ���
    {
        T* helper = new T[len];
        if( helper != NULL)
        {
            Merge(array, helper, 0, len-1, mode);
        }
        delete[] helper;
    }
    /*
    *   ����������ȡ�����е�ĳ��Ԫ����Ϊ��׼�����л���Ϊ��������������
    *               Ҫ��:   �����������������Ԫ�ض�С�ڻ���ڻ�׼Ԫ��
    *                       ���Ҳ�������������Ԫ�ض����ڻ�׼Ԫ��
    *                       �ۻ�׼Ԫ�������������������м�
    * 
    *   ʱ�临�Ӷ�O(nLogn)  �ռ临�Ӷ�O(nLogn)
    */    
    template < typename T >
    static void Quick(T array[], int len, MODESELECT mode = LOW2HIGH)     //�������򣨲��ȶ���
    {     
        Quick(array, 0, len-1, mode);
    }



    /* ʵ��DataStLib���о�̬��������� */
    template <typename T>
    static void Select(Array<T>& array, MODESELECT mode = LOW2HIGH)
    {
        Select(array.array(), array.length(), mode);
    }



};    
}
#endif // _SORT_H_

