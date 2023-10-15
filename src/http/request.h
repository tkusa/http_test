#include <iostream>
#include <map>

using namespace std;

#ifndef REQUEST_H
#define REQUEST_H

namespace Http
{

    class Request 
    {
        public:
            string version;
            string method;
            string target;
            map<string, string> fields;
            string body;

    };
}

#endif
