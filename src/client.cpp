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

int main(int argc, char *argv[]) {
  string prog = argv[0];
  if (argc != 2) {
    cout << "(!) usage: " + prog + " <url>" << endl;
    exit(0);
  }
  string url = argv[1];

  Socket socket;
  Parser parser;
  Request request = parser.parseUrl(url);
  request.version = "HTTP/1.1";

  string request_data = parser.build(request);

  cout << "----- Request ------" << endl;
  cout << request_data << endl;
  cout << "--------------------" << endl;

  int port;
  if (request.schema == "http") {
    port = 80;
  } else {
    cout << "(!) Not implemented." << endl;
    exit(0);
  }

  char host[1024] = {0};
  request.host.copy(host, request.host.length());
  int server = socket.create(host, port);
  socket.deliver(request_data);

  string data = socket.receive();
  cout << "----- Response ------" << endl;
  cout << data << endl;
  cout << "--------------------" << endl;

}