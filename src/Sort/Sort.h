#ifndef _SORT_H_
#define _SORT_H_

#include "Object.h"
#include "StaticArray.h"

namespace DataStLib {
    enum MODESELECT {
        LOW2HIGH,
        HIGH2LOW,
    };

    class Sort : public Object {
    private:
        //排序类不会有对象
        Sort() {};

        Sort(const Sort &) {};

        Sort &operator=(const Sort &);

        template<typename T>
        static void Swap(T &a, T &b) {
            T c(a);
            a = b;
            b = c;
        }

        template<typename T>
        static void Merge(T src[], T helper[], int begin, int mid, int end, MODESELECT mode = LOW2HIGH) {    //归并排序
            int leftBegin = begin;
            int rightBegin = mid + 1;
            int helperBegin = begin;

            while ((leftBegin <= mid) && (rightBegin <= end)) {
                if ((mode == LOW2HIGH) ? (src[leftBegin] < src[rightBegin]) : (src[leftBegin] > src[rightBegin])) {
                    helper[helperBegin++] = src[leftBegin++];
                } else {
                    helper[helperBegin++] = src[rightBegin++];
                }
            }
            /* 将左或者右有剩余的元素，全部一次性拷贝 */
            while (leftBegin <= mid) {
                helper[helperBegin++] = src[leftBegin++];
            }
            while (rightBegin <= end) {
                helper[helperBegin++] = src[rightBegin++];
            }
            for (int i = begin; i <= end; i++) {
                src[i] = helper[i];
            }
        }

        template<typename T>
        static void Merge(T src[], T helper[], int begin, int end, MODESELECT mode = LOW2HIGH) {     //归并排序
            if (begin < end) {
                int mid = (begin + end) / 2;

                Merge(src, helper, begin, mid, mode);
                Merge(src, helper, mid + 1, end, mode);
                Merge(src, helper, begin, mid, end, mode);
            }
        }

        template<typename T>
        static int Partition(T array[], int begin, int end, MODESELECT mode = LOW2HIGH) {    //快排：划分函数
            T pval = array[begin];

            while (begin < end)       //划分排序，并找到基准值
            {
                while (((mode == LOW2HIGH) ? (array[end] > pval) : (array[end] < pval)) && (begin < end)) {
                    end--;
                }
                Swap(array[begin], array[end]);

                while (((mode == LOW2HIGH) ? (array[begin] <= pval) : (array[begin] >= pval)) && (begin < end)) {
                    begin++;
                }
                Swap(array[begin], array[end]);
            }

            array[begin] = pval;    //确定基准值，在此位置之前有序，在此位置之后有序。
            return begin;
        }

        template<typename T>
        static void Quick(T array[], int begin, int end, MODESELECT mode = LOW2HIGH) {   //快速排序
            if (begin < end) {
                int pval = Partition(array, begin, end, mode);
                Quick(array, begin, pval - 1, mode);
                Quick(array, pval + 1, end, mode);
            }
        }


    public:
        /*
        *   选择排序： ①首先在未排序序列中找到最小（大），存放在起始位置，
        *             ②再从剩余未排序元素中继续寻找最小（大）元素，放在已排序序列末尾。
        *
        *   时间复杂度O(n^2)
        */
        template<typename T>
        static void Select(T array[], int len, MODESELECT mode = LOW2HIGH) {      //选择排序（不稳定）
            for (int i = 0; i < len; i++) {
                int min = i;
                for (int j = i + 1; j < len; j++) {
                    if ((mode == LOW2HIGH) ? (array[j] < array[min]) : (array[j] > array[min])) {
                        min = j;
                    }
                }
                if (min != i) {
                    Swap(array[i], array[min]);
                }
            }
        }

