#include "stdafx.h"

#include "media.h"
#include "rtp_packet.h"
#include "rtcp_packet.h"
#include <boost\bind.hpp>
#include <random>
#include <Windows.h>

enum RtcpPayloadTypes
{
    SenderReport = 200
};

namespace media
{
    uint64_t get_ntp_time()
    {
        FILETIME ft, ntp_ft;
        SYSTEMTIME ntp_epoch;

        ntp_epoch.wDay = 1;
        ntp_epoch.wHour = 0;
        ntp_epoch.wMilliseconds = 0;
        ntp_epoch.wMinute = 0;
        ntp_epoch.wMonth = 1;
        ntp_epoch.wSecond = 0;
        ntp_epoch.wYear = 1900;

        ::GetSystemTimeAsFileTime(&ft);
        ::SystemTimeToFileTime(&ntp_epoch, &ntp_ft);

        ULARGE_INTEGER li;
        li.LowPart = ft.dwLowDateTime - ntp_ft.dwLowDateTime;
        li.HighPart = ft.dwHighDateTime - ntp_ft.dwHighDateTime;

        return 
            ((li.QuadPart / 10000000) << 32) |
            ((li.QuadPart % 10000000) * ULONG_MAX) / 10000000;
    }

    std::default_random_engine engine((unsigned long)get_ntp_time());
    std::uniform_int_distribution<uint32_t> dist;

    uint32_t rand32()
    {
        return dist(engine);
    }
}