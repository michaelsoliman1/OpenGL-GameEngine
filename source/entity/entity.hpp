#include "../components/i_component.hpp"
#include <unordered_map>
#include "string"

class Entity{
    std::unordered_map<int, IComponent*> components;
public:
    Entity();
    ~Entity();
    void addComponent(int id, IComponent* c);
    void removeComponent(IComponent* c);
    void getComponent(IComponent* c);
};