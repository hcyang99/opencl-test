__kernel void vadd(
    __global const float* a,
    __global const float* b,
    __global float* c
) {
    int i = get_global_id(0);
    c[i] = a[i] + b[i];
    if (i == 0)
        printf("%.2f + %.2f == %.2f\n", a[i], b[i], c[i]);
}