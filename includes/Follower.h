#ifndef FOLLOWER_H
#define FOLLOWER_H
using namespace std;
#include <Subscriber.h>
#include <iostream>
#include <string>

class Follower : public Subscriber{




    public:

        Follower(const string& name) : Subscriber(name){};

        void receiveMessage(const string& topic, const string& message) override{
            cout<< getName() << " " << topic << " " << message << endl;
        }

}






#endif // FOLLOWER_H