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
int main(int argc,char* argv[]){
    try {
        if(argc!=2){
            std::cerr<<"Usage: client <host>"<<std::endl;
            return 1;
        }
        boost::asio::io_service io_s;
        tcp::resolver resolver(io_s);
        tcp::resolver::query query(argv[1],"9013");
            //构造一个询问对象，使用server的名字argv[1]和服务名字daytime
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
            //端点迭代器的类型是ip::tcp::resolver::iterator

            //现在可以连接socket了，上面的端点可能是ipv4和ipv6，因此我们需要尝试各种可能；
        tcp::socket socket(io_s);
        boost::asio::connect(socket,endpoint_iterator);
            //是client和特定的ip类型相分离，conenct自动做这件事情.

        for(;;){
            boost::array<char,128> buf;
            //使用boost array保持接受的数据
            boost::system::error_code error;

            size_t  len = socket.read_some(boost::asio::buffer(buf),error);
            //asio::buffer自动识别array的大小，来防止缓冲区溢出.
            //除了使用boost::array外，还可以使用char[]或者是std::vector来解决；


            //当server关闭连接时，read_some会退出，并且带有error::eof错误；
            //这样我们就能介绍循环了。
            if(error == boost::asio::error::eof){
                break;//server安全关闭连接
            }else if(error){
                throw boost::system::system_error(error);//some other error
            }
            std::cout.write(buf.data(),len);
            //输出数据
        }
    }catch (std::exception& e){
        std::cerr<<e.what()<<std::endl;
        //输出产生的任何异常
    }
    return 0;
}

