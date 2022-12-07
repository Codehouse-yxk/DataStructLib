#include "MyString.h"
#include "Exception.h"
#include <cstdlib>
#include <cstring>

using namespace std;

namespace DataStLib {

    // KMP子串查找算法---创建PMT表
    int *MyString::MakePmtTable(const char *s) {
        int len = strlen(s);
        int *table = static_cast<int *>(malloc(sizeof(int) * len));

        if (table != NULL) {
            int LongLength = 0; //前后缀交集元素的最长长度
            table[0] = 0;       //长度为1的子串，LL长度为0；

            //贪心算法（假设下一步成立）
            for (int i = 1; i < len; i++) {
                while ((LongLength > 0) && (s[LongLength] != s[i])) //若不一致，则从table中循环查找已经匹配的LongLength值，否则未匹配到
                {
                    LongLength = table[LongLength - 1];
                }

                //在上一次LongLength值基础上往后扩展一个字符，判断这个字符与新加入的字符是否一致
                if (s[LongLength] == s[i]) {
                    LongLength++;
                }

                table[i] = LongLength;
            }
        }
        return table;
    }

    // KMP算法
    int MyString::KMP(const char *s, const char *p) {
        int ret = -1;
        int sl = strlen(s);
        int pl = strlen(p);
        int *pmt = MakePmtTable(p);

        if ((pmt != NULL) && (pl > 0) && (pl <= sl)) {
            for (int i = 0, j = 0; i < sl; i++) {
                while ((j > 0) && s[i] != p[j]) {
                    j = pmt[j - 1];
                }

                if (s[i] == p[j]) {
                    j++;
                }

                if (j == pl) {
                    ret = i + 1 - pl;
                    break;
                }
            }
        }
        return ret;
    }

    int MyString::indexOf(const char *s) const {
        return (KMP(m_str, s ? s : ""));
    }

    int MyString::indexOf(const MyString &s) const {
        return (KMP(m_str, s.m_str));
    }

    MyString &MyString::remove(int index, int len) {
        if (index >= 0 && index < m_length) {
            int left = index;
            int right = index + len;

            while ((left < right) && (right < m_length)) {
                m_str[left++] = m_str[right++];
            }

            m_str[left] = '\0';
            m_length = left;
        }
        return *this;
    }

    MyString &MyString::remove(const char *s) {
        return remove(indexOf(s), s ? strlen(s) : 0);
    }

    MyString &MyString::remove(const MyString &s) {
        return remove(indexOf(s), s.length());
    }

    MyString &MyString::replace(const char *t, const char *s) {
        int index = indexOf(t);

        if (index > 0) {
            remove(t);
            insert(index, s);
        }

        return *this;
    }

    MyString &MyString::replace(const MyString &t, const char *s) {
        return replace(t.m_str, s);
    }

    MyString &MyString::replace(const char *t, const MyString &s) {
        return replace(t, s.m_str);
    }

    MyString &MyString::replace(const MyString &t, const MyString &s) {
        return replace(t.m_str, s.m_str);
    }

    MyString MyString::sub(int index, int len) const {
        MyString ret;
        if ((index >= 0) && (index < m_length) && (len >= 0)) {
            int length = (index + len > m_length) ? (m_length - index) : len;

            char *str = reinterpret_cast<char *>(malloc(length + 1));

            // strncpy(str, m_str+index, length);
            for (int i = 0; i < length; i++) {
                str[i] = m_str[i + index];
            }

            str[length] = '\0';

            ret = str;
        } else {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Paramter is invalid...");
        }
        return ret;
    }

