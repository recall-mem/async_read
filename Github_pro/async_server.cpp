#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <istream>

using namespace boost;


void async_connect(asio::io_context& ios, asio::ip::tcp::acceptor& acceptor)
{

    auto socket = std::make_shared<asio::ip::tcp::socket>(ios);

    acceptor.async_accept(*socket , [&](system::error_code ec){

        if(!ec){

            std::cout << "client connected\n";

            asio::streambuf buffer;
            system::error_code ec;
            asio::read(*socket, buffer, asio::transfer_all(), ec);

            if(!ec)
            {
                std::istream is(&buffer);
                std::string line;
                while(getline(is,  line)){std::cout << line << std::endl;}
            }

            else
            {
                std::cerr << ec.message() << '\n';
            }

        }

        else{

            std::cerr << "error durning connect" << ec.message() << '\n';
        
        }

        async_connect(ios, acceptor);
    });

}

int main(){

    asio::io_context ios_;
    asio::ip::tcp::endpoint ep_(asio::ip::address_v4::any(), 5005);
    asio::ip::tcp::acceptor acceptor_(ios_, ep_);

    acceptor_.listen(asio::socket_base::max_listen_connections);
    std::thread worker([&ios_, &acceptor_]()
    {
        async_connect(ios_, acceptor_);
        ios_.run();
    });

    std::this_thread::sleep_for(std::chrono::seconds(300));

    return 0;
} 