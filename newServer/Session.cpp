// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include "Session.h"

Session::Session(boost::asio::io_service& io_service) : mSocket(io_service){}

tcp::socket& Session::socket() {
    return mSocket;
}

void Session::start() {
    mSocket.async_read_some(boost::asio::buffer(mData, max_length), boost::bind(&Session::handleRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Session::handleRead(const boost::system::error_code& error, size_t bytes_transferred) {
    if (!error) {

        //Do stuff with data here

        std::cout << mSocket.remote_endpoint().address().to_string() << std::endl;
        std::cout << mData << std::endl;

        //Writes data back!
        boost::asio::async_write(mSocket, boost::asio::buffer(mData, bytes_transferred), boost::bind(&Session::handleWrite, this, boost::asio::placeholders::error));
    } else {
        delete this;
    }
}

void Session::handleWrite(const boost::system::error_code& error) {
    if (!error) {
        mSocket.async_read_some(boost::asio::buffer(mData, max_length),
        boost::bind(&Session::handleRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    } else {
        delete this;
    }
}
