#pragma once
#include <CL/opencl.hpp>

#include <string>

#define CHECK_ERROR(x) \
    do { if ((x)) {\
        std::cerr << std::format("Error {} at {}:{}\n",\
            (x), __FILE__, __LINE__);\
        std::exit(1);\
    } } while(0)

std::string ReadFile(std::string path);
cl::Device GetDefaultDevice();