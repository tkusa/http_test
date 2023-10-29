#include <iostream>
#include <string>
#include <vector>
#include "parser.h"
#include "request.h"
#include "response.h"

using namespace std;
using namespace Http;

Request Parser::parseUrl(string url)
{
    Request request;
    string url_buf = url;
    string scheme_sep = "://";
    string slash = "/";
    int pos = url_buf.find(scheme_sep);
    request.schema = url_buf.substr(0, pos);
    url_buf = url_buf.substr(pos + scheme_sep.length());
    int host_pos = url_buf.find(slash);
    request.host = url_buf.substr(0, host_pos);
    request.fields["Host"] = url_buf.substr(0, host_pos);
    request.target = url_buf.substr(host_pos);
    request.method = "GET";

    return request;
}


Request Parser::parse(string data)
{
    Request request;
    string request_data = data;
    string crlf = "\r\n";
    string space = " ";
    string header_sep = ": ";
    int crlf_len = crlf.length();
    int space_len = space.length();
    int sep_len = header_sep.length();
    vector<string> headers = {};
    int pos = request_data.find(crlf);

    while (pos != string::npos) {
        if (pos == 0) {
            request.body = request_data.substr(crlf_len);
            break;
        }
        string line = request_data.substr(0, pos);
        headers.emplace_back(line);
        request_data = request_data.substr(pos + crlf_len);
        pos = request_data.find(crlf);
    }

    string start_line = headers[0];
    int method_pos = start_line.find(space);
    request.method = start_line.substr(0, method_pos);
    start_line = start_line.substr(method_pos + space_len);
    int target_pos = start_line.find(space);
    request.target = start_line.substr(0, target_pos);
    request.version = start_line.substr(target_pos + space_len);

    for (int i = 1; i < headers.size(); i++) {
        string header = headers[i];
        int sep_pos = header.find(header_sep);
        string left = header.substr(0, sep_pos);
        string right = header.substr(sep_pos + sep_len);
        request.fields[left] = right;
    }
    return request;
}

string Parser::build(Request request)
{
    string result = "";
    string first = request.method + " " + request.target + " " + request.version + "\r\n";
    result += first;
    for (pair<string, string> field : request.fields) {
        string header = field.first + ": " + field.second + "\r\n";
        result +=  header;
    }
    result += "\r\n";
    if (request.body != "") {
        string body = request.body + "\r\n";
        result += body;
        result += "\r\n\r\n";
    }
    
    return result;
}

string Parser::build(Response response)
{
    string result = "";
    string first = response.version + " " + to_string(response.status) + "\r\n";
    result += first;
    for (pair<string, string> field : response.fields) {
        string header = field.first + ": " + field.second + "\r\n";
        result +=  header;
    }
    result += "\r\n";
    string body = response.body + "\r\n";
    result += body;
    result += "\r\n\r\n";
    return result;
}
