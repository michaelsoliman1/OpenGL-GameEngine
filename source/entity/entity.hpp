#include <vector>
#include "../components/i_component.hpp"


class Entity{
    std::vector<IComponent*> components;
public:
    Entity() = default;
    ~Entity();
    void addComponent(IComponent* c);
    void removeComponent(IComponent* c);
};