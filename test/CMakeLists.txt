cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_COMPILER      "clang++" )         # 显示指定使用的C++编译器
set(CMAKE_CXX_FLAGS   "-std=c++11")             # c++11
set(CMAKE_CXX_FLAGS   "-g")                     # 调试信息
set(CMAKE_CXX_FLAGS   "-Wl,--no-as-needed")                  # 开启所有警告
set(CMAKE_CXX_FLAGS   "-pthread")   
set(CMAKE_CXX_FLAGS_DEBUG   "-O0" )             # 调试包不优化
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG " )   # release包优化
set(lib_path ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

message(${lib_path})

link_directories(${lib_path})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
FILE(GLOB test_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(test_algo ${test_srcs})
target_link_libraries(test_algo algo data_struct)
install(TARGETS test_algo DESTINATION bin/)

