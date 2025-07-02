#include "GPSCarPublisher.h"
#include <iostream>
GPSCarPublisher::GPSCarPublisher(const std::string& name, Broker* broker)
    : Publisher(name, broker) {
    std::cout << "GPSCarPublisher " << name << " creado." << std::endl;
}