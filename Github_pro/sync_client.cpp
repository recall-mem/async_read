#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>

using namespace boost;


int main(){

    using tcp = asio::ip::tcp;

    asio::io_context ios_;
    tcp::endpoint ep(asio::ip::address_v4::from_string("127.0.0.1"), 5005);
    tcp::socket socket(ios_);
    system::error_code ec;

    socket.connect(ep, ec);
    
    if(ec)
    {
       std::cerr << ec.message() << std::endl; 
    }
    else
    {
        std::cout << "connected" << std::endl;

        const char* data = "hello server";

        asio::write(socket, asio::buffer(data, 13), ec);
    }


    std::this_thread::sleep_for(std::chrono::seconds(20));

    return 0;
}