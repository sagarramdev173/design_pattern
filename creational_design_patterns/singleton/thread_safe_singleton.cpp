/**
 * @file thread_safe_singleton.cpp
 * @author Sagar Ramdev (sagar.ramdev@gmail.com)
 * @brief Creates thread safe singleton objects
 * @version 0.1
 * @date 2024-05-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <mutex>
#include <thread>
#include <string>

class singleton{
    /**
     * @brief class to simulate thread safe singelton pattern
     * 
     */
    private:
        static singleton* instance;        
        static std::mutex mtx;
        std::string dummy_value;
        singleton(std::string value){
            dummy_value = value;
        }
        ~singleton(){}
        singleton(const singleton& other) = delete;
        void operator=(const singleton& other) = delete;

    public:
/**
 * @brief Get the instance object
 * 
 * @param value 
 * @return singleton* 
 */
        static singleton *get_instance(const std::string& value){
            if(instance == nullptr){
                mtx.lock();
                if(instance == nullptr){
                instance = new singleton(value);
                }    
                mtx.unlock();
            }
            return instance;
        }
/**
 * @brief Get the dummy value object
 * 
 * @return std::string 
 */
        std::string get_dummy_value(){
            return dummy_value;
        }
    
};
singleton* singleton::instance = nullptr;
std::mutex singleton::mtx;

/**
 * @brief Demo thread function which simulates threading
 * 
 */

void threadfoo(){
    singleton* s1 = singleton::get_instance("fromfoo");
      std::cout << "getting dummy value : " << s1->get_dummy_value() << std::endl;
    
}

void threadbar(){
    singleton* s1 = singleton::get_instance("frombar");
    std::cout << "getting dummy value : " << s1->get_dummy_value() << std::endl;
    
}
/**
 * @brief main function to demo the threadsafe singleton
 * 
 * @return int 
 */
int main(){
    
    /// creating two threads
    std::thread t1(threadfoo);
    std::thread t2(threadbar);
    
    /// joining the threads
    t1.join();
    t2.join();
    
    return 0;   
}