cmake_minimum_required(VERSION 3.15)
project(unix_shell)

set(CMAKE_CXX_STANDARD 14)

add_executable(unix_shell main.cpp simple/cat.cpp simple/wc.cpp simple/ls.cpp simple/mv.cpp simple/tail.cpp admin/adduser.cpp admin/chmod.cpp sys/kill.cpp sys/ping.cpp sys/ifconfig.cpp admin/chown.cpp simple/Simple.cpp simple/Simple.h admin/Admin.h admin/Admin.cpp sys/ping.h sys/ifconfig.h sys/kill.h)