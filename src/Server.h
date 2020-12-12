//
// Created by misha on 11/12/2020.
//

#ifndef DB_SERVER_H
#define DB_SERVER_H

#include "cpprest/http_listener.h"
#include "cpprest/asyncrt_utils.h"
#include "cpprest/json.h"
#include "cpprest/uri.h"
#include "Connection.h"

using namespace web::http;
using namespace utility;
using namespace web;
using namespace http::experimental::listener;

namespace CustomClasses {
    class Server {
    public:
        Server(std::vector<DataBase*> *, DataBase*, IdComponent*);

        CustomClasses::Connection *connection;

    private:
        void handlePost(http_request request);

        http_listener m_listener;
    };
}


#endif //DB_SERVER_H
