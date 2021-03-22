/* Author: Stephen Sottosanti */
#pragma once

#include "Shape.h"

class Cuboid : public Shape {
public:
   Cuboid(const std::string&);
   void setCuboid(const double&, const double&, const double&);
    
   virtual double getArea() override;

   virtual double getVolume() override;         

   virtual bool test(const std::vector<std::string>& cond) override; 

   virtual std::string getInfo() override;

private:
    double length;
    double width;
    double height;   
};
