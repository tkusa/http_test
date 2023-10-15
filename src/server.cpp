#include <iostream>
#include "connection/socket.h"
#include "http/parser.h"
#include "http/request.h"
#include "http/response.h"

using namespace std;
using namespace Connection;
using namespace Http;

int main() {
    
    Parser parser;
    cout << "Start simple HTTP Server" << endl;
    while (true) {
        Socket socket;
        socket.serve(80);

        string data = socket.receive();
        cout << "----- Request ------" << endl;
        cout << data << endl;
        cout << "--------------------" << endl;

        Request request = parser.parse(data);
        Response response;
        response.version = "HTTP/1.1";
        response.status = 200;
        response.fields["Content-Length"] = "13";
        response.body = "Hello World";
        string result = parser.build(response);
        cout << "----- Response -----" << endl;
        cout << result << endl;
        cout << "--------------------" << endl;
        
        socket.deliver(result);
        socket.finish();
    }
    cout << "Stop" << endl;
}

