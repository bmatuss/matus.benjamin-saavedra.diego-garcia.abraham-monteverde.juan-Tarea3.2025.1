#ifndef BROKER_H
#define BROKER_H

#include <string>
#include <map>
#include <vector>
#include <Subscriber.h> 

class Broker{
    public:
        Broker(const std::string& defaultTopic);
        void subscribe(const std::string& topic, Subscriber* subscriber);
        void publish(const std::string& topic , const std::string& message);
        std::string getDefaultTopic() const;
    private:
        std::string defaultTopic;
        std::map<std::string, std::vector<Subscriber*>> topics;
};
#endif // BROKER_H