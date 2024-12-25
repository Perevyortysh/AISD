#pragma once
#include <cmath>
#include <complex>
#include <cstddef>
#include <random>
#include <type_traits>

template <typename T>
class Vector {
private:
    std::size_t size_;
    T* data;
    const T epsilon = 1e-6;

public:
    Vector(std::size_t size, T value);
    Vector(std::size_t size, float low, float high);

    Vector(const Vector<T>& other);
    ~Vector();

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    Vector<T>& operator=(const Vector<T>& other);
    Vector<T> operator+(const Vector<T>& other) const;
    Vector<T> operator-(const Vector<T>& other) const;
    Vector<T> operator*(const T& other) const;
    friend Vector<T> operator*(const T& scalar, const Vector<T>& vec) { return vec * scalar; }
    Vector<T> operator/(const T& other) const;
    T operator*(const Vector<T>& other) const;
    bool operator==(const Vector<T>& other) const;
    bool operator!=(const Vector<T>& other) const { return !operator==(other); }

    std::size_t size() const { return size_; }

    T length() const;
    T sinOfAngleWith(const Vector<T>& other) const;
    T areaTriangle(const Vector<T>& other) const;

private:
    void fillWithRandomNumbers(float low, float high);
};

template <typename T>
Vector<T>::Vector(std::size_t size, T value) : size_(size) {
    data = new T[size];
    for (std::size_t i = 0; i < size; i++) {
        data[i] = value;
    }
}

template <typename T>
inline Vector<T>::Vector(std::size_t size, float low, float high) : size_(size) {
    data = new T[size];
    fillWithRandomNumbers(low, high);
}

template <typename T>
inline Vector<T>::Vector(const Vector<T>& other) {
    size_ = other.size_;
    data = new T[size_];
    for (std::size_t i = 0; i < size_; i++) {
        data[i] = other[i];
    }
}

template <typename T>
Vector<T>::~Vector() { delete[] data; }

template <typename T>
inline T& Vector<T>::operator[](std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range.");
    }
    return data[index];
}

template <typename T>
inline const T& Vector<T>::operator[](std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range.");
    }
    return data[index];
}

template <typename T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (size_ != other.size_) {
        throw std::invalid_argument("Vectors must have the same size.");
    }

    for (std::size_t i = 0; i < size_; i++) {
        data[i] = other[i];
    }
    return *this;
}

template <typename T>
inline Vector<T> Vector<T>::operator+(const Vector<T>& other) const {
    if (size_ != other.size_) {
        throw std::invalid_argument("Vectors must have the same size.");
    }

    Vector<T> result(size_, 0);
    for (std::size_t i = 0; i < size_; i++) {
        result[i] = data[i] + other[i];
    }
    return result;
}

template <typename T>
inline Vector<T> Vector<T>::operator-(const Vector<T>& other) const {
    if (size_ != other.size_) {
        throw std::invalid_argument("Vectors must have the same size.");
    }

    Vector<T> result(size_, 0);
    for (std::size_t i = 0; i < size_; i++) {
        result[i] = data[i] - other[i];
    }
    return result;
}

template <typename T>
inline Vector<T> Vector<T>::operator*(const T& other) const {
    Vector<T> result(size_, 0);
    for (std::size_t i = 0; i < size_; i++) {
        result[i] = data[i] * other;
    }
    return result;
}

template <typename T>
inline Vector<T> Vector<T>::operator/(const T& other) const {
    Vector<T> result(size_, 0);
    for (std::size_t i = 0; i < size_; i++) {
        result[i] = data[i] / other;
    }
    return result;
}

template <typename T>
inline T Vector<T>::operator*(const Vector<T>& other) const {
    if (size_ != other.size_) {
        throw std::invalid_argument("Vectors must have the same size.");
    }

    T result = 0;
    for (std::size_t i = 0; i < size_; i++) {
        result += data[i] * other[i];
    }
    return result;
}

template <typename T>
inline bool Vector<T>::operator==(const Vector<T>& other) const {
    if (size != other.size_) {
        return false;
    }

    for (std::size_t i = 0; i < size_; i++) {
        if (std::abs(data[i] - other[i]) > epsilon) {
            return false;
        }
    }
    return true;
}

template <typename T>
inline T Vector<T>::length() const {
    static_assert(std::is_arithmetic<T>::value, "Length can only be calculated with numeric types ");

    T result = 0;
    for (std::size_t i = 0; i < size_; i++) {
        result += data[i] * data[i];
    }

    return std::sqrt(result);
}

template <typename T>
inline T Vector<T>::sinOfAngleWith(const Vector<T>& other) const {
    if (size_ != other.size_) {
        throw std::invalid_argument("Vectors must have the same size.");
    }
    static_assert(std::is_arithmetic<T>::value, "Angle can only be calculated with numeric types ");

    return std::sqrt(1 - std::pow((*this * other) / (length() * other.length()), 2));
}

template <typename T>
inline T Vector<T>::areaTriangle(const Vector<T>& other) const {
    static_assert(std::is_arithmetic<T>::value, "Area of the triangle can only be calculated with numeric types ");

    T sinAngle = sinOfAngleWith(other);
    return 0.5 * length() * other.length() * sinAngle;
}

template <typename T>
inline void Vector<T>::fillWithRandomNumbers(float low, float high) {
    static_assert(std::is_arithmetic<T>::value or
        std::is_same<T, std::complex<float>>::value or
        std::is_same<T, std::complex<double>>::value,
        "Vector can only be instantiated with numeric types or std::complex types.");

    std::random_device rd;
    std::mt19937 eng(rd());

    if constexpr (std::is_same<T, std::complex<float>>::value) {
        std::uniform_real_distribution<float> dist(low, high);
        for (std::size_t i = 0; i < size_; i++) {
            data[i] = std::complex<float>(dist(eng), dist(eng));
        }
    }
    else if constexpr (std::is_same<T, std::complex<double>>::value) {
        std::uniform_real_distribution<double> dist(low, high);
        for (std::size_t i = 0; i < size_; i++) {
            data[i] = std::complex<double>(dist(eng), dist(eng));
        }
    }
    else {
        std::uniform_real_distribution<T> dist(low, high);
        for (std::size_t i = 0; i < size_; i++) {
            data[i] = dist(eng);
        }
    }
}