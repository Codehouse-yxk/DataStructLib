#include "Exception.h"
#include <cstring>
#include <malloc.h>
#include <cstdlib>

namespace DataStLib
{
void Exception::init(const char* message, const char* file, int line)
{
    m_message = (message ? strdup(message) : NULL);    //����Ĳ���message���ܴ�����ջ������ȫ�����������ᵼ��û�а취����message��ָ���ⲿ�ַ������������ڣ�
    													//����ֱ��ʹ�ò���ȫ����Ҫ���ַ�������һ�ݵ��ѿռ�

    if(file != NULL)
    {
        char sl[16] = {0};
        itoa(line, sl, 10);		//���к�ת��Ϊ�ַ�����ʽ���������������
        m_location = static_cast<char*>(malloc(strlen(file) + strlen(sl) + 2));		//��������Ҫ���ڴ�ռ䣬+2����Ϊ�� : ���͡� �ַ��������� ����Ҫ�ռ�
		if(m_location != NULL)
		{
			m_location = strcpy(m_location,file);
			m_location = strcat(m_location,":");	//�ַ���ƴ��,���������ʽΪ ���ļ������кš�
			m_location = strcat(m_location,sl);
		}
    }
    else
    {
        m_location = NULL;
    }
}
Exception::Exception()
{
    init(NULL,NULL,0);
}

Exception::Exception(const char* message)
{
    init(message,NULL,0);
}

Exception::Exception(const char* file, int line)
{
    init(NULL,file,line);

}

Exception::Exception(const char* message, const char* file, int line)
{
    init(message,file,line);

}

Exception::Exception(const Exception& e)
{
    m_message = strdup(e.m_message);
    m_location = strdup(e.m_location);
}

Exception& Exception::operator= (const Exception& e)
{
    if(this != &e)
    {
        free(m_message);
        free(m_location);

        m_message = e.m_message;
        m_location = e.m_location;
    }
    return *this;
}

const char* Exception::message() const
{
    if(m_message == NULL)
    {
         return "NULL";
    }
    return m_message;
}
const char* Exception::location() const
{
    return m_location;
}
Exception::~Exception()
{
    free (m_message);
    free (m_location);
}
void ExceptionTest(void)
{
    try
    {
        //throw Exception("test",__FILE__,__LINE__);
        THROW_EXCEPTION(NullPointerException,"Test");  //����ʹ��NULL������ʹ�á�NULL�� ����Ϊ���ܶ�NULL���н�����
        //throw Exception(__FILE__,__LINE__);
    }

    catch(const ArithmeticException& e)
    {
        cout << " catch(const ArithmeticException& e)" << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }
    catch(const NullPointerException& e)
    {
        cout << " catch(const NullPointerException& e)" << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }
    catch(const Exception& e)
    {
        cout << " catch(const Exception& e)" << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }
    cout << "ExceptionTest  end" << endl;
}
}


