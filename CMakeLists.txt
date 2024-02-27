cmake_minimum_required(VERSION 3.14)

project(ZeroMQ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})


find_package(Threads)
find_package(cppzmq)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(
    broker
    broker.cpp
)
target_link_libraries(
    broker
    PRIVATE cppzmq ${CMAKE_THREAD_LIBS_INIT} Qt${QT_VERSION_MAJOR}::Core
)

add_executable(
    destination
    destination.cpp
)
target_link_libraries(
    destination
    PRIVATE cppzmq ${CMAKE_THREAD_LIBS_INIT} Qt${QT_VERSION_MAJOR}::Core
)

add_executable(
    source
    source.cpp
    #zhelpers.hpp
)
target_link_libraries(
    source
    PRIVATE cppzmq ${CMAKE_THREAD_LIBS_INIT} Qt${QT_VERSION_MAJOR}::Core
)
