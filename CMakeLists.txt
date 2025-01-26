cmake_minimum_required(VERSION 3.10)
project(firstServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS system)

set(SOURCES 
src/main.cpp
src/Session.cpp
src/Server.cpp
)

add_executable(firstServer ${SOURCES})

target_include_directories(firstServer PUBLIC include)

target_link_libraries(firstServer PRIVATE Boost::system)