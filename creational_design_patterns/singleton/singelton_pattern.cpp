/**
 * @file singelton_pattern.cpp
 * @author sagar ramdev 
 * @brief Creates singletion object for the class
 * @version 0.1
 * @date 2024-05-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>

using namespace std;

class singelton_pattern
{
private:
    /* data */
    // @brief singelton object which is static class member variable    
    static singelton_pattern *instance;
    static int instance_count;

    /**
     * @brief Construct a new singelton pattern object
     * ( Making contructor private so that we will have more control on object creation)
     *    
     */
    singelton_pattern(){
    std::cout << "singleton_pattern classs object created" << std::endl;
    instance_count++;
    }

public:
/**
 * @brief Destroy the singelton pattern object
 * 
 */
    ~singelton_pattern()
    {
        if(instance != nullptr && instance_count){
        std::cout << "singleton_pattern classs object destroyed" << std::endl;
        instance_count--;
        delete instance;        
        instance = nullptr;        
        }
    }
/**
 * @brief Get the singleton object object  
 * @return singelton_pattern object refernce 
 */
static singelton_pattern& get_singleton_object(){
    
    if(instance == nullptr){
        instance = new singelton_pattern();
    }
    return *instance;
    }
/**
 * @brief Get the instance count object
 *  (how many insatcens fo the class is avaiable)   
 * @return int 
 */
static int get_instance_count(){
    return instance_count;
}
};

/// @brief class member variable intilization
singelton_pattern *singelton_pattern::instance = nullptr;
int singelton_pattern::instance_count = 0;

/**
 * @brief 
 * 
 * @param argc no of argument passed from command line to singleton binary
 * @param argv arguments from command line to singleton binary
 * @return int 
 */
int main(int argc, char const *argv[])
{
    /* code */
    std::cout << "instance count : " << singelton_pattern::get_instance_count() << std::endl;
    singelton_pattern s1 = singelton_pattern::get_singleton_object();
    singelton_pattern s2 = singelton_pattern::get_singleton_object();
    std::cout << "instance count : " << singelton_pattern::get_instance_count() << std::endl;
    return 0;
}
