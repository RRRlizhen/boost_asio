#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <algorithm>
#include <boost/function.hpp>
#include <cstdlib>
#include <cstring>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
using namespace std;
using boost::asio::ip::tcp;

std::string make_daytime_string(){
    using namespace std;//for time_t,time and ctime;
    time_t now = time(0);//now = 1506337163
    return ctime(&now);//Mon Sep 25 18:59:23 2017
}

int main(){
    try {
        boost::asio::io_service ios;
        tcp::acceptor acceptor(ios,tcp::endpoint(tcp::v4(),9013));
        //ip::tcp::acceptor对象，用来监听多个连接
        //tcp的13号端口，ipv4

        for(;;){//永久循环，意味着它能一次处理一个连接
            tcp::socket socket(ios);
            acceptor.accept(socket);//接受连接

            std::string message = make_daytime_string();//获取daytime

            boost::system::error_code ignored_error;
            boost::asio::write(socket,boost::asio::buffer(message),ignored_error);
            //传输到client所对应的socket连接上去
        }
    }catch (std::exception &e){
        std::cerr<<e.what()<<std::endl;
    }
    return 0;
}
