#ifndef BROKER_H
#define BROKER_H

#include <string>
#include <map>
#include <vector>
#include <Subscriber.h> 

class Broker{
    public:
        void subscribe(const std::string& topic, Subscriber* subscriber);
        void publish(const std::string& topic , const std::string& message);
    private:
        std::map<std::string, std::vector<Subscriber*>> topics;
};
#endif // BROKER_H