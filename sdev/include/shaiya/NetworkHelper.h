#pragma once

namespace shaiya
{
    struct CUser;

    class NetworkHelper
    {
    public:

        static void Send(CUser* user, void* packet, int length);
        static void SendDBAgent(void* packet, int length);
        static void SendGameLog(void* packet, int length);
        static void SendSession(void* packet, int length);
        static void SendUserLog(void* packet, int length);
    };
}
