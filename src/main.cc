#include <CL/opencl.hpp>

#include "utils.hh"

#include <vector>
#include <string>
#include <iostream>
#include <format>
using namespace std; 

int main() {
    // Host Data
    vector<float> a_host(1024);
    vector<float> b_host(1024);
    vector<float> c_host(1024);

    for (int i = 0; i < 1024; ++i) {
        a_host[i] = i;
        b_host[i] = i * 2;
    }

    cl::Device dev = GetDefaultDevice();
    cl::Context ctx(CL_DEVICE_TYPE_CPU);
    cl::CommandQueue queue(ctx);
    CHECK_ERROR(queue.finish());

    cl::Program prog(ctx, ReadFile("src/vadd.cl"), true);
    auto vadd = cl::KernelFunctor<cl::Buffer, cl::Buffer, cl::Buffer>(prog, "vadd");

    cl::Buffer a_device;
    cl::Buffer b_device;
    cl::Buffer c_device(ctx, CL_MEM_WRITE_ONLY, 1024 * sizeof(float));

    queue.enqueueWriteBuffer(a_device, true, 0, 1024*sizeof(float), &a_host[0]);
    queue.enqueueWriteBuffer(b_device, true, 0, 1024*sizeof(float), &b_host[0]);
    CHECK_ERROR(queue.finish());

    vadd(cl::EnqueueArgs(queue, cl::NDRange(1024)), a_device, b_device, c_device);
    CHECK_ERROR(queue.finish());

    cl::copy(queue, c_device, c_host.begin(), c_host.end());
    for (int i = 0; i < 1024; ++i) {
        if (c_host[i] != a_host[i] + b_host[i]) {
            cerr << format("Failed: {:.2f} + {:.2f} ==> {:.2f}\n", 
                a_host[i], b_host[i], c_host[i]);
            exit(1);
        }
    }
    cerr << "Verification Passed\n";
}