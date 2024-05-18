/**
 * @file factory_method.cpp
 * @author Sagar Ramdev (sagarramdev173@gmail.com)
 * @brief It demostrates factory method pattern which hides the creation of object from end user returns teh vehicle object irrepective of user vehicle choice
 * @version 0.1
 * @date 2024-05-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>

using namespace std;

/**
 * @brief created vechcile abstract interface  
 * 
 */
class Vehicle{

    public:
    virtual void createvechicle() = 0;
};
/**
 * @brief implemeted car class by inheriting from abstract vehicle
 * 
 */
class Car : public Vehicle{

    public:
    Car(){
        cout << "car object created" << endl;
    }
    void createvechicle(){
        cout << "creating your car" << endl;
    }
};
/**
 * @brief implemeted bike class by inheriting from abstract vehicle
 * 
 */
class bike : public Vehicle{
    public:
    bike(){
        cout << "bike object created" << endl;
    }
    void createvechicle(){
        cout << "creating your bike" << endl;
    }
};

/**
 * @brief created a factory class to get vehicle as per user choice 
 * it hides the implementation of vehicle creation returns a vehicle object.
 */
class VehicalFactory{

    public:
    static Vehicle* getVehicle(string type){
        if(type.compare("car") == 0){
            return new Car();
        }
        else if(type.compare("bike") == 0){
            return new bike();
        }
        else{
            return nullptr;
        }
    }
};
/**
 * @brief main appilcation program
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    Vehicle *home_vehicle = VehicalFactory::getVehicle("bike");
    Vehicle *friend_vehicle = VehicalFactory::getVehicle("car");
    home_vehicle->createvechicle();
    friend_vehicle->createvechicle();
    return 0;
}
