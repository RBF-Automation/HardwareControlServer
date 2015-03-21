#include "Server.h"

std::string sysOut;
char sysOutBuff[100];

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: server <port>\n";
            return 1;
        }
        sysOut = std::string("fuser ") + argv[1] + "/tcp -k";
        strcpy(sysOutBuff, sysOut.c_str());
        std::cout << "running....\n";
        system(sysOutBuff);
        boost::asio::io_service ioService;
        Server s(ioService, std::atoi(argv[1]));
        ioService.run();

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
