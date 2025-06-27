#ifndef VIDEOPUBLISHER_H
#define VIDEOPUBLISHER_H

#include <Publisher.h>
#include <string>
#include <Broker.h>

class VideoPublisher : public Publisher {
public:
    VideoPublisher(const std::string& name, Broker* broker);
};

#endif // VIDEOPUBLISHER_H
