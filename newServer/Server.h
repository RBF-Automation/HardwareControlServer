// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "Session.h"
#include "NodeHandler.h"

using boost::asio::ip::tcp;

class Server
{
    private:
        boost::asio::io_service& mIoService;
        tcp::acceptor mAcceptor;

    public:
        Server(boost::asio::io_service& io_service, short port);

    private:

        void startAccept();
        void handleAccept(Session* newSession, const boost::system::error_code& error);
};
