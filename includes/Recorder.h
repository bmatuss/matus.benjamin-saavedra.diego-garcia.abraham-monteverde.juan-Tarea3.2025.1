#ifndef RECORDER_H
#define RECORDER_H
#include <fstream>
#include <Subscriber.h>
#include <string>

class Recorder : public Subscriber{
    public:
        Recorder (const std::string& name, const std::string& fileName );
        ~Recorder();

        void receiveMessage(const std::string& topic, const std::string& message) override;

    private:
        // std::ofstream must be used if 'using namespace std;' is removed
        // and fstream is included.
        std::ofstream file;
};

#endif // RECORDER_H