/* Author: Stephen Sottosanti */
#pragma once

#include "Shape.h"

class Cylinder : public Shape {
public:
   Cylinder(const std::string&);
   void setCylinder(const double&, const double&);

   virtual double getArea() override;

   virtual double getVolume() override;         

   virtual bool test(const std::vector<std::string>& cond) override; 

   virtual std::string getInfo() override; 

private:
    double radius;
    double height;   
};
