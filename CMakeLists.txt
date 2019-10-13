cmake_minimum_required(VERSION 3.14)
project(unix_shell)

set(CMAKE_CXX_STANDARD 14)

add_executable(unix_shell
        main.cpp
        sys/kill.cpp
#        sys/ping.cpp
#        sys/ifconfig.cpp
        simple/Simple.cpp
        simple/Simple.h
        admin/Admin.h
        admin/Admin.cpp
#        sys/ping.h
#        sys/ifconfig.h
        sys/kill.h
        )