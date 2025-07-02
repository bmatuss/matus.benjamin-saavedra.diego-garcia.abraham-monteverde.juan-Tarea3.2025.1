#ifndef GPSCARFOLLOWER_H
#define GPSCARFOLLOWER_H

#include <QObject>
#include <Subscriber.h>
#include <string>

class GPSCarFollower : public QObject, public Subscriber {
    Q_OBJECT

public:
    GPSCarFollower(const std::string& name);
    ~GPSCarFollower() override = default;
    void receiveMessage(const std::string& topic, const std::string& message) override;

signals:
    void messageProcessed(const QString &message);
    
};
#endif // GPSCARFOLLOWER_H