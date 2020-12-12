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

#find_package(cpprestsdk CONFIG REQUIRED)

include_directories(src/dep/cpprestsdk/Release/include)

add_executable(main src/db.cpp ${db_SRC} src/CharStreamDecoder.cpp src/CharStreamDecoder.h src/Enums.h src/Server.cpp src/Server.h src/dataTypes/functions/tableFunctions/InsertFunctionComponent.cpp src/dataTypes/functions/tableFunctions/InsertFunctionComponent.h)
#target_link_libraries(main PRIVATE
#        cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_brotli_internal)
