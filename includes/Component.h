#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>
using namespace std;



class Component{
    protected:
        string name;



    public:
        //constructor
        Component(string name) : name(name) {}
        //virtual destructor
        virtual ~Component()=default;

        //getters 
        string getName() const {
            return name;
        }
};






#endif // COMPONENT_H