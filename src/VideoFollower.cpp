#include "VideoFollower.h"
#include <QString>
#include <iostream>

VideoFollower::VideoFollower(const std::string& name)
    : QObject(nullptr), Subscriber(name) {}

void VideoFollower::receiveMessage(const std::string& topic, const std::string& message) {
    std::cout << "VideoFollower (" << this->name << ") recibió en tópico '" << topic << "': " << message << std::endl;
    emit messageProcessed(QString::fromStdString(message));
}