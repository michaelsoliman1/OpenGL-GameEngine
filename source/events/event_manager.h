//
// Created by michael on ١٧‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_EVENTMANAGER_H
#define GRAPHICS_EVENTMANAGER_H

#include "event.h"

class EventManager{
public:
    Event<int, int, int, int> keyboardEvents;
    Event<double, double> mousePositionEvents;
    Event<int, int, int> mouseButtonEvents;
    Event<double, double> mouseScrollEvents;

};

#endif //GRAPHICS_EVENTMANAGER_H
