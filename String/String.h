#ifndef STRING_H
#define STRING_H

#include "Object/Object.h"

namespace DataStLib
{
class String : public Object
{
protected:
    char* m_str;
    int m_length;
    void init(const char* s);
    bool equal(const char* startaddr, const char* str, int len)const; //��1���Ƚϵ���ʼλ�ã���2����Ҫ�Ƚϵ��Ӵ�����3���Ӵ�����    
	static int *MakePmtTable(const char *s);
	static int KMP(const char* s, const char* p);
public:
    String();
    String(char c);
    String(const char* s);
    String(const String& s);

	int indexOf(const char *s)const;
	int indexOf(const String& s)const;

	String& remove(int index, int len);
	String& remove(const char* s);
	String& remove(const String& s);

	String& replace(const char* t, const char* s);
	String& replace(const String& t, const char* s);
	String& replace(const char* t, const String& s);
	String& replace(const String& t, const String& s);

	String sub(int index, int len)const;
	
    int length()const;
    const char* str()const;  //������c�ַ�ת����ת��

    bool startWith(const char* s)const;
    bool startWith(const String& s)const;
    bool endOf(const char* s)const;
    bool endOf(const String& s)const;
    String& insert(int i, const char* s);
    String& insert(int i, const String& s);
    String& trim(); //ɾ���ַ���ǰ��Ŀո�

    char& operator [](int i);
    char operator [](int i)const;
    bool operator == (const String& s)const;
    bool operator == (const char* s)const;
    bool operator != (const String& s)const;
    bool operator != (const char* s)const;
    bool operator > (const String& s)const;
    bool operator > (const char* s)const;
    bool operator < (const String& s)const;
    bool operator < (const char* s)const;
    bool operator <= (const String& s)const;
    bool operator <= (const char* s)const;
    bool operator >= (const String& s)const;
    bool operator >= (const char* s)const;
	
	//+ -����ı��������+= -=��ı��������
    String operator +(const String& s)const;
    String operator +(const char* s)const;
    String& operator +=(const String& s);
    String& operator +=(const char* s);

    String operator -(const String& s)const;
    String operator -(const char* s)const;
    String& operator -=(const String& s);
    String& operator -=(const char* s);

    String& operator =(const String& s);
    String& operator =(const char* s);
    String& operator =(const char c);

    ~String();
};
}

#endif // STRING_H
