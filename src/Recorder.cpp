#include "Recorder.h"
#include <sstream>

using namespace std;

Recorder::Recorder(const string& name, const string& filename)
    : Subscriber(name), file(filename, ios::out | ios::app) {}

Recorder::~Recorder() {
    if (file.is_open()) {
        file.close();
    }
}

void Recorder::receiveMessage(const string& topic, const string& message) {
    string x_str, y_str;
    int x = 0, y = 0;

    istringstream iss(message);
    if (getline(iss, x_str, ',') && getline(iss, y_str)) {
        if (x_str.rfind("x=", 0) == 0) {
            x = stoi(x_str.substr(2));
        }
        if (y_str.rfind("y=", 0) == 0) {
            y = stoi(y_str.substr(2));
        }
    }

    if (file.is_open()) {
        file << name << "," << topic << "," << x << "," << y << "\n";
    }
}