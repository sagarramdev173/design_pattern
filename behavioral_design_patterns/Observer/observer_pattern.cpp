/**
 * @file observer_pattern.cpp
 * @author Sagar Ramdev (sagarramdev173@gmail.com)
 * @brief This Design Pattern is used to implement observer pattern
 *         where observer act as a subscriber to the service given by publisher or subject
 * @version 0.1
 * @date 2024-05-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include<iostream>
#include<vector>
#include<list>
#include<iterator>
#include<algorithm>
#include <string>
using namespace std;

/**
 * @brief subscriber interface
 * 
 */
class ISubscriber{
    public:
        virtual void notify(string value) = 0;
};

/**
 * @brief User class implements subscriber
 *        where each user is a subscriber with a unique id
 *        and receives notification from the service 
 */
class User: public ISubscriber{
    private:
        int userid;
    public:
        User(int id){
            this->userid = id;
        }
        void notify(string value){
            cout << "User: "<<userid << " notified with: " << value << endl;
        }
};

/**
 * @brief Publisher interface
 *        with basic attach ,detach and notify methods
 * 
 */
class IPublisher{
    public:
        virtual void attach(ISubscriber *sub) = 0;
        virtual void detach(ISubscriber *sub) = 0;
        virtual void notifySubscribers(string) = 0;
};

/**
 * @brief Publisher class implements publisher interface
 *         with basic attach ,detach and notify methods and maintins a list of subscribers
 *          in list of subscribers
 *  
 */
class Publisher: public IPublisher{
    private:
        list<ISubscriber*> subscribers;
    public:
        void attach(ISubscriber *sub){
            subscribers.push_back(sub);
        }
        void detach(ISubscriber *sub){
            subscribers.remove(sub);
        }
        void notifySubscribers(string msg){
            for(auto sub: subscribers){
                sub->notify(msg);
            }
        }
};

/**
 * @brief main function to test the observer pattern
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    User *user1 = new User(1);
    User *user2 = new User(2);
    User *user3 = new User(3);
    Publisher *pub = new Publisher();
    pub->attach(user1);
    pub->attach(user2);
    pub->attach(user3);
    pub->notifySubscribers("Hello World");
    pub->detach(user2);
    pub->notifySubscribers("Hello India");
    return 0;
}
