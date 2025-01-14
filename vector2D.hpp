#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include<iostream>
namespace math_op  {

template<typename _T>
class Vector2D {
    public:
    constexpr Vector2D(_T x, _T y) : x(x), y(y) {}
    _T x, y;

    constexpr Vector2D operator+(const Vector2D& _v) const {
        return Vector2D(this->x + _v.x, this->y + _v.y);
    }

    constexpr Vector2D operator-(const Vector2D& _v) const {
        return Vector2D(this->x - _v.x, this->y - _v.y);
    }

    constexpr Vector2D operator*(double _scalar) const {
        return Vector2D(this->x * _scalar, this->y * _scalar);
    }

    constexpr double get_magnitude() const {
        return std::sqrt((this->x * this->x) + (this->y * this->y));
    }

    constexpr Vector2D normalize () const {
        double mg = get_magnitude();
        return Vector2D(this->x / mg, this->y / mg);
    }

    void show_vector(){
        std::cout << "(" << this->x << ", " << this->y << ")" << std::endl;
    }

};

}

#endif