cmake_minimum_required(VERSION 3.14)

project(ZeroMQ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

find_package(Threads)
find_package(cppzmq)

add_executable(
    broker
    broker.cpp
)
target_link_libraries(
    broker
    PRIVATE cppzmq ${CMAKE_THREAD_LIBS_INIT}
)

add_executable(
    destination
    destination.cpp
)
target_link_libraries(
    destination
    PRIVATE cppzmq ${CMAKE_THREAD_LIBS_INIT}
)

add_executable(
    source
    source.cpp
)
target_link_libraries(
    source
    PRIVATE cppzmq ${CMAKE_THREAD_LIBS_INIT}
)
