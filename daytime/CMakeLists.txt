cmake_minimum_required(VERSION 3.6)
project(boost_All)

message(STATUS "start running cmake...")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
include_directories(./client_asio)
include_directories(./server_asio)

set(SOURCE_FILES server_asio/main.cpp)
add_executable(boost_All ${SOURCE_FILES})

set(Boost_INCLUDE_DIR /Users/lizhen/src_github/boost_1_65_1/)
set(Websocketpp_INCLUDE_DIR /Users/lizhen/src_github/websocketpp)
#set(boost_LIBRARIES /Users/lizhen/src_github/boost_1_65_1/stage/lib)
set(Boost_COMPONENTS Thread Filesystem Regex Serialization Signals System Timer REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIS_RUNTIME OFF)

find_package(Boost COMPONENTS ${Boost_COMPONENTS})
if (Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    message(STATUS "websocketpp: ${Websocketpp_INCLUDE_DIR}")
    include_directories(${Boost_INCLUDE_DIR})
    include_directories(${Websocketpp_INCLUDE_DIR})
    target_link_libraries(boost_All ${Boost_LIBRARIES})
endif()

