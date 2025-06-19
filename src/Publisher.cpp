#include "Publisher.h"
#include "Broker.h" 

using namespace std;

Publisher::Publisher(const string& name, Broker* broker)
    : name(name), broker(broker) {
}

void Publisher::publish(const string& topic, const string& message) {
    broker->publish(topic, message);
}

string Publisher::getName() const {
    return name;
}