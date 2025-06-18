#ifndef RECORDER_H
#define RECORDER_H
#include <fstream>
#include <Subscriber.h>
#include <string>
using namespace std;
class Recorder : public Subscriber{

    public:

        Recorder (const string& name, const string& fileName );
        ~Recorder();


        virtual void receiveMessage(const string& topic, const string& message) override;



    private:
        ofstream file; 

    


};

#endif // RECORDER_H