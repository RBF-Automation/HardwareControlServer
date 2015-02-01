#include "Server.h"
#include "ServerSocket.h"
#include "SocketException.h"
#include "JsonControl.h"
#include <stdint.h>
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <mutex>

std::mutex NodeAccessMutex;


struct thread_data
{
  int  thread_id;
  char *message;
};

Server::Server()
{
  RunServer();
}


void dataHandlerThread(std::string data)
{
  const char * c = data.c_str();
  JsonControl jsn;
  jsn.DecodeJsonObject(c);
  //std::cout << data << std::endl;

  NodeAccessMutex.lock();
  //execute node code here
  NodeAccessMutex.unlock();

  /*
  char dataCompare[1024] = "testCompare";
  if(strcmp (data,dataCompare) == 0)
{
std::cout << data << std::endl;
}
*/
}

void newServerThread()
{
  std::cout << "running....\n";
  system("fuser 30000/tcp -k");

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

            new_sock >> data;
            std::thread t2(dataHandlerThread, data);
            //new_sock << data;

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
