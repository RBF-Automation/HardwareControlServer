// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "NodeHandler.h"

using boost::asio::ip::tcp;

class Session
{

    private:
        tcp::socket mSocket; //socket_
        enum { max_length = 1048 };
        char mData[max_length]; //data_
        NodeHandler node_m;

    public:
        Session(boost::asio::io_service& io_service, NodeHandler node);

        tcp::socket& socket();

        void start();

    private:
        void handleRead(const boost::system::error_code& error, size_t bytes_transferred);

        void handleWrite(const boost::system::error_code& error);

};
