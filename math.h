#pragma once


class Matrix4 {
public:
    // 全零
    Matrix4();
    Matrix4(const float arr[][4]);
    Matrix4 operator~();
    Matrix4 operator*(const Matrix4& matrix);
    Matrix4& operator*=(const Matrix4& matrix);

public:
    static Matrix4 CreateScale(float scale);
    static Matrix4 CreateScale(const class Vector3& vector3);
    static Matrix4 CreateUnitary();


    float data[4][4];


};

class Vector3 {
public:
    Vector3(float x, float y, float z);

    float data[3];
};


