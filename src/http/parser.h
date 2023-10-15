#include <iostream>
#include <map>
#include "request.h"
#include "response.h"

using namespace std;
using namespace Http;

#ifndef PARSER_H
#define PARSER_H

namespace Http
{
    class Parser 
        {
            public:
                Request parse(string data);
                string build(Response response);

        };
}

#endif