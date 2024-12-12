cmake_minimum_required(VERSION 3.30)
project(FTPClient_libcurl)

set(CMAKE_CXX_STANDARD 17)

add_executable(${CMAKE_PROJECT_NAME}
        FTP.cpp
        FtpManage.cpp
        FtpManage.h)

find_package(CURL REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE CURL::libcurl)