#pragma once
#include"math.h"
#include "texture.h"
#include "actor.h"


class Actor;

class BaseComponent{
public:
    BaseComponent() = default;
    ~BaseComponent() = default;
    virtual void Update() = 0;


    Actor *GetOwner() const;

protected:
    Actor* owner = nullptr;
    friend void Actor::AddComponent(class BaseComponent* component);;

};

class MeshComponent : public BaseComponent{
public:
    MeshComponent(class Model* model, class Texture* texture);
    ~MeshComponent();
    // to actor
    void Update() override;


private:
    class Model* model;
    class Texture* texture;
    BaseMatrix4 scale;
    BaseMatrix4 rotation;
    BaseMatrix4 translation;
    BaseMatrix4 scaleZ;
    BaseMatrix4 worldTrans;
    void computeWorldTrans();
public:
    Model *getModel() const;

    Texture *getTexture() const;

    const BaseMatrix4 getWorldTrans() const;

    void setScale(float scale);

    void setTranslation(float x, float y, float z);
};

/**
 * 定义和修改actor的位置及朝向
 */
class LocationComponent : public BaseComponent {
public:

public:
    LocationComponent() = default;
    //下面的两个函数用于初始化位置
    void SetLocation(float x, float y, float z);
    /**
     * @param front actor面朝的方向（z轴的方向）
     * @param theta 根据右手定则旋转的角度（如果为0，代表x轴平行于世界坐标的xy面）
     */
    void SetDirection(const Vector3 &front, float theta);
    //下面的函数用于在初始化的基础上进一步移动
    void TranslateZ(float distance);
    void TranslateX(float distance);
    void TranslateY(float distance);
    void RotateY(float theta);


    void Update() override;
    const Matrix4& GetWorldTrans();
    const Matrix4& GetWorldTransInverse();


private:
    TranslationMatrix translation;
    OrthogonalMatrix rotate;
    Matrix4 worldTrans = MatrixFactory::CreateUnitary();
    Matrix4 worldTransInverse = MatrixFactory::CreateUnitary();

    void Compute();

};

class CameraComponent : public BaseComponent {
public:
    void Update() override;

    CameraComponent() = default;
    void SetProjection(float width, float height, float near, float far);
    const Matrix4& GetProjection();
private:
    Matrix4 perspectiveProjection = MatrixFactory::CreatePerspectiveProjection(1, 1, 1, 2);

};