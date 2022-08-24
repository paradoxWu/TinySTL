cmake_minimum_required(VERSION 3.10)
# 设置工程名称
set(PROJECT_NAME TinySTL)
# 设置工程版本号
set(PROJECT_VERSION "0.0.1" CACHE STRING "default")

# SET(CMAKE_CXX_COMPILER "/usr/local/bin/g++-11")
# SET(CMAKE_C_COMPILER "/usr/local/bin/gcc-11")

message("DIRECTORY:${CMAKE_CURRENT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_COMPILER      "clang++" )         # 显示指定使用的C++编译器
set(CMAKE_CXX_FLAGS   "-std=c++11")             # c++11
set(CMAKE_CXX_FLAGS   "-g")                     # 调试信息
set(CMAKE_CXX_FLAGS   "-Wall")                  # 开启所有警告
set(CMAKE_CXX_FLAGS_DEBUG   "-O0" )             # 调试包不优化
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG " )   # release包优化

project(${PROJECT_NAME}
    LANGUAGES CXX C 
    VERSION ${PROJECT_VERSION}
)

OPTION(DEBUG    "Output log to terminal for debugging" OFF)
OPTION(TEST "Test the lib" ON)

IF(DEBUG)
        ADD_DEFINITIONS(-DDEBUG=1)
ENDIF()

MACRO(SUB_DIR_LIST result curdir)
    FILE(GLOB children ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${child})
            GET_FILENAME_COMPONENT(dir_name ${child} NAME_WE)
            LIST(APPEND dirlist ${dir_name})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

SUB_DIR_LIST(modules ${CMAKE_CURRENT_SOURCE_DIR}/src)
FOREACH (module ${modules})
    message(${module})
    SET(module_dir ${CMAKE_CURRENT_SOURCE_DIR}/src/${module})
    # aux_source_directory(${module_dir} module_srcs)
    FILE(GLOB module_srcs ${module_dir}/*.cpp)
    add_library(${module} SHARED ${module_srcs})
    install(TARGETS ${module} DESTINATION install/lib)
ENDFOREACH()

IF(TEST)
    # add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
    INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test DESTINATION install/)
    INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include DESTINATION install/)
ENDIF()


