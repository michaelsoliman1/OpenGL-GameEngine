

#include <vector>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <iostream>

#include "../components/i_component.hpp"


class Entity{
    std::unordered_map<std::type_index, IComponent*> components = {};
public:
    int id;
    std::string tag;

    explicit Entity(int _id, std::string _tag = ""){
        id=_id;
        //why should i use std_move??
        tag = std::move(_tag);
    };
    ~Entity() = default;

    template<typename T>
    void addComponent(T c){
        components[std::type_index(typeid(*c))] = c;
    };

    template<typename T>
    IComponent* getComponentByType(T c){
        return this->components[std::type_index(typeid(*c))];
    };

    std::unordered_map<std::type_index, IComponent*> getAllComponents(){
        return components;
    };

    template<typename T>
    void removeComponent(T* c){
        components.erase(std::type_index(typeid(c)));
    }
};

