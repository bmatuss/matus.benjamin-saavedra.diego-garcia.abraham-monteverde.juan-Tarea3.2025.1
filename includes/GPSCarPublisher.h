#ifndef GPSCARPUBLISHER_H
#define GPSCARPUBLISHER_H

#include <Publisher.h>
#include <string>
#include <Broker.h>

class GPSCarPublisher : public Publisher {
public:
    GPSCarPublisher(const std::string& name, Broker* broker);
};

#endif // GPSCARPUBLISHER_H