// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include "Session.h"
#include "JsonControl.h"
#include "Actions.h"
#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/writer.h"
#include "rapidjson/include/rapidjson/stringbuffer.h"
#include <stdint.h>
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <mutex>

std::mutex NodeAccessMutex;

Session::Session(boost::asio::io_service& io_service, NodeHandler node) : mSocket(io_service)
{
  node_m = node;
}

tcp::socket& Session::socket()
{
    return mSocket;
}

void Session::start()
{
    mSocket.async_read_some(boost::asio::buffer(mData, max_length), boost::bind(&Session::handleRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Session::handleRead(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
      if(mSocket.remote_endpoint().address().to_string() == "127.0.0.1") // only listen to local host
      {
        SwitchDataPacket packet;
        //const char * c = mData.c_str();
        //JsonControl jsn;
        //jsn.DecodeJsonObject(c);

        rapidjson::Document doc;
        doc.Parse(mData);

        uint64_t x = doc["nodeid"].GetUint64();
        std::cout << x << std::endl;
        node_m.SetWritingPipe(x);

        switch ( doc["action"].GetUint() )
        {
          case Actions::SWITCH:

          packet.state = doc["state"].GetUint();

          NodeAccessMutex.lock();
          node_m.WriteData(&packet,sizeof(packet)) != true;
          NodeAccessMutex.unlock();

          break;
          default:
          // Code
          break;
        }
      }

        //std::cout << mSocket.remote_endpoint().address().to_string() << std::endl;

        //std::cout << mData << std::endl;

        //Writes data back!
        //boost::asio::async_write(mSocket, boost::asio::buffer(mData, bytes_transferred), boost::bind(&Session::handleWrite, this, boost::asio::placeholders::error));
    }
    else
    {
        delete this;
    }
}

void Session::handleWrite(const boost::system::error_code& error)
{
    if (!error)
    {
        mSocket.async_read_some(boost::asio::buffer(mData, max_length),
        boost::bind(&Session::handleRead, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        delete this;
    }
}
