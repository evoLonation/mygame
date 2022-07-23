#pragma once
#include"math.h"
#include "texture.h"

class BaseComponent{
    public:
    BaseComponent() = default;
    ~BaseComponent() = default;
    virtual void Update() = 0;

//    static class MeshComponent* CreateMeshComponent(const std::string &modelName, const std::string& textureName);

};

class MeshComponent : BaseComponent{
    public:
    MeshComponent(class Model* model, class Texture* texture);
    ~MeshComponent();
    // to actor
    void Update() override;

    private:
    class Model* model;
    class Texture* texture;
    Matrix4 scale;
    Matrix4 rotation;
    Matrix4 translation;
    Matrix4 scaleZ;
    Matrix4 worldTrans;
    void computeWorldTrans();
public:
    Model *getModel() const;

    Texture *getTexture() const;

    const Matrix4 &getWorldTrans() const;

    void setScale(float scale);
};