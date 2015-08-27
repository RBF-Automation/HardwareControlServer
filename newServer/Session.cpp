// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include "Session.h"
#include "JsonControl.h"
#include "SwitchDataPacket.h"
#include "MultiSwitchDataPacket.h"
#include "Actions.h"

#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/prettywriter.h"  // for stringify JSON
#include "rapidjson/include/rapidjson/filestream.h"  // wrapper of C stream for prettywriter as output
#include "rapidjson/include/rapidjson/writer.h"
#include "rapidjson/include/rapidjson/stringbuffer.h"
//#inlcude "rapidjson/include/rapidjson/allocators.h"
//#include "rapidjson/include/rapidjson/encodings.h"
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
        MultiSwitchDataPacket multiSwitchData;
        //const char * c = mData.c_str();
        //JsonControl jsn;
        //jsn.DecodeJsonObject(c);
        //std::cout << mData << std::endl;
        rapidjson::Document doc;
        doc.Parse(mData);
        uint64_t nodeID;
        uint32_t action;

        bool nodeID_Test = doc.HasMember("nodeid");
        bool action_Test = doc.HasMember("action");


    if(nodeID_Test != 0 )
    {
      nodeID = doc["nodeid"].GetUint64();
    }
    else
    {
      nodeID = 0;
    }
        //std::cout << nodeID << std::endl;
        node_m.SetWritingPipe(nodeID);

    if(action_Test != 0)
    {
      action = doc["action"].GetUint();
    }
    else
    {
      action = 0;
    }


        switch ( action )
        {
          case Actions::SWITCH:

            packet.state = doc["state"].GetUint();

            NodeAccessMutex.lock();
            node_m.WriteData(&packet,sizeof(packet)) != true;
            NodeAccessMutex.unlock();

          break;

          case Actions::MULTI_SWITCH:

            multiSwitchData.state = doc["state"].GetUint();

            multiSwitchData.outletNum = doc["switchNum"].GetUint();

            NodeAccessMutex.lock();
            node_m.WriteData(&multiSwitchData,sizeof(multiSwitchData)) != true;
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
