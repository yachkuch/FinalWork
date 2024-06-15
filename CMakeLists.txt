cmake_minimum_required(VERSION 3.12)

project(AsyncIO)

set(CLIENT 1)
set(SEVER 1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(LIB_INCLUDE "/networker"
                "/database"
                "/ui"
                "/protocol")

find_package(Boost CONFIG REQUIRED)
link_libraries(Boost::boost)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(SOURCES sqlite/sqlite3.c)

file(GLOB helloworld_SRC
     "database/*.h"
     "database/*.c*"
     "networker/*.c*"
     "networker/*.h"
     "ui/*.h"
     "ui/*.cpp"
     "protocol/*.h"
)

include_directories(${LIB_INCLUDES})
if(CLIENT)
add_executable(asio_client asio_client.cpp)
endif()

if(SEVER)
add_executable(asio_server asio_server.cpp ${SOURCES} ${helloworld_SRC})
endif()

if(CLIENT)
target_include_directories(asio_client PRIVATE sqlite/)
endif()

if(SEVER)
target_include_directories(asio_server PRIVATE sqlite/)
target_include_directories(asio_server PRIVATE database/)
target_include_directories(asio_server PRIVATE networker/)
target_include_directories(asio_server PRIVATE ui/)
target_include_directories(asio_server PRIVATE protocol/)
endif()
if(MINGW)
  target_link_libraries(asio_client ws2_32)
endif()
if(MINGW)
  target_link_libraries(asio_server ws2_32)
endif()
if(CLIENT)
target_link_libraries(asio_client ${Boost_LIBRARIES})
endif()

if(SEVER)

target_link_libraries(asio_server ${Boost_LIBRARIES})
target_link_libraries(asio_server PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
endif()


