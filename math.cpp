//
// Created by 18389 on 7/22/2022.
//

#include <cstring>
#include "math.h"


Matrix4::Matrix4() {
    memset(data, 0, 4 * 4 * sizeof(float) );
}
Matrix4::Matrix4(const float arr[][4]) {
    memcpy(data, arr, 4 * 4 * sizeof(float) );
}

Matrix4 Matrix4::operator~() {
    Matrix4 m;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m.data[i][j] = data[j][i];
    return m;
}

Matrix4 Matrix4::operator*(const Matrix4 &matrix) {
    Matrix4 m;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                m.data[i][j] += data[i][k] * matrix.data[k][j];
    return m;
}
Matrix4& Matrix4::operator*=(const Matrix4& matrix){
    *this = *this * matrix;
    return *this;
}
Matrix4 Matrix4::CreateScale(float scale) {
    float arr[4][4] = {
            {scale, 0,  0,  0},
            {0, scale,  0,  0},
            {0, 0,  scale,  0},
            {0, 0,  0,      1},
    };
    return Matrix4(arr);
}

Matrix4 Matrix4::CreateScale(const struct Vector3 &vector3) {
    float arr[4][4] = {
            {vector3.data[0], 0,  0,  0},
            {0, vector3.data[1],  0,  0},
            {0, 0,  vector3.data[2],  0},
            {0, 0,  0,      1},
    };
    return Matrix4(arr);
}

Matrix4 Matrix4::CreateUnitary() {
    float arr[4][4] = {
            {1, 0,  0,  0},
            {0, 1,  0,  0},
            {0, 0,  1,  0},
            {0, 0,  0,  1},
    };
    return Matrix4(arr);
}


Vector3::Vector3(float x, float y, float z) {
    data[0] = x;
    data[1] = y;
    data[2] = z;
}
