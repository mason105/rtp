
#include <stdarg.h>
#include <stdio.h>
#include <Windows.h>
#include "log.h"

namespace media
{
    void log_msg(const char* format, ...)
    {
        char buffer[512];

        va_list args;
        va_start(args, format);

        vsnprintf_s(buffer, _TRUNCATE, format, args);

        va_end(args);

        SYSTEMTIME st;
        ::GetLocalTime(&st);

        printf("%02d:%02d:%02d.%03d: %s", 
            st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, buffer);
    }
}