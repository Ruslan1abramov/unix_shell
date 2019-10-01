cmake_minimum_required(VERSION 3.15)
project(unix_shell)

set(CMAKE_CXX_STANDARD 14)

add_executable(unix_shell main.cpp cat.cpp wc.cpp ls.cpp mv.cpp tail.cpp adduser.cpp chmod.cpp kill.cpp)