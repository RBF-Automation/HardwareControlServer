// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include "Server.h"


Server::Server(boost::asio::io_service& io_service, short port) : mIoService(io_service), mAcceptor(io_service, tcp::endpoint(tcp::v4(), port)) {
    startAccept();
}

void Server::startAccept() {
    Session* newSession = new Session(mIoService);
    mAcceptor.async_accept(newSession->socket(), boost::bind(&Server::handleAccept, this, newSession, boost::asio::placeholders::error));
}

void Server::handleAccept(Session* newSession, const boost::system::error_code& error) {
    if (!error) {
        newSession->start();
    } else {
        delete newSession;
    }

    startAccept();
}
