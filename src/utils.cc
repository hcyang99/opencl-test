#include "utils.hh"

#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

string ReadFile(string path) {
    ifstream is(path, ios::ate);
    size_t size = is.tellg();
    is.seekg(0);
    string buf(size, '\0');
    is.read(&buf[0], size);
    return buf;
}

cl::Device GetDefaultDevice(){
    
    /**
     * Search for all the OpenCL platforms available and check
     * if there are any.
     * */

    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    if (platforms.empty()){
        std::cerr << "No platforms found!" << std::endl;
        exit(1);
    }

    /**
     * Search for all the devices on the first platform and check if
     * there are any available.
     * */

    auto platform = platforms.front();
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

    if (devices.empty()){
        std::cerr << "No devices found!" << std::endl;
        exit(1);
    }

    /**
     * Return the first device found.
     * */

    return devices.front();
}