/**
 * @file abstract_factory.cpp
 * @author Sagar ramdev (sagarramdev173@gmail.com)
 * @brief Creating abstract GUI factory for windows and linux based operating system
 * @version 0.1
 * @date 2024-05-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
using namespace std;

/**
 * @brief created an interface for button and dialogbox
 * 
 */
class IButton{
    public:
        virtual void press() = 0;        
};

class IDialogBox{
    public:
        virtual void show() = 0;
};

/**
 * @brief created concrete classes for button and dialogbox
 * 
 */
class WindowsButton : public IButton{
    public:
        void press(){
            cout << "windows button pressed" << endl;
        }
};

class WindowsDialogBox : public IDialogBox{
    public:
        void show(){
            cout << "windows dialogbox shown" << endl;
        }
};

class LinuxButton : public IButton{
    public:
        void press(){
            cout << "linux button pressed" << endl;
        }
};  


class LinuxDialogBox : public IDialogBox{
    public:
        void show(){
            cout << "linux dialogbox shown" << endl;
        }
};  

/**
 * @brief created abstract factory class for button and dialogbox
 * 
 */
class IFactory{
    public:
        virtual IButton* createButton() = 0;
        virtual IDialogBox* createDialogBox() = 0;
};

/**
 * @brief created concrete factory class for button and dialogbox
 * 
 */
class WindowsFactory : public IFactory{
    public:
        IButton* createButton(){
            return new WindowsButton();
        }
        IDialogBox* createDialogBox(){
            return new WindowsDialogBox();
        }
};

class LinuxFactory : public IFactory{
    public:
        IButton* createButton(){
            return new LinuxButton();
        }
        IDialogBox* createDialogBox(){
            return new LinuxDialogBox();
        }
};

/**
 * @brief created factory class to get button and dialogbox as per user OS choice
 * 
 */
class GUIFactory{
    public:
        static IFactory* getFactory(string type){
            if(type.compare("windows") == 0){
                return new WindowsFactory();
            }
            else if(type.compare("linux") == 0){
                return new LinuxFactory();
            }
            else{
                return nullptr;
            }
        }
};

/**
 * @brief main appilcation program to demonstrate abstract factory design pattern
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    string ostype = "linux";
    IFactory *mygui = GUIFactory::getFactory(ostype);
    mygui->createButton()->press();
    mygui->createDialogBox()->show();
    return 0;
}
