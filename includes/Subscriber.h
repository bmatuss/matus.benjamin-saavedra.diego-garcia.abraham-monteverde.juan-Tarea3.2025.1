#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H
#include <Component.h>
#include <string>
using namespace std;



class Subscriber : public Component{
    protected:

    public:
        Subscriber(const string& name) : Component(name) {}
        virtual ~Subscriber() {};

        virtual void receiveMessage(const string& topic, const string& message) = 0;

    }



    






#endif // SUBSCRIBER_H