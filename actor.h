#pragma once
#include "component.h"

class Actor{
public:
    Actor() = default;
    void AddComponent(class BaseComponent* component);
    BaseComponent * GetComponent(Component_Type type);

private:
    std::map<Component_Type, BaseComponent*> componentMap;


};