        /*
        *   插入排序： 通过构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。
        *
        *   时间复杂度O(n^2)
        */
        template<typename T>
        static void Insert(T array[], int len, MODESELECT mode = LOW2HIGH) {       //插入排序（稳定）
            for (int i = 1; i < len; i++)    //第一个元素可以不进行比较，所以从1开始
            {
                int k = i;
                T e = array[i];

                for (int j = i - 1; (j >= 0) && ((mode == LOW2HIGH) ? (e < array[j]) : (e > array[j])); j--) {
                    array[j + 1] = array[j];   //将插入点后的元素向后移动
                    k = j;
                }
                if (k != i) {
                    array[k] = e;
                }
            }
        }

        /*
        *   冒泡排序： 从后开始两两比较，若后面的元素小于前面的元素，进行交换，反复进行下去，最小的元素会浮出水面（冒泡）
        *
        *   时间复杂度O(n^2)
        *
        *   exchange是交换标记，属于冒泡排序优化。
        */
        template<typename T>
        static void Bubble(T array[], int len, MODESELECT mode = LOW2HIGH) {      //冒泡排序（稳定）
            bool exchange = true;

            for (int i = 0; (i < len) && (exchange); i++) {
                exchange = false;
                for (int j = len - 1; j > i; j--) {
                    if ((mode == LOW2HIGH) ? (array[j] < array[j - 1]) : (array[j] > array[j - 1])) {
                        Swap(array[j], array[j - 1]);
                        exchange = true;
                    }
                }
            }
        }

        /*
        *   希尔排序（缩小增量排序）： 插入排序改进版，将序列按递增系数进行分组，对各组进行插入排序。
        *
        *   时间复杂度O(n^1.3)
        */
        template<typename T>
        static void Shell(T array[], int len, MODESELECT mode = LOW2HIGH) {   //希尔排序（不稳定）
            int d = len;
            do {
                d = d / 3 + 1;

                for (int i = d; i < len; i += d)   //插入排序  i表示即将插入的元素的角标，作为每一组比较数据的最后一个一个元素角标
                {
                    int k = i;
                    T e = array[i];
                    cout << "ex ： d = " << d << "       i = " << i << endl;

                    for (int j = i - d; (j >= 0) && (mode == LOW2HIGH) ? (e < array[j]) : (e > array[j]); j -= d) {
                        cout << "in ： d = " << d << "       i = " << i << "       j = " << j << "   array[i] = " << array[i] << "    array[j] = " << array[j] << endl;
                        //j表示与i同一组的数组元素角标
                        array[j + d] = array[j];   //将插入点后的元素向后移动
                        k = j;

                    }
                    if (k != i) {
                        array[k] = e;
                    }
                }
            } while (d > 1);
        }

        /*
        *   归并排序（分治法）：将已有序(归并)的子序列合并，得到完全有序的序列《先使每个子序列有序，再使子序列段间有序》
        *
        *   时间复杂度O(nLogn)   空间复杂度O(n)
        */
        template<typename T>
        static void Merge(T array[], int len, MODESELECT mode = LOW2HIGH) {   //归并排序（稳定）
            T *helper = new T[len];
            if (helper != NULL) {
                Merge(array, helper, 0, len - 1, mode);
            }
            delete[] helper;
        }

        /*
        *   快速排序：任取序列中的某个元素作为基准将序列划分为左右两个子序列
        *               要求:   ①左侧子序列中所有元素都小于或等于基准元素
        *                       ②右侧子序列中所有元素都大于基准元素
        *                       ③基准元素排在这两个子序列中间
        *
        *   时间复杂度O(nLogn)  空间复杂度O(nLogn)
        */
        template<typename T>
        static void Quick(T array[], int len, MODESELECT mode = LOW2HIGH) { //快速排序（不稳定）
            Quick(array, 0, len - 1, mode);
        }

        /* 实现DataStLib库中静态数组的排序 */
        template<typename T>
        static void Select(Array <T> &array, MODESELECT mode = LOW2HIGH) {
            Select(array.array(), array.length(), mode);
        }
    };
}
#endif // _SORT_H_

