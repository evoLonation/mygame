#include "actor.h"
#include "component.h"

void Actor::AddComponent(BaseComponent *component) {
    component->owner = this;
    componentMap.insert(std::pair<size_t, BaseComponent*>(typeid(*component).hash_code(), component));
}

