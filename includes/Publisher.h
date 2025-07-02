#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <string>
#include <Broker.h>

class Publisher {
    public:
        Publisher(const std::string& name, Broker* broker);
        void publish(const std::string& topic, const std::string& message);
        std::string getName() const;

    private:
        std::string name;
        Broker* broker;
};

#endif // PUBLISHER_H