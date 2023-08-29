#include <iostream>

class Vector3 {
public:
    float x, y, z;

    Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    float dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 cross(const Vector3& other) const {
        return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    Vector3 convolve(const Vector3& other) const {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }
};

int main() {
    Vector3 v1(1, 2, 3);
    Vector3 v2(4, 5, 6);

    Vector3 sum = v1 + v2;
    Vector3 difference = v1 - v2;
    float dotProduct = v1.dot(v2);
    Vector3 crossProduct = v1.cross(v2);
    Vector3 convolution = v1.convolve(v2);

    std::cout << "Sum: (" << sum.x << ", " << sum.y << ", " << sum.z << ")" << std::endl;
    std::cout << "Difference: (" << difference.x << ", " << difference.y << ", " << difference.z << ")" << std::endl;
    std::cout << "Dot Product: " << dotProduct << std::endl;
    std::cout << "Cross Product: (" << crossProduct.x << ", " << crossProduct.y << ", " << crossProduct.z << ")" << std::endl;
    std::cout << "Convolution: (" << convolution.x << ", " << convolution.y << ", " << convolution.z << ")" << std::endl;

    return 0;
}