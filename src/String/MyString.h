#ifndef MY_STRING_H
#define MY_STRING_H

#include "Object.h"

namespace DataStLib
{
    class MyString : public Object
    {
    public:
        MyString();

        MyString(char c);

        MyString(const char *s);

        MyString(const MyString &s);

        int indexOf(const char *s) const;

        int indexOf(const MyString &s) const;

        MyString &remove(int index, int len);

        MyString &remove(const char *s);

        MyString &remove(const MyString &s);

        MyString &replace(const char *t, const char *s);

        MyString &replace(const MyString &t, const char *s);

        MyString &replace(const char *t, const MyString &s);

        MyString &replace(const MyString &t, const MyString &s);

        MyString sub(int index, int len) const;

        int length() const;

        const char *str() const; //用来和c字符转进行转换

        bool startWith(const char *s) const;

        bool startWith(const MyString &s) const;

        bool endOf(const char *s) const;

        bool endOf(const MyString &s) const;

        MyString &insert(int i, const char *s);

        MyString &insert(int i, const MyString &s);

        MyString &trim(); //删除字符串前后的空格

        char &operator[](int i);

        char operator[](int i) const;

        bool operator==(const MyString &s) const;

        bool operator==(const char *s) const;

        bool operator!=(const MyString &s) const;

        bool operator!=(const char *s) const;

        bool operator>(const MyString &s) const;

        bool operator>(const char *s) const;

        bool operator<(const MyString &s) const;

        bool operator<(const char *s) const;

        bool operator<=(const MyString &s) const;

        bool operator<=(const char *s) const;

        bool operator>=(const MyString &s) const;

        bool operator>=(const char *s) const;

        //+ -不会改变对象自身，+= -=会改变对象自身
        MyString operator+(const MyString &s) const;

        MyString operator+(const char *s) const;

        MyString &operator+=(const MyString &s);

        MyString &operator+=(const char *s);

        MyString operator-(const MyString &s) const;

        MyString operator-(const char *s) const;

        MyString &operator-=(const MyString &s);

        MyString &operator-=(const char *s);

        MyString &operator=(const MyString &s);

        MyString &operator=(const char *s);

        MyString &operator=(const char c);

        ~MyString();

    protected:
        void init(const char *s);

        bool equal(const char *startaddr, const char *str, int len) const; //参1：比较点起始位置，参2：需要比较的子串，参3：子串长度

        static int *MakePmtTable(const char *s);

        static int KMP(const char *s, const char *p);

    protected:
        char *m_str;

        int m_length;
    };
}

#endif // MY_STRING_H
