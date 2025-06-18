#ifndef BROKER_H
#define BROKER_H
#include <Subscriber.h>
#include <map>
#include <vector>
using namespace std;


class Broker{
    public:
        void subscribe(const string& topic, Subscriber* subscriber ){
            topics[topic].push_back(subscriber);

        }

        void publish(const string& topic , const string& message){
            for(Subscriber* sub : topics[topic]) {
                sub->receiveMessage(topic, message);
            }
        }


    private:
        map<string, vector<Subscriber*>> topics; 

};




#endif // BROKER_H