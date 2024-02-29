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

FILE(GLOB COMMON_SOURCES
    Common/zhelpers.hpp
    Common/IClient.h Common/IClient.cpp
)

add_executable(
    broker
    Broker/broker.cpp
    Broker/Broker.h Broker/Broker.cpp
    Broker/BackupManager.h Broker/BackupManager.cpp
    ${COMMON_SOURCES}
)
target_link_libraries(
    broker
    PRIVATE cppzmq ${CMAKE_THREAD_LIBS_INIT} Qt${QT_VERSION_MAJOR}::Core
)

add_executable(
    destination
    Destination/destination.cpp
    Destination/Destination.h Destination/Destination.cpp
    ${COMMON_SOURCES}
)
target_link_libraries(
    destination
    PRIVATE cppzmq ${CMAKE_THREAD_LIBS_INIT} Qt${QT_VERSION_MAJOR}::Core
)

add_executable(
    source
    Source/source.cpp
    Source/Source.h Source/Source.cpp
    ${COMMON_SOURCES}
)
target_link_libraries(
    source
    PRIVATE cppzmq ${CMAKE_THREAD_LIBS_INIT} Qt${QT_VERSION_MAJOR}::Core
)
