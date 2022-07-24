
#include <cstring>
#include "math.h"

bool is0(float a){
    return a < 0.000001 && a > -0.000001;
}

class ScaleMatrix MatrixFactory::CreateScale(float scale) {
    return CreateScale(scale, scale, scale);
}

class ScaleMatrix MatrixFactory::CreateScale(float scaleX, float scaleY, float scaleZ) {
    float arr[4][4] = {
            {scaleX, 0,  0,  0},
            {0, scaleY,  0,  0},
            {0, 0,  scaleZ,  0},
            {0, 0,  0,       1},
    };
    return {arr};
}

class TranslationMatrix MatrixFactory::CreateTranslation(float x, float y, float z) {
    float arr[4][4] = {
            {1, 0,  0,  0},
            {0, 1,  0,  0},
            {0, 0,  1,  0},
            {x, y,  z,  1},
    };
    return {arr};
}

class OrthogonalMatrix MatrixFactory::CreateRotationX(float theta) {
    float arr[4][4] = {
            {1, 0,  0,  0},
            {0, std::cos(theta),    std::sin(theta),  0},
            {0, -std::sin(theta),   std::cos(theta),  0},
            {0, 0,                      0,  1},
    };
    return {arr};
}

class OrthogonalMatrix MatrixFactory::CreateRotationY(float theta) {
    float arr[4][4] = {
            {std::cos(theta), 0, -std::sin(theta),  0},
            {0,     1,  0,0},
            {std::sin(theta), 0,  std::cos(theta),  0},
            {0, 0,                      0,  1},
    };
    return {arr};
}

class OrthogonalMatrix MatrixFactory::CreateRotationZ(float theta) {
    float sin = std::sin(theta);
    float cos = std::cos(theta);
    float arr[4][4] = {
            {cos,   sin,    0,  0,  },
            {-sin,  cos,    0,  0,  },
            {0,     0,      1,  0,  },
            {0,     0,      0,  1,  },
    };
    return {arr};
}
Matrix4 MatrixFactory::CreateUnitary() {
    float arr[4][4] = {
            {1, 0,  0,  0},
            {0, 1,  0,  0},
            {0, 0,  1,  0},
            {0, 0,  0,  1},
    };
    return {arr};
}
/**
 * 在游戏引擎架构一书中，透视投影矩阵的转换貌似会颠倒z轴；因此这里使用《创建3D游戏这本书》的矩阵创建方式，使得观察体积是z轴正方向的，更加符合常识。
 */
Matrix4 MatrixFactory::CreatePerspectiveProjection(float left, float right, float top, float bottom, float near, float far) {
    auto m4 = Matrix4();
    m4.data[0][0] =  2 * near / (right - left);
    m4.data[1][1] =  2 * near / (top - bottom);
    m4.data[2][0] = (right + left) / (right - left);
    m4.data[2][1] = (top + bottom) / (top - bottom);
    m4.data[2][2] = -(far + near) / (near - far);
    m4.data[2][3] = 1;
    m4.data[3][2] = 2 * near * far / (near - far);
    return m4;
}

Matrix4 MatrixFactory::CreatePerspectiveProjection(float width, float height, float near, float far) {
    return CreatePerspectiveProjection(-width / 2, width / 2, height / 2, -height / 2, near, far);
}

class OrthogonalMatrix MatrixFactory::CreateByQuaternion(const struct UnitQuaternion &quaternion) {
    float x = quaternion.data[0];
    float y = quaternion.data[1];
    float z = quaternion.data[2];
    float w = quaternion.data[3];
    float arr[4][4] = {
            {1-2*y*y-2*z*z, 2*x*y+2*w*z,  2*x*z-2*w*y,  0},
            {2*x*y-2*w*z, 1-2*x*x-2*z*z,  2*y*z+2*w*x,  0},
            {2*x*z+2*w*y, 2*y*z-2*w*x,  1-2*x*x-2*y*y,  0},
            {0, 0,  0,  1},
    };
    return {arr};
}

BaseMatrix4::BaseMatrix4(const float arr[][4]) {
    memcpy(data, arr, 4 * 4 * sizeof(float) );
}

Matrix4 operator~(const BaseMatrix4& matrix4) {
    Matrix4 m;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m.data[i][j] = matrix4.Get(j, i);
    return m;
}
OrthogonalMatrix operator~(const OrthogonalMatrix& matrix4){
    return {(~static_cast<BaseMatrix4>(matrix4)).data};
}

Matrix4 BaseMatrix4::operator*(const BaseMatrix4 &matrix) const{
    Matrix4 m;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                m.data[i][j] += data[i][k] * matrix.data[k][j];
    return m;
}
void BaseMatrix4::operator*=(const BaseMatrix4& matrix){
    *this = *this * matrix;
}



float BaseMatrix4::Get(int i, int j) const {
    return data[i][j];
}


Matrix4::Matrix4(const float (*arr)[4]) : BaseMatrix4(arr) {}

TranslationMatrix::TranslationMatrix(): BaseMatrix4(MatrixFactory::CreateUnitary()) {}

TranslationMatrix::TranslationMatrix(const float (*arr)[4]) : BaseMatrix4(arr) {}

TranslationMatrix TranslationMatrix::operator!() {
    TranslationMatrix  translationMatrix(*this);
    translationMatrix.data[3][0] = -data[3][0];
    translationMatrix.data[3][1] = -data[3][1];
    translationMatrix.data[3][2] = -data[3][2];
    return translationMatrix;
}

TranslationMatrix TranslationMatrix::operator*(const TranslationMatrix &matrix) {
    return {(*this * static_cast<BaseMatrix4>(matrix)).data};
}

void TranslationMatrix::operator*=(const TranslationMatrix &matrix) {
    *this = *this * matrix;
}


OrthogonalMatrix::OrthogonalMatrix(): BaseMatrix4(MatrixFactory::CreateUnitary()) {}

OrthogonalMatrix::OrthogonalMatrix(const float (*arr)[4]) : BaseMatrix4(arr) {}

OrthogonalMatrix OrthogonalMatrix::operator!() const {
    return {(~*this).data};
}

OrthogonalMatrix OrthogonalMatrix::operator*(const OrthogonalMatrix &matrix) {
    return {(*this * static_cast<BaseMatrix4>(matrix)).data};
}

void OrthogonalMatrix::operator*=(const OrthogonalMatrix &matrix) {
    *this = *this * matrix;
}



ScaleMatrix::ScaleMatrix(): BaseMatrix4(MatrixFactory::CreateUnitary()) {}

ScaleMatrix::ScaleMatrix(const float (*arr)[4]) : BaseMatrix4(arr) {}

ScaleMatrix ScaleMatrix::operator!() {
    ScaleMatrix  scaleMatrix(*this);
    scaleMatrix.data[0][0] = 1 / data[0][0];
    scaleMatrix.data[1][1] = 1 / data[1][1];
    scaleMatrix.data[2][2] = 1 / data[2][2];
    return scaleMatrix;
}

ScaleMatrix ScaleMatrix::operator*(const ScaleMatrix &matrix) {
    return {(*this * static_cast<BaseMatrix4>(matrix)).data};
}

void ScaleMatrix::operator*=(const ScaleMatrix &matrix) {
    *this = *this * matrix;
}


Vector3::Vector3(float x, float y, float z) {
    data[0] = x;
    data[1] = y;
    data[2] = z;
}
Vector3 operator*(float x, const Vector3 &vector3) {
    return {x * vector3.data[0], x * vector3.data[1], x * vector3.data[2]};
}

float operator*(const Vector3 &vector1, const Vector3 &vector2) {
    return vector1.data[0] * vector2.data[0] + vector1.data[1] * vector2.data[1] + vector1.data[2] * vector2.data[2];
}

Vector3 operator%(const Vector3 &vector1, const Vector3 &vector2) {
    return {vector1.data[1] * vector2.data[2] - vector1.data[2] * vector2.data[1],
            vector1.data[2] * vector2.data[0] - vector1.data[0] * vector2.data[2],
            vector1.data[0] * vector2.data[1] - vector1.data[1] * vector2.data[0]};
}

Vector3 operator+(const Vector3 &vector1, const Vector3 &vector2) {
    return {vector1.data[0] + vector2.data[0], vector1.data[1] + vector2.data[1], vector1.data[2] + vector2.data[2]};
}
float operator~(const Vector3& vector){
    return std::sqrt(vector * vector);
}

Vector3 operator/(const Vector3 &vector3, float x) {
    return {vector3.data[0] / x, vector3.data[1] / x, vector3.data[2] / x};
}

bool operator==(const Vector3 &vector1, const Vector3 &vector2) {
    return is0(vector1.data[0] - vector2.data[0]) &&
            is0(vector1.data[1] - vector2.data[1]) &&
            is0(vector1.data[2] - vector2.data[2]);
}


Quaternion Quaternion::operator*() {
    return {-data[0], -data[1], -data[2], data[3]};
}

Quaternion::Quaternion(float x, float y, float z, float w) {
    data[0] = x;
    data[1] = y;
    data[2] = z;
    data[3] = w;
}

Quaternion Quaternion::operator*(const Quaternion &quaternion) {
    Vector3 qv = Vector3(quaternion.data[0], quaternion.data[1], quaternion.data[2]);
    float qs = quaternion.data[3];
    Vector3 pv = Vector3(data[0], data[1], data[2]);
    float ps = data[3];
    return {ps * qv + qs * pv + pv % qv, (ps * qs - pv * qv)};
}

Quaternion::Quaternion(Vector3 qv, float qs):Quaternion(qv.data[0], qv.data[1], qv.data[2], qs) {}


UnitVector3::UnitVector3(const Vector3 &vector3){
    Vector3 vector = vector3 / ~vector3;
    data[0] = vector.data[0];
    data[1] = vector.data[1];
    data[2] = vector.data[2];
}

UnitQuaternion::UnitQuaternion(const UnitVector3& unitVector, float theta) {
    float sin = std::sin(theta / 2);
    float cos = std::cos(theta / 2);
    data[0] = unitVector.data[0] * sin;
    data[1] = unitVector.data[1] * sin;
    data[2] = unitVector.data[2] * sin;
    data[3] = cos;
}
