//
// Created by michael on ٦‏/١٢‏/٢٠٢٠.
//

#include "entity.hpp"

void Entity::addComponent(IComponent *c) {
    components.push_back(c);
}