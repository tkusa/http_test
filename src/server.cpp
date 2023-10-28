#include <iostream>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "connection/socket.h"
#include "http/parser.h"
#include "http/request.h"
#include "http/response.h"

using namespace std;
using namespace std::filesystem;
using namespace Connection;
using namespace Http;

int main() {
    string document_root = "./html";
    string default_document = "index.html";
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
        string document = request.target;
        if (document == "/") {
            document += default_document;
        }

        
        Response response;
        response.version = "HTTP/1.1";
        response.status = 200;
        response.fields["Host"] = request.fields["Host"];

        string path = document_root + document;
        if (exists(path)) {
            ifstream reading_file;
            reading_file.open(path, ios::in);
            string reading_line_buffer;
            while(getline(reading_file, reading_line_buffer)){
                response.body += reading_line_buffer + "\r\n";
            }
        } else {
            response.status = 404;
            response.body = "404 Not Found";
        }

        response.fields["Content-Length"] = to_string(response.body.length());
        string result = parser.build(response);
        cout << "----- Response -----" << endl;
        cout << result << endl;
        cout << "--------------------" << endl;
        
        socket.deliver(result);
        socket.finish();
    }
    cout << "Stop" << endl;
}

