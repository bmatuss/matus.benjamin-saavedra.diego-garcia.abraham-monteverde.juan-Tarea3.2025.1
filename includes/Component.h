#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Component{
    protected:
        std::string name;

    public:
        //constructor
        Component(const std::string& name);
        //virtual destructor
        virtual ~Component()=default;

        //getters 
        std::string getName() const;
};
#endif // COMPONENT_H