#include "GPSCarFollower.h"
#include <iostream>
#include <QDebug>

GPSCarFollower::GPSCarFollower(const std::string& name) 
    : QObject(), Subscriber(name) {
    qDebug() << "GPSCarFollower creado:" << QString::fromStdString(name);
}

void GPSCarFollower::receiveMessage(const std::string& topic, const std::string& message) {
    qDebug() << "GPSCarFollower recibió mensaje en topic:" << QString::fromStdString(topic) 
             << "Mensaje:" << QString::fromStdString(message);
    
    emit messageProcessed(QString::fromStdString(message));
}
