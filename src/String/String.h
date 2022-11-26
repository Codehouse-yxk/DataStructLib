#ifndef STRING_H
#define STRING_H

#include "Object.h"

namespace DataStLib
{
    class String : public Object
    {
    public:
        String();

        String(char c);

        String(const char *s);

        String(const String &s);

        int indexOf(const char *s) const;

        int indexOf(const String &s) const;

        String &remove(int index, int len);

        String &remove(const char *s);

        String &remove(const String &s);

        String &replace(const char *t, const char *s);

        String &replace(const String &t, const char *s);

        String &replace(const char *t, const String &s);

        String &replace(const String &t, const String &s);

        String sub(int index, int len) const;

        int length() const;

        const char *str() const; //用来和c字符转进行转换

        bool startWith(const char *s) const;

        bool startWith(const String &s) const;

        bool endOf(const char *s) const;

        bool endOf(const String &s) const;

        String &insert(int i, const char *s);

        String &insert(int i, const String &s);

        String &trim(); //删除字符串前后的空格

        char &operator[](int i);

        char operator[](int i) const;

        bool operator==(const String &s) const;

        bool operator==(const char *s) const;

        bool operator!=(const String &s) const;

        bool operator!=(const char *s) const;

        bool operator>(const String &s) const;

        bool operator>(const char *s) const;

        bool operator<(const String &s) const;

        bool operator<(const char *s) const;

        bool operator<=(const String &s) const;

        bool operator<=(const char *s) const;

        bool operator>=(const String &s) const;

        bool operator>=(const char *s) const;

        //+ -不会改变对象自身，+= -=会改变对象自身
        String operator+(const String &s) const;

        String operator+(const char *s) const;

        String &operator+=(const String &s);

        String &operator+=(const char *s);

        String operator-(const String &s) const;

        String operator-(const char *s) const;

        String &operator-=(const String &s);

        String &operator-=(const char *s);

        String &operator=(const String &s);

        String &operator=(const char *s);

        String &operator=(const char c);

        ~String();

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

#endif // STRING_H
