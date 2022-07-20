link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
FILE(GLOB test_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(test_algo ${test_srcs})
target_link_libraries(test_algo algo)
install(TARGETS test_algo DESTINATION)

