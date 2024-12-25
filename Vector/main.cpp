#include "Vector.h"
#include <cmath>
#include <complex>
#include <cstddef>
#include <iostream>

int main() {
    // Vector <double> v(3, 2.0f);
    // Vector <double> v2(3, 1.0f);

    // Vector <std::complex<float>> v(3, std::complex<float>(1.0f, 2.0f));
    // Vector <std::complex<float>> v2(3, std::complex<float>(1.0f, 2.0f));

    // auto v3 = v + v2;
    // v = v + v2;
    // v = 2.0 * v;

    //for (std::size_t i = 0; i < v.size(); i++) {
    //    std::cout << v[i] << std::endl;
    //}

    Vector<float> v1(2, 1.0f);
    Vector<float> v2(2, 1.0f);
    v1[1] = 0;
    std::cout << v1.areaTriangle(v2) << std::endl;
}