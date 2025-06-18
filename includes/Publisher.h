#ifndef PUBLISHER_H
#define PUBLISHER_H
#include <Broker.h>



class Publisher {
    public:
        Publisher(const string& name, Broker* broker) 
            : name(name), broker(broker) {};

        void publish(const string& topic , const string& message){
            broker->publish(topic, message);
        }

        string getName() const {
            return name;
        }

    private:
        string name;
        Broker* broker; //puntero al broker , solo usa

    };

#endif // PUBLISHER_H