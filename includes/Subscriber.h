#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H
#include <Component.h>
#include <string>

class Subscriber : public Component{
    public:
        Subscriber(const std::string& name) : Component(name) {}
        virtual ~Subscriber() = default;
        virtual void receiveMessage(const std::string& topic, const std::string& message) = 0;
};

#endif // SUBSCRIBER_H