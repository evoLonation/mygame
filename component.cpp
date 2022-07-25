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

Model *MeshComponent::getModel() const {
    return model;
}

void MeshComponent::setScale(float scale){
    this->scale = MatrixFactory::CreateScale(scale);
    scaleZ = MatrixFactory::CreateScale(1, 1, 1/scale);
    computeWorldTrans();
}

Texture *MeshComponent::getTexture() const {
    return texture;
}

const BaseMatrix4 MeshComponent::getWorldTrans() const {
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
    translation = MatrixFactory::CreateTranslation(x, y, z);
    Compute();
}

void LocationComponent::SetDirection(const Vector3 &front, float theta) {
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
    rotate *= MatrixFactory::CreateRotationZ(theta);
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
    Vector4 vector(0, 0, distance, 0);
    vector = vector * rotate;
    translation *= MatrixFactory::CreateTranslation(vector[0], vector[1], vector[2]);
    Compute();
}

void LocationComponent::TranslateX(float distance) {
    Vector4 vector(distance, 0, 0, 0);
    vector = vector * rotate;
    translation *= MatrixFactory::CreateTranslation(vector[0], vector[1], vector[2]);
    Compute();
}

void LocationComponent::TranslateY(float distance) {

}

void LocationComponent::RotateY(float theta) {
    rotate *= MatrixFactory::CreateRotationY(theta);
    Compute();
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
