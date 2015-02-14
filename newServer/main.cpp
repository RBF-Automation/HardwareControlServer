#include "Server.h"

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: server <port>\n";
            return 1;
        }

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
