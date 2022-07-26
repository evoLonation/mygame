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
    Model *GetModel() const;

    Texture *getTexture() const;

    BaseMatrix4 getWorldTrans() const;

    void GetScale(float scale);

    void setTranslation(float x, float y, float z);
};

/**
 * 定义和修改actor的位置及朝向
 * 所有位置变化可以分为两种类型：
 * 相对于世界空姐的变化：初始化Set成员等等
 * 相对于目前的模型空间的变化
 *
 * 每次执行Set类的成员函数时，都会重置之前所有的相对于模型空间的变化
 *
 *
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
    //根据本坐标系中的一个轴来旋转
    void RotateByAxis(const Vector3& start, const Vector3& vector, float theta);


    void Update() override;
    const Matrix4& GetWorldTrans();
    const Matrix4& GetWorldTransInverse();


private:
    TranslationMatrix translation;
    OrthogonalMatrix rotate;
    bool isInitialization = true;

    Matrix4 worldTrans = MatrixFactory::CreateUnitary();
    Matrix4 worldTransInverse = MatrixFactory::CreateUnitary();

    //每个Set函数执行前执行的
    void Initialization();
    //每个Set函数执行后执行的
    void Compute();

    // 添加新的变换（在现在模型空间基础上）
    void AddTransform(const TranslationMatrix& matrix);
    void AddTransform(const OrthogonalMatrix& matrix);

};

class CameraComponent : public BaseComponent {
public:
    void Update() override;

    CameraComponent() = default;
    void SetProjection(float width, float height, float near, float far);
    // 以近平面为轴进行转动
    void RotateByNearY();
    const Matrix4& GetProjection();
private:
    Matrix4 perspectiveProjection = MatrixFactory::CreatePerspectiveProjection(1, 1, 1, 2);

};