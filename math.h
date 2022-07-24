#pragma once
#include <cmath>

constexpr float PI = 3.1415926535;
inline bool is0(float);

class MatrixFactory{
public:
    static class ScaleMatrix CreateScale(float scale);
    static class ScaleMatrix CreateScale(float scaleX, float scaleY, float scaleZ);
    static class TranslationMatrix CreateTranslation(float x, float y, float z);
    static class OrthogonalMatrix CreateRotationX(float theta);
    static class OrthogonalMatrix CreateRotationY(float theta);
    static class OrthogonalMatrix CreateRotationZ(float theta);
    static class OrthogonalMatrix CreateByQuaternion(const class UnitQuaternion& quaternion);
    static class Matrix4 CreateUnitary();
    static class Matrix4 CreatePerspectiveProjection(float left, float right, float top, float bottom, float near, float far);
    static class Matrix4 CreatePerspectiveProjection(float width, float height, float near, float far);
};
//由于转置操作子类与父类返回值不同且定义在类中的话就会无参从而无法重载，因此定义在外面
class Matrix4 operator~(const class BaseMatrix4& matrix4);
class OrthogonalMatrix operator~(const class OrthogonalMatrix& matrix4);

class BaseMatrix4 {
public:
    BaseMatrix4() = default;
    explicit BaseMatrix4(const float arr[][4]);

    //转置
//    virtual class Matrix4 operator~();
    virtual class Matrix4 operator*(const BaseMatrix4& matrix) const;
    void operator*=(const BaseMatrix4& matrix);


public:
    float Get(int x, int y) const;
protected:
    float data[4][4] = {};
};

// 可变矩阵，唯一变化是将data的访问权限升级为public
class Matrix4 : public BaseMatrix4 {
    friend MatrixFactory;
public:
    Matrix4(const float (*arr)[4]);
    Matrix4() = default;
    using BaseMatrix4::data;



};

// 位移矩阵
// 更改其逆矩阵计算方式
class TranslationMatrix : public BaseMatrix4 {
    friend MatrixFactory;
public:
    TranslationMatrix();
protected:
    TranslationMatrix(const float (*arr)[4]);

public:

    TranslationMatrix operator!();
    //新定义的函数会直接覆盖掉原来的父类中的运算符重载，尽管参数不完全一样
    TranslationMatrix operator*(const TranslationMatrix& matrix);
    using BaseMatrix4::operator*;
    void operator*=(const TranslationMatrix& matrix);
    // *= 运算就不用继承父类的了

};

//标准正交矩阵，表示纯旋转
class OrthogonalMatrix : public BaseMatrix4 {
public:
    OrthogonalMatrix();

    friend MatrixFactory;
    friend OrthogonalMatrix operator~(const OrthogonalMatrix& matrix4);
protected:
    OrthogonalMatrix(const float (*arr)[4]);

public:
    OrthogonalMatrix operator!() const;
    OrthogonalMatrix operator*(const OrthogonalMatrix& matrix);
    using BaseMatrix4::operator*;
    void operator*=(const OrthogonalMatrix& matrix);
};




//缩放矩阵
class ScaleMatrix : public BaseMatrix4 {
public:
    ScaleMatrix();

    friend MatrixFactory;
protected:
    ScaleMatrix(const float (*arr)[4]);

public:
    ScaleMatrix operator!();
    ScaleMatrix operator*(const ScaleMatrix& matrix);
    using BaseMatrix4::operator*;
    void operator*=(const ScaleMatrix& matrix);
};



class Vector4 {
public:
    Vector4(float x, float y, float z, float w){
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = w;
    }
    float data[4] = {};

    float& operator[](int i){
        return data[i];
    }
};

class Vector3 {
public:
    Vector3() = default;
    Vector3(float x, float y, float z);

    float data[3] = {};
};
class UnitVector3 : public Vector3{
public:
    UnitVector3(const Vector3& vector3);
};

Vector3 operator*(float x, const Vector3& vector3);
Vector3 operator/(const Vector3& vector3, float x);
float operator*(const Vector3& vector1, const Vector3& vector2);
//叉积
Vector3 operator%(const Vector3& vector1, const Vector3& vector2);
Vector3 operator+(const Vector3& vector1, const Vector3& vector2);
bool operator==(const Vector3& vector1, const Vector3& vector2);

float operator~(const Vector3& vector);


class Quaternion {
public:
    Quaternion() = default;
    Quaternion(float x, float y, float z, float w);
    //共轭
    Quaternion operator*();
    Quaternion operator*(const Quaternion& quaternion);
    Quaternion(Vector3 qv, float qs);
    float data[4] = {};


};
class UnitQuaternion : public Quaternion{
public:
    UnitQuaternion(const UnitVector3& unitVector, float theta);
};

