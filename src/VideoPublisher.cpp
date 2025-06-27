#include <VideoPublisher.h>
#include <iostream>

VideoPublisher::VideoPublisher(const std::string& name, Broker* broker)
    : Publisher(name, broker) {
    std::cout << "VideoPublisher " << name << " creado." << std::endl;
}