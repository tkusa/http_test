#include <iostream>

using namespace std;

#ifndef SOCKET_H
#define SOCKET_H

namespace Connection
{

    class Socket 
    {
        public:
            int sock;
            int connection_fd;
            char buffer[8196] = { 0 };
            int create(char* ip_addr,  int port);
            int serve(int port);
            void deliver(string data);
            string receive();
            int finish();
    };
}

#endif
