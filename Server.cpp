#include "Server.h"
#include "ServerSocket.h"
#include "SocketException.h"
#include "JsonControl.h"
#include "NodeHandler.h"
#include "Actions.h"
#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/writer.h"
#include "rapidjson/include/rapidjson/stringbuffer.h"
#include <stdint.h>
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <mutex>

NodeHandler node;


Server::Server()
{
  RunServer();
}


void dataHandlerThread(std::string data)
{
  SwitchDataPacket packet;
  const char * c = data.c_str();
  //JsonControl jsn;
  //jsn.DecodeJsonObject(c);

  rapidjson::Document doc;
  doc.Parse(c);
  //std::cout << doc["action"].GetInt() << std::endl;

  switch ( doc["action"].GetUint() )
  {
    case Actions::SWITCH:
      packet.state = doc["state"].GetUint();
      while(node.WriteData(&packet,sizeof(packet)) != true)
      {

      }

    break;
    default:
    // Code
    break;
  }
  //std::cout << data << std::endl;


}

void newServerThread()
{

  std::cout << "running....\n";
  system("fuser 30000/tcp -k");

  node.InitRadio();

  for(;;)
  {

    try
    {
      // Create the socket
      ServerSocket server ( 30000 );

      while ( true )
      {
        ServerSocket new_sock;
        server.accept ( new_sock );

        try
        {
          while ( true )
          {
            std::string data;
            std::string send = "{\"sent\":true}";

            new_sock >> data;
            //new_sock << send;
            std::thread t2(dataHandlerThread, data);

            t2.detach();
          }
        }
        catch ( SocketException& ) {}
      }
    }
    catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
  }
}



void Server::RunServer()
{
  std::thread t1(newServerThread);

  t1.detach();
}

Server::~Server()
{

}
