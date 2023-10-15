#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>

#include "socket.h"

using namespace std;
using namespace Connection;


int Socket::create(char* ip_addr, int port) {
    this->sock = 0;
    struct sockaddr_in address;

    if (( this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "Socket creation error\n" << endl;
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if (inet_pton(AF_INET, ip_addr, &address.sin_addr) <= 0) {
        cout << "Invalid address/ Address not supoprted \n" << endl;
        return -1;
    }

    if ((this->connection_fd = connect(this->sock, (struct sockaddr*)&address, sizeof(address))) < 0) {
        cout << "Connection failed \n" << endl;
        return -1;
    }

    return this->sock;
}


int Socket::serve(int port) {
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int opt = 1;
    
    if ((this->connection_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "Socket creation error\n" << endl;
        return -1;
    }

    if (setsockopt(this->connection_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        cout << "setsockopt error" << endl;
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(this->connection_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        cout << "bind error" << endl;
        return -1;
    }

    if (listen(this->connection_fd, 3) < 0) {
        cout << "listen error" << endl;
        return -1;
    }

    if ((sock = accept(this->connection_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        cout << "accept error" << endl;
        return -1;
    }

    return this->sock;
}

void Socket::deliver(string data) {
    send(this->sock, data.c_str(), data.length(), 0);
}

string Socket::receive() {
    read(this->sock, this->buffer, 8196);
    string str = this->buffer;
    return str;
}

int Socket::finish() {
    close(this->sock);
    shutdown(connection_fd, SHUT_RDWR);
    return 0;
}

