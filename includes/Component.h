#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Component{
    protected:
        std::string name;

    public:
        Component(const std::string& name);
        virtual ~Component() = default;
        std::string getName() const;
};
#endif // COMPONENT_H