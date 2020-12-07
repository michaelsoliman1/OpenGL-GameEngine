#include <vector>
#include "../components/i_component.hpp"


class Entity{
    std::vector<IComponent*> components;
public:
    Entity() = default;
    ~Entity();
    int size();
    void addComponent(IComponent* c);
    void removeComponent(IComponent* c);
    void getComponent(IComponent* c);
    std::vector<IComponent*> renderComponents();
};