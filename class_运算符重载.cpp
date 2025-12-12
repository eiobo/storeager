// 题目：自定义二维向量类 Vector2D 的运算符重载
// 请你设计并实现一个名为 Vector2D 的 C++ 类，用于表示二维平面上的向量。该类应该有两个 double 类型的私有成员变量，分别表示向量的 x 和 y 分量。

// 你需要为 Vector2D 类实现以下运算符重载：
//     构造函数: 能够接收两个 double 值来初始化 x 和 y 分量。如果未提供参数，则初始化为 (0.0, 0.0)。
//     加法运算符 operator+: 实现两个 Vector2D 对象相加。它应该返回一个新的 Vector2D 对象，其分量分别是对应分量之和。
//     减法运算符 operator-: 实现两个 Vector2D 对象相减。它应该返回一个新的 Vector2D 对象，其分量分别是对应分量之差。
//     标量乘法运算符 operator*: 实现一个 Vector2D 对象与一个 double 类型的标量相乘。它应该返回一个新的 Vector2D 对象，其分量是原向量分量分别乘以标量。
//     相等运算符 operator==: 比较两个 Vector2D 对象是否相等（即它们的 x 分量和 y 分量是否都相等）。
//     不等运算符 operator!=: 比较两个 Vector2D 对象是否不相等。
//     赋值运算符 operator=: 实现将一个 Vector2D 对象的值赋给另一个 Vector2D 对象。此运算符应返回对当前对象的引用，并正确处理自我赋值的情况。
//     输出流运算符 operator<<: 实现将 Vector2D 对象格式化输出到标准输出流，形式如 (x, y)。此函数应作为类的友元函数实现。
//     下标运算符 operator[]: 实现通过下标访问向量的 x 和 y 分量。vec[0] 应返回 x 分量，vec[1] 应返回 y 分量。需要提供 const 和非 const 版本，以支持读写操作。如果下标无效（非 0 或 1），应抛出 std::out_of_range 异常。

#include <iostream>

using namespace std;

class Vector2D {
private: 
    double x;
    double y;
public:
    Vector2D() : x(0.0), y(0.0) {}
    Vector2D(double x_in, double y_in) : x(x_in), y(y_in) {}
    Vector2D(const Vector2D& another) : x(another.x), y(another.y) {}
    inline void PrintVector2D() const;
    Vector2D operator+(const Vector2D& another) const;
    Vector2D operator-(const Vector2D& another) const;
    Vector2D operator*(const Vector2D& another) const;
    bool operator==(const Vector2D& another) const;
    bool operator!=(const Vector2D& another) const;
    Vector2D& operator=(const Vector2D& another);
    friend ostream& operator<<(ostream& os, const Vector2D& vec);
    double& operator[](int idx) {
        if(idx == 0) return this->x;
        else if(idx == 1) return this->y;
        else throw out_of_range("Vector 2D index out of range. Valid idx is 0 , 1 !");
    }
};

// 友元函数不是类的成员函数，在类中声明只是可以允许他访问私有变量
ostream& operator<<(ostream& os, const Vector2D& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

Vector2D& Vector2D::operator=(const Vector2D& another) {
    this->x = another.x;
    this->y = another.y;
    return *this;
}

bool Vector2D::operator!=(const Vector2D& another) const {
    return !(*this == another);
}

bool Vector2D::operator==(const Vector2D& another) const {
    return (this->x == another.x && this->y == another.y);
}

Vector2D Vector2D::operator*(const Vector2D& another) const {
    Vector2D retval;
    retval.x = this->x * another.x;
    retval.y = this->y * another.y;
    return retval;
}

Vector2D Vector2D::operator-(const Vector2D& another) const {
    Vector2D retval;
    retval.x = this->x - another.x;
    retval.y = this->y - another.y;
    return retval;
}

Vector2D Vector2D::operator+(const Vector2D& another) const {
    Vector2D retval;
    retval.x = this->x + another.x;
    retval.y = this->y + another.y;
    return retval;
}

inline void Vector2D::PrintVector2D() const {
    cout << "x: " << x << ' ' << "y : " << y << endl; 
}

int main() {
    Vector2D v1, v2(3.1314123, 4.213451), v3(1.178623478, 2.88192359);  // v1 默认构造 v2，v3参数构造
    Vector2D v4 = v1 + v2 + v3;
    cout << v4 << endl;
    cout << v4[0] << endl;              // 重载[]
    v4 = v4 * v2 + v3;                  // + *
    cout << v4 << endl;
    Vector2D v5 = v4;                   // 调用拷贝构造函数（浅拷贝）
    Vector2D v6(v5);                    // 调用拷贝构造函数（浅拷贝）
    Vector2D v7;                        // 调用默认构造函数
    v7 = v5;                            // 调用operator=
    cout << v5 << endl << v6 << endl;
}
