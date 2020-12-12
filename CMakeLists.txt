cmake_minimum_required(VERSION 3.17)
project(db)

set(CMAKE_CXX_STANDARD 20)

file(GLOB db_SRC
        "src/*.h"
        "src/*.cpp"
        "src/dataTypes/*.h"
        "src/dataTypes/*.cpp"
        "src/dataTypes/functions/tableFunctions/*.h"
        "src/dataTypes/functions/tableFunctions/*.cpp"
        )


#restinio
#include_directories(src/dep/restinio/dev)
#include_directories(src/dep/restinio/dev/asio/include)
#include_directories(src/dep/restinio/dev/fmt/include)
#include_directories(src/dep/restinio/dev/restinio)
#include_directories(src/dep/restinio/dev/nodejs/http_parser)
#find_package(src/dep/restinio/dev/cmake_build/restinio/restinio-config.cmake REQUIRED)

# Make your project dependent on restinio,
# and let cmake deal with all t he headers paths and linked libs.
#target_link_libraries(db PRIVATE restinio::restinio)

#include_directories(src/dep/cpprestsdkRelease/)
find_package(cpprestsdk CONFIG REQUIRED)

add_executable(main src/db.cpp ${db_SRC} src/CharStreamDecoder.cpp src/CharStreamDecoder.h src/Enums.h src/Server.cpp src/Server.h src/dataTypes/functions/tableFunctions/InsertFunctionComponent.cpp src/dataTypes/functions/tableFunctions/InsertFunctionComponent.h)
#cpprestsdk
target_link_libraries(main PRIVATE
        cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_brotli_internal)
#set(cpprestsdk_DIR C:/dev/vcpkg/installed/x86-windows/share/cpprestsdk)
#set(ZLIB_INCLUDE_DIR C:/dev/vcpkg/installed/x86-windows/share/zlib)
#include_directories(C:/dev/vcpkg/installed/x86-windows/share)

#target_link_libraries(db src/dep/cpprestsdkRelease/cpprest142_2_10.dll)
#target_link_libraries(db src/dep/cpprestsdkRelease/cpprest142_2_10.lib)

#
#add_library(mio STATIC src/dep/mio/mio.cpp)
#target_link_libraries(db PRIVATE cpprestsdk::cpprest)
#target_link_libraries(db PRIVATE cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_brotli_internal)

#include_directories(C:/boost/boost_1_74_0)

#SET(CMAKE_EXE_LINKER_FLAGS  "-lws2_32")