    void MyString::init(const char *s) {
        m_str = strdup(s);
        if (m_str) {
            m_length = strlen(m_str);
        } else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create MyString Object");
        }
    }

    MyString::MyString() {
        init("");
    }

    MyString::MyString(char c) {
        char arr[] = {c, '\0'};
        init(arr);
    }

    MyString::MyString(const char *s) {
        init(s ? s : ""); //判断s是否为NULL
    }

    MyString::MyString(const MyString &s) {
        init(s.m_str);
    }

    int MyString::length() const {
        return m_length;
    }

    const char *MyString::str() const {
        return m_str;
    }

    bool MyString::equal(const char *startaddr, const char *str, int len) const //判断字符串中的部分子串是否相相等
    {
        bool ret = (str != NULL);
        for (int i = 0; i < len && ret; i++) {
            ret = ret && (startaddr[i] == str[i]);
        }
        return ret;
    }

    bool MyString::startWith(const char *s) const {
        bool ret = (s != NULL);

        if (ret) {
            int len = strlen(s);

            ret = (len < m_length) && equal(m_str, s, len);
        }
        return ret;
    }

    bool MyString::startWith(const MyString &s) const {
        return startWith(s.m_str);
    }

    bool MyString::endOf(const char *s) const {
        bool ret = (s != NULL);

        if (ret) {
            int len = strlen(s);

            char *str = m_str + (m_length - len); //指针偏移计算，定位到子串首地址

            ret = (len < m_length) && equal(str, s, len);
        }
        return ret;
    }

    bool MyString::endOf(const MyString &s) const {
        return endOf(s.m_str);
    }

    MyString &MyString::insert(int i, const char *s) {
        if ((i >= 0) && (i <= m_length)) {
            if ((s != NULL) && (s[0] != 0)) {
                int len = strlen(s);
                char *str = reinterpret_cast<char *>(malloc(m_length + len + 1));
                if (str != NULL) {
                    strncpy(str, m_str, i);
                    strncpy(str + i, s, len);
                    strncpy(str + i + len, m_str + i, m_length - i);

                    str[m_length + len + 1] = '\0';
                    free(m_str);
                    m_str = str;
                    m_length = m_length + len;
                } else {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory in MyString& MyString::insert(int i, const char* s)");
                }
            }
        } else {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter is invalid in MyString& MyString::insert(int i, const char* s)");
        }
        return *this;
    }

    MyString &MyString::insert(int i, const MyString &s) {
        return insert(i, s.m_str);
    }

    MyString &MyString::trim() {
        int b = 0;
        int e = m_length - 1;
        while (m_str[b] == ' ')
            b++;
        while (m_str[e] == ' ')
            e--;

        if (b == 0) {
            m_str[e + 1] = '\0';
            m_length = e + 1;
        } else {
            for (int i = 0, j = b; j <= e; i++, j++) {
                m_str[i] = m_str[j];
            }
            m_str[e - b + 1] = '\0';
            m_length = e - b + 1;
        }

        return (*this);
    }

    char &MyString::operator[](int i) {
        if ((i >= 0) && (i < m_length)) {
            return m_str[i];
        } else {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter is invalid in char& MyString::operator [](int i)");
        }
    }

    char MyString::operator[](int i) const {
        return (const_cast<MyString &>(*this))[i];
    }

    bool MyString::operator==(const MyString &s) const {
        return (strcmp(m_str, s.m_str) == 0);
    }

    bool MyString::operator==(const char *s) const {
        return (strcmp(m_str, s) == 0);
    }

    bool MyString::operator!=(const MyString &s) const {
        return !(*this == s);
    }

    bool MyString::operator!=(const char *s) const {
        return !(*this == s);
    }

    bool MyString::operator>(const MyString &s) const {
        return (strcmp(m_str, s.m_str) > 0);
    }

    bool MyString::operator>(const char *s) const {
        return (strcmp(m_str, s) > 0);
    }

    bool MyString::operator<(const MyString &s) const {
        return (strcmp(m_str, s.m_str) < 0);
    }

    bool MyString::operator<(const char *s) const {
        return (strcmp(m_str, s) < 0);
    }

    bool MyString::operator<=(const MyString &s) const {
        return (strcmp(m_str, s.m_str) <= 0);
    }

    bool MyString::operator<=(const char *s) const {
        return (strcmp(m_str, s) <= 0);
    }

    bool MyString::operator>=(const MyString &s) const {
        return (strcmp(m_str, s.m_str) >= 0);
    }

    bool MyString::operator>=(const char *s) const {
        return (strcmp(m_str, s) >= 0);
    }

    MyString MyString::operator+(const MyString &s) const {
        return (*this + s.m_str);
    }

    MyString MyString::operator+(const char *s) const {
        MyString ret;
        int len = m_length + strlen(s);
        char *str = reinterpret_cast<char *>(malloc(len + 1));
        if (str) {
            strcpy(str, m_str);
            strcat(str, s ? s : "");

            free(ret.m_str);

            ret.m_str = str;
            ret.m_length = len;
        } else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No Memory in operator +(const char* s)");
        }
        return ret;
    }

    MyString &MyString::operator+=(const MyString &s) {
        return (*this = *this + s);
    }

    MyString &MyString::operator+=(const char *s) {
        return (*this = *this + s);
    }

    MyString MyString::operator-(const MyString &s) const {
        return MyString(*this).remove(s);
    }

    MyString MyString::operator-(const char *s) const {
        return MyString(*this).remove(s);
    }

    MyString &MyString::operator-=(const MyString &s) {
        return remove(s);
    }

    MyString &MyString::operator-=(const char *s) {
        return remove(s);
    }

    MyString &MyString::operator=(const MyString &s) {
        return (*this = s.m_str);
    }

    MyString &MyString::operator=(const char *s) {
        if (m_str != s) {
            char *str = strdup(s);

            if (str) {
                free(m_str);
                m_str = str;
                m_length = strlen(m_str);
            } else {
                THROW_EXCEPTION(NoEnoughMemoryException, "NO memory in MyString& MyString::operator =(const char* s)const");
            }
        }
        return *this;
    }

    MyString &MyString::operator=(const char c) {
        char arr[] = {c, '\0'};
        return (*this = arr);
    }

    MyString::~MyString() {
        free(m_str);
    }
}
