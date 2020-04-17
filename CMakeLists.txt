cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
foreach(policy
    CMP0074 # CMake 3.12
    )
  if(POLICY ${policy})
    cmake_policy(SET ${policy} NEW)
  endif()
endforeach()
option(BUILD_COVERAGE "Build coverage" OFF)

set(
  HUNTER_CACHE_SERVERS
  "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
  CACHE STRING "Default cache server"
)

include("cmake/HunterGate.cmake")

HunterGate(
  URL "https://github.com/cpp-pm/hunter/archive/v0.23.218.tar.gz"
  SHA1 "9a3594a61227967fb92159339ba326701b287b19"
)


project(server)

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

hunter_add_package(Boost COMPONENTS filesystem log system thread)
find_package(Boost CONFIG REQUIRED filesystem log log_setup system thread)
find_package(Threads)
add_library(server STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/Server.cpp
)
add_library(client STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/Client.cpp
)
add_library(log STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/log.cpp
)
add_executable(main
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp)

target_include_directories(server
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(client
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(log
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(log  ${CMAKE_THREAD_LIBS_INIT}
        Boost::log_setup
        Boost::log
        Boost::thread
        Boost::filesystem
        Boost::system)
target_link_libraries(server log  ${CMAKE_THREAD_LIBS_INIT}
        Boost::log_setup
        Boost::log
        Boost::thread
        Boost::filesystem
        Boost::system)
target_link_libraries(client log  ${CMAKE_THREAD_LIBS_INIT}
        Boost::log_setup
        Boost::log
        Boost::thread
        Boost::filesystem
        Boost::system)
target_link_libraries(main server client)
