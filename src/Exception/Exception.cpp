#include "Exception.h"
#include <cstring>
#include <malloc.h>
#include <cstdlib>

namespace DataStLib {
    void Exception::init(const char *message, const char *file, int line) {
        m_message = (message ? strdup(message) : NULL);    //传入的参数message可能存在于栈、或者全局数据区，会导致没有办法控制message所指向外部字符串的生命周期，
        //所以直接使用不安全，需要将字符串复制一份到堆空间

        if (file != NULL) {
            char sl[16] = {0};
            snprintf(sl, sizeof(sl), "%d", line);   //将行号转换为字符串格式，并存放在数组中
            //itoa(line, sl, 10);
            m_location = static_cast<char *>(malloc(
                    strlen(file) + strlen(sl) + 2));        //分配所需要的内存空间，+2是因为“ : ”和“ 字符串结束符 ”需要空间
            if (m_location != NULL) {
                m_location = strcpy(m_location, file);
                m_location = strcat(m_location, ":");    //字符串拼接,最终输出格式为 “文件名：行号”
                m_location = strcat(m_location, sl);
            }
        } else {
            m_location = NULL;
        }
    }

    Exception::Exception() {
        init(NULL, NULL, 0);
    }

    Exception::Exception(const char *message) {
        init(message, NULL, 0);
    }

    Exception::Exception(const char *file, int line) {
        init(NULL, file, line);

    }

    Exception::Exception(const char *message, const char *file, int line) {
        init(message, file, line);
    }

    Exception::Exception(const Exception &e) {
        m_message = strdup(e.m_message);
        m_location = strdup(e.m_location);
    }

    Exception &Exception::operator=(const Exception &e) {
        if (this != &e) {
            free(m_message);
            free(m_location);

            m_message = e.m_message;
            m_location = e.m_location;
        }
        return *this;
    }

    const char *Exception::message() const {
        if (m_message == NULL) {
            return "NULL";
        }
        return m_message;
    }

    const char *Exception::location() const {
        return m_location;
    }

    Exception::~Exception() {
        free(m_message);
        free(m_location);
    }

    void ExceptionTest(void) {
        try {
            //throw Exception("test",__FILE__,__LINE__);
            THROW_EXCEPTION(NullPointerException, "Test");  //不能使用NULL，可以使用“NULL” ，因为不能对NULL进行解引用
            //throw Exception(__FILE__,__LINE__);
        }

        catch (const ArithmeticException &e) {
            cout << " catch(const ArithmeticException& e)" << endl;
            cout << e.message() << endl;
            cout << e.location() << endl;
        }
        catch (const NullPointerException &e) {
            cout << " catch(const NullPointerException& e)" << endl;
            cout << e.message() << endl;
            cout << e.location() << endl;
        }
        catch (const Exception &e) {
            cout << " catch(const Exception& e)" << endl;
            cout << e.message() << endl;
            cout << e.location() << endl;
        }
        cout << "ExceptionTest  end" << endl;
    }
}


