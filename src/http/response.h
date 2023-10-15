#include <iostream>
#include <map>

using namespace std;

#ifndef RESPONSE_H
#define RESPONSE_H

namespace Http
{

    class Response 
    {
        public:
            string version;
            int status;
            map<string, string> fields;
            string body;

    };
}

#endif
