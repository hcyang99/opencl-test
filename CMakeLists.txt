cmake_minimum_required(VERSION 3.20)
project(opencl-test LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCL REQUIRED)
add_compile_definitions(CL_HPP_TARGET_OPENCL_VERSION=300)

add_executable(main src/main.cc src/utils.hh src/utils.cc)
target_link_libraries(main OpenCL::OpenCL)