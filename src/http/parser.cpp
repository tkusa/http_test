#include <iostream>
#include <string>
#include <vector>
#include "parser.h"
#include "request.h"
#include "response.h"

using namespace std;
using namespace Http;

Request Parser::parse(string data)
{
    Request request;
    string request_data = data;
    string delimiter = "\r\n";
    int del_length = delimiter.length();
    vector<string> lines = {};

    while (int pos = request_data.find(delimiter) != string::npos) {
        string line = request_data.substr(0, pos);
        lines.emplace_back(line);

        request_data = request_data.substr(pos + del_length);
    }
    
    return request;
}

string Parser::build(Response response)
{
    string result = "";
    string first = response.version + " " + to_string(response.status) + "\r\n";
    result += first;
    for (pair<string, string> field : response.fields) {
        string header = field.first + ":" + field.second + "\r\n";
        result +=  header;
    }
    result += "\r\n";
    string body = response.body + "\r\n";
    result += body;
    result += "\r\n\r\n";
    return result;
}