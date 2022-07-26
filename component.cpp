#include"component.h"
#include "model.h"
#include "texture.h"
#include "actor.h"

MeshComponent::MeshComponent(class Model* model, class Texture* texture)
: model(model), texture(texture),
scale(MatrixFactory::CreateUnitary()), worldTrans(MatrixFactory::CreateUnitary()), rotation(MatrixFactory::CreateUnitary()),
translation(MatrixFactory::CreateUnitary()), scaleZ(MatrixFactory::CreateUnitary()){}
MeshComponent::~MeshComponent(){}

void MeshComponent::Update(){

}

Model *MeshComponent::GetModel() const {
    return model;
}

void MeshComponent::GetScale(float scale){
    this->scale = MatrixFactory::CreateScale(scale);
    scaleZ = MatrixFactory::CreateScale(1, 1, 1/scale);
    computeWorldTrans();
}

Texture *MeshComponent::getTexture() const {
    return texture;
}

BaseMatrix4 MeshComponent::getWorldTrans() const {
    return worldTrans;
}

void MeshComponent::computeWorldTrans() {
    worldTrans = scale;
    worldTrans *= rotation;
    worldTrans *= translation;
    worldTrans *= scaleZ;

}

void MeshComponent::setTranslation(float x, float y, float z) {
    translation = MatrixFactory::CreateTranslation(x, y, z);
    computeWorldTrans();
}



void LocationComponent::SetLocation(float x, float y, float z) {
    Initialization();
    translation = MatrixFactory::CreateTranslation(x, y, z);
    Compute();
}

void LocationComponent::SetDirection(const Vector3 &front, float theta) {
    Initialization();
    const Vector3 v1(0, 0, 1);
    const Vector3 &v2 = front;
    if(v1 == v2){
        rotate = OrthogonalMatrix();
    }else if(is0(v1 * v2 + ~v1 * ~v2)){
        rotate = MatrixFactory::CreateRotationY(PI);
    }else{

        // 计算旋转角度
        float cos = ( v1 * v2 ) / (~v1 * ~v2);
        float theta1 = std::acos(cos);

        UnitQuaternion unitQuaternion(UnitVector3(v1 % v2), theta1);
        rotate = MatrixFactory::CreateByQuaternion(unitQuaternion);
    }
    rotate = MatrixFactory::CreateRotationZ(theta) * rotate;
    Compute();
}

void LocationComponent::Update() {

}


const Matrix4& LocationComponent::GetWorldTrans() {
    return worldTrans;
}

void LocationComponent::Compute() {
    worldTrans = rotate * translation;
    worldTransInverse = !translation * !rotate;
}

const Matrix4 &LocationComponent::GetWorldTransInverse() {
    return worldTransInverse;
}

void LocationComponent::TranslateZ(float distance) {
//    Vector4 vector(0, 0, distance, 0);
//    vector = vector * rotate;
//    translation *= MatrixFactory::CreateTranslation(vector[0], vector[1], vector[2]);
//    Compute();
    AddTransform(MatrixFactory::CreateTranslation(0, 0, distance));
}

void LocationComponent::TranslateX(float distance) {
//    Vector4 vector(distance, 0, 0, 0);
//    vector = vector * rotate;
//    translation *= MatrixFactory::CreateTranslation(vector[0], vector[1], vector[2]);
//    Compute();
    AddTransform(MatrixFactory::CreateTranslation(distance, 0, 0));
}

void LocationComponent::TranslateY(float distance) {
//    Vector4 vector(0, distance, 0, 0);
//    vector = vector * rotate;
//    translation *= MatrixFactory::CreateTranslation(vector[0], vector[1], vector[2]);
//    Compute();
    AddTransform(MatrixFactory::CreateTranslation(0, distance, 0));
}

void LocationComponent::RotateY(float theta) {
//    rotate *= MatrixFactory::CreateRotationY(theta);
//    Compute();
    AddTransform(MatrixFactory::CreateRotationY(theta));
}

void LocationComponent::RotateByAxis(const Vector3 &start, const Vector3 &vector, float theta) {
    /** 简单来讲，将原来的点变换为旋转后的点的过程：
     * 首先将点的坐标变换为以start为原点、基向量不变的新坐标系；
     * 然后使用四元数进行旋转；
     * 最后再变换回来。
     */
    AddTransform(MatrixFactory::CreateTranslation(start[0], start[1], start[2]));
    AddTransform(MatrixFactory::CreateByQuaternion(UnitQuaternion(UnitVector3(vector), theta)));
    AddTransform(MatrixFactory::CreateTranslation(-start[0], -start[1], -start[2]));

}

void LocationComponent::Initialization() {
    if(isInitialization == false) {
        rotate = OrthogonalMatrix();
        translation = TranslationMatrix();
        isInitialization = true;
    }
}

void LocationComponent::AddTransform(const OrthogonalMatrix &matrix) {
    worldTrans = matrix * worldTrans;
    worldTransInverse = worldTransInverse * !matrix;
}
void LocationComponent::AddTransform(const TranslationMatrix &matrix) {
    worldTrans = matrix * worldTrans;
    worldTransInverse = worldTransInverse * !matrix;
}


Actor *BaseComponent::GetOwner() const {
    return owner;
}

void CameraComponent::Update() {

}


void CameraComponent::SetProjection(float width, float height, float near, float far) {
    perspectiveProjection = MatrixFactory::CreatePerspectiveProjection(width, height, near, far);
}

const Matrix4 &CameraComponent::GetProjection() {
    return perspectiveProjection;
}

void CameraComponent::RotateByNearY() {

    owner->GetComponent<LocationComponent>();
}
