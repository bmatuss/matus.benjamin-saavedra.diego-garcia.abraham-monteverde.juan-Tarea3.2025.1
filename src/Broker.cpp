#include "Broker.h"
#include "Subscriber.h"

using namespace std;

Broker::Broker(const string& defaultTopic) : defaultTopic(defaultTopic) {}

void Broker::subscribe(const string& topic, Subscriber* subscriber) {
    topics[topic].push_back(subscriber);
}

void Broker::publish(const string& topic, const string& message) {
    for (Subscriber* sub : topics[topic]) {
        sub->receiveMessage(topic, message);
    }
}

string Broker::getDefaultTopic() const {
    return defaultTopic;
}