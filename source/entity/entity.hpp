#include <vector>
#include "../components/i_component.hpp"


class Entity{
    std::vector<IComponent*> components;

public:
    Entity() = default;
    ~Entity() = default;
    void addComponent(IComponent* c);
    void removeComponent(IComponent* c);
    std::vector<IComponent*> getComponents();
};