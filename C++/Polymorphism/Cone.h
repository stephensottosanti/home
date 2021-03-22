/* Stephen Sottosanti */
#pragma once

#include "Shape.h"

class Cone : public Shape {
public:
    Cone(const std::string&);

    void setCone(const double&, const double&);

    virtual double getArea() override;

    virtual double getVolume() override;         

    virtual bool test(const std::vector<std::string>& cond) override; 

    virtual std::string getInfo() override; 

private:
    double radius;
    double height;   
};