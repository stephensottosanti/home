/* Author: Stephen Sottosanti */
#include "Cylinder.h"

using namespace std;

Cylinder::Cylinder(const std::string& name) : Shape(name) {
    this->radius = 0.0; 
    this->height = 0.0;
}

void Cylinder::setCylinder(const double& radius, const double& height) { 
    this->radius = radius; 
    this->height = height;
}

double Cylinder::getArea() { return (2.0 * PI * radius * (radius + height)); } 

double Cylinder::getVolume() { return (PI * pow(radius, 2.0) * height); }         

bool Cylinder::test(const std::vector<std::string>& cond) { 
    bool test = true;
    std::string c1, c2, c3;
    std::string type = "cylinder";
    int loops = cond.size();
    int i = 0;

    while(loops--){
        c1 = cond.at(i);
        loops--;
        c2 = cond.at(i+1);
        loops--;
        c3 = cond.at(i+2);

        if(c1 == "type"){
            if(c2 == "=="){
                if(type == c3){}
                else test = false;
            }
            else if(c2 == "!="){
                if(type != c3){}
                else test = false;
            }
            else if(c2 == ">="){
                if(type >= c3){}
                else test = false;
            }
            else if(c2 == "<="){
                if(type <= c3){}
                else test = false;
            }
            else if(c2 == ">"){
                if(type > c3){}
                else test = false;
            }
            else{ // <
                if(type < c3){}
                else test = false;
            }
        }
        else if(c1 == "area"){
            double area = getArea();
            if(c2 == "=="){
                if(area == stod(c3)){}
                else test = false;
            }
            else if(c2 == "!="){
                if(area != stod(c3)){}
                else test = false;
            }
            else if(c2 == ">="){
                if(area >= stod(c3)){}
                else test = false;
            }
            else if(c2 == "<="){
                if(area <= stod(c3)){}
                else test = false;
            }
            else if(c2 == ">"){
                if(area > stod(c3)){}
                else test = false;
            }
            else{ // <
                if(area < stod(c3)){}
                else test = false;
            }
        }
        else{ // volume
            double volume = getVolume(); 
            if(c2 == "=="){
                if(volume == stod(c3)){}
                else test = false;
            }
            else if(c2 == "!="){
                if(volume != stod(c3)){}
                else test = false;
            }
            else if(c2 == ">="){
                if(volume >= stod(c3)){}
                else test = false;
            }
            else if(c2 == "<="){
                if(volume <= stod(c3)){}
                else test = false;
            }
            else if(c2 == ">"){
                if(volume > stod(c3)){}
                else test = false;
            }
            else{ // <
                if(volume < stod(c3)){}
                else test = false;
            }
        }
        
        i += 3;
    }    

    return test;
} // test if the conditions are statisfied

std::string Cylinder::getInfo() {
   std::stringstream str_stream;

   str_stream << "Cylinder: " << Shape::getName();
   str_stream << ", Radius=" << std::fixed << std::setprecision(2) << radius;
   str_stream << ", Height=" << std::fixed << std::setprecision(2) << height;
   str_stream << "\n\tSurface Area: " << std::fixed << std::setprecision(2) << getArea();
   str_stream << ", Volume: " << std::fixed << std::setprecision(2) << getVolume() << std::endl;

   return str_stream.str();
}