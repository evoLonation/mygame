#include"component.h"
#include "model.h"
#include "texture.h"

MeshComponent::MeshComponent(class Model* model, class Texture* texture)
: model(model), texture(texture),
scale(Matrix4::CreateUnitary()), worldTrans(Matrix4::CreateUnitary()), rotation(Matrix4::CreateUnitary()),
translation(Matrix4::CreateUnitary()), scaleZ(Matrix4::CreateUnitary())
{

}
MeshComponent::~MeshComponent(){

}
void MeshComponent::Update(){

}

Model *MeshComponent::getModel() const {
    return model;
}

void MeshComponent::setScale(float scale){
    this->scale = Matrix4::CreateScale(scale);
    scaleZ = Matrix4::CreateScale(Vector3(1, 1, 1/scale));
    computeWorldTrans();
}

Texture *MeshComponent::getTexture() const {
    return texture;
}

const Matrix4 &MeshComponent::getWorldTrans() const {
    return worldTrans;
}

void MeshComponent::computeWorldTrans() {
    worldTrans = scale;
    worldTrans *= rotation;
    worldTrans *= translation;
    worldTrans *= scaleZ;

}


