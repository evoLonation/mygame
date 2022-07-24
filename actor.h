#pragma once

#include <map>
#include <typeinfo>


class BaseComponent;

class Actor{
public:
    Actor() = default;
    void AddComponent(class BaseComponent* component);

    template<class T>
    T* GetComponent(){
        return static_cast<T*>(componentMap[typeid(T).hash_code()]);
    }

private:
    std::map<std::size_t, BaseComponent*> componentMap;


};