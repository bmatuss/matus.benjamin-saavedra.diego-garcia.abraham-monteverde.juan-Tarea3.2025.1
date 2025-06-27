#ifndef VIDEOFOLLOWER_H
#define VIDEOFOLLOWER_H

#include <QObject>
#include <Subscriber.h>
#include <string>

class VideoFollower : public QObject, public Subscriber {
    Q_OBJECT

public:
    VideoFollower(const std::string& name);
    ~VideoFollower() override = default;
    void receiveMessage(const std::string& topic, const std::string& message) override;

signals:
    void messageProcessed(const QString &message);
};
#endif // VIDEOFOLLOWER_H