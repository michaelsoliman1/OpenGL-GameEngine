//
// Created by michael on ٦‏/١‏/٢٠٢١.
//

#ifndef GRAPHICS_EVENT_H
#define GRAPHICS_EVENT_H

#include <functional>
#include <list>
#include <iostream>
#include <string>

using namespace std;


template <typename... Args>
class Event{
    typedef std::function<void(Args...)> EventType;
private:
    std::list<EventType> eventListeners;

public:

    class CBID
    {
    public:
        CBID() : valid(false) {}
    private:
        friend class Event<Args...>;
        CBID(typename std::list<EventType>::iterator i)
                : iter(i), valid(true)
        {}

        typename std::list<EventType>::iterator iter;
        bool valid;
    };

    // register to be notified
    CBID addListener(EventType eventListener)
    {
        if (eventListener)
        {
            eventListeners.push_back(eventListener);
            return CBID(--eventListeners.end());
        }
        return CBID();
    }

    // unregister to be notified
    void deleteListener(CBID &id)
    {
        if (id.valid)
        {
            eventListeners.erase(id.iter);
        }
    }

    void notifyListeners(Args... args)
    {
        for (auto &eventListener : eventListeners)
        {
            eventListener(args...);
        }
    }
};

#endif //GRAPHICS_EVENT_H
