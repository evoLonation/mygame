#include "actor.h"


void Actor::AddComponent(BaseComponent *component) {
    component->SetOwner(this);
    componentMap.insert(std::pair<Component_Type, BaseComponent*>(component->GetType(), component));
}

BaseComponent* Actor::GetComponent(Component_Type type) {
    return componentMap[type];
}
