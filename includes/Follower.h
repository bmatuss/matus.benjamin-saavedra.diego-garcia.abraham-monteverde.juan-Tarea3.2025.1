#ifndef FOLLOWER_H
#define FOLLOWER_H

#include <Subscriber.h>
#include <string>

class Follower : public Subscriber{
    public:
        Follower(const std::string& name);
        ~Follower() override = default; 
        void receiveMessage(const std::string& topic, const std::string& message) override;
};
#endif // FOLLOWER_H