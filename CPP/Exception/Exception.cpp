#include "Exception.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>

namespace ds
{
    void Exception::init(const char* messge, const char* file, int line)
    {
        m_message = (messge ? strdup(messge) : NULL);
        if (file != NULL)
        {
            char sl[16] = { 0 };

            snprintf(sl, sizeof(sl), "%d", line);
            m_location = static_cast<char*>(malloc(strlen(file) + strlen(sl) + 2));

            if (m_location != NULL)
            {
                strcpy(m_location,file);
                strcat(m_location, ":");
                strcat(m_location,  sl);
            }
        }
        else
        {
            m_location = NULL;
        }
    }

    Exception::Exception(const char* message)
    {
        init(message, NULL, 0);
    }
    Exception::Exception(const char* file, int line)
    {
        init(NULL, file, line);
    }
    Exception::Exception(const char* messge, const char* file, int line)
    {
        init(messge, file, line);
    }

    Exception::Exception(const Exception& e)
    {
        m_message = strdup(e.m_message);
        m_location = strdup(e.m_location);
    }
    Exception& Exception::operator= (const Exception& e)
    {
        if (this != &e)
        {
            free(m_message);
            free(m_location);
            m_message = strdup(e.m_message);
            m_location = strdup(e.m_location);
        }
        return *this;
    }

    const char* Exception::message()const
    {
        return m_message;
    }
    const char* Exception::location()const
    {
        return m_location;
    }

    Exception::~Exception()
    {
        free(m_message);
        free(m_location);
    }
}
