#include "Follower.h"
#include <iostream>

using namespace std;

Follower::Follower(const string& name) : Subscriber(name) {}

void Follower::receiveMessage(const string& topic, const string& message) {
    cout << getName() << " received on topic '" << topic << "': " << message << endl;
}