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

    string dummy_value;

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
 * @brief The singleton should not be cloneable
 * 
 * @param singleton_pattern object
 */
    singelton_pattern (const singelton_pattern& other) = delete;

/**
 * @brief Singlteon should nto be assignable 
 * 
 * @param singleton_pattern object
 */
    void operator=(const singelton_pattern& other) = delete;

/**
 * @brief Get the singleton object object  
 * @return singelton_pattern object refernce 
 */
static singelton_pattern* get_singleton_object(){
    
    if(instance == nullptr){
        instance = new singelton_pattern();
    }
    return instance;
    }
/**
 * @brief Get the instance count object
 *  (how many insatcens fo the class is avaiable)   
 * @return int 
 */
static int get_instance_count(){
    return instance_count;
}

/**
 * @brief Set the dummy value object
 * 
 * @param string value 
 */
void set_dummy_value(string value){
    dummy_value = value;
}
/**
 * @brief Get the dummy value object
 * 
 * @return string 
 */
string get_dummy_value(){
    return dummy_value;
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
    singelton_pattern *s1 = singelton_pattern::get_singleton_object();    
    singelton_pattern *s2 = singelton_pattern::get_singleton_object();

    //setting the dummy vlaue and observing that only one instance is created
    s1->set_dummy_value("demo");
    std::cout << "Getting the object dumy value : " << s2->get_dummy_value() << std::endl;
    
    std::cout << "instance count : " << singelton_pattern::get_instance_count() << std::endl;
    return 0;
}
