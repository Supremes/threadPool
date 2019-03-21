project(threadPool)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_C_COMPILER g++)
set(CMAKE_BUILD_TYPE "Debug")
add_compile_options(-std=c++11)
set(C_FLAGS
    -g
)
aux_source_directory(threadPool SRC_LIST)

find_package(Threads)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})