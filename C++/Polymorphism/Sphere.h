/* Stephen Sottosanti */
#pragma once

#include "Shape.h"

class Sphere : public Shape {
public:
    Sphere(const std::string&);
    
    void setRadius(const double&);

    virtual double getArea() override;

    virtual double getVolume() override;         

    virtual bool test(const std::vector<std::string>& cond) override; 

    virtual std::string getInfo() override; 
    

private:
    double radius;   
};