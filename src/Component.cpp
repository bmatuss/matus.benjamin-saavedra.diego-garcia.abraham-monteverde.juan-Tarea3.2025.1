#include "Component.h"

using namespace std;

Component::Component(const string& name) : name(name) {}

string Component::getName() const {
    return name;
}