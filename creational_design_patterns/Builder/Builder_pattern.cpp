/**
 * @file Builder_pattern.cpp
 * @author Sagar Ramdev (sagarramdev173@gmail.com)
 * @brief Builder design pattern is used to create a complex object using simple objects aka Builder
 * @version 0.1
 * @date 2024-05-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>

using namespace std;

/**
 * @brief Defining common product which will be created by builder
 * 
 */
class Desktop
{
    private:
    string monitor;
    string keyboard;
    string mouse;
    public:    
    string getMonitor(){return monitor;}
    string getKeyboard(){return keyboard;}
    string getMouse(){return mouse;}
    void setMonitor(string monitor){this->monitor = monitor;}
    void setKeyboard(string keyboard){this->keyboard = keyboard;}
    void setMouse(string mouse){this->mouse = mouse;}   
    void showSpec(){
        cout << "Desktop Spec: " << monitor << " " << keyboard << " " << mouse << endl;
    }
};

/**
 * @brief Defining the abstract builder Desktop which is a interface for creating complex object
 *        by different concrete builders.
 * 
 */
class DesktopBuilder {
    protected:
    Desktop *desktop;
    public:
    DesktopBuilder(){
        desktop = new Desktop();
    }
    virtual void buildMonitor() = 0;
    virtual void buildKeyboard() = 0;
    virtual void buildMouse() = 0;
    virtual Desktop* getDesktop(){return desktop;}    
};

/**
 * @brief Gaming Desktop Builder is a concrete builder which will build gaming desktop
 * 
 */
class GamingDesktopBuilder : public DesktopBuilder{
    public:
    void buildMonitor(){
        desktop->setMonitor("Gaming monitor");
    }
    void buildKeyboard(){
        desktop->setKeyboard("Gaming keyboard");
    }
    void buildMouse(){
        desktop->setMouse("Gaming mouse");
    }
};

/**
 * @brief Normal Desktop Builder is a concrete builder which will build normal desktop
 * 
 */
class NormalDesktopBuilder : public DesktopBuilder{
    public:
    void buildMonitor(){
        desktop->setMonitor("Normal monitor");
    }
    void buildKeyboard(){
        desktop->setKeyboard("Normal keyboard");
    }
    void buildMouse(){
        desktop->setMouse("Normal mouse");
    }
};

/**
 * @brief Desktop Director is a class which will use builder to build complex desktop object
 * 
 */
class DesktopDirector{
    private:
    DesktopBuilder *builder;
    public:
    void setBuilder(DesktopBuilder *builder){
        this->builder = builder;
    }
    Desktop* getDesktop(){
        builder->buildMonitor();
        builder->buildKeyboard();
        builder->buildMouse();
        return builder->getDesktop();
    }
};

/**
 * @brief main function to test the builder pattern
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    /// creating Desktop director and different concrete desktop builder
    DesktopDirector *director = new DesktopDirector();
    NormalDesktopBuilder *builder1 = new NormalDesktopBuilder();
    GamingDesktopBuilder *builder2 = new GamingDesktopBuilder();

    /// using director to set builder and get desktop
    director->setBuilder(builder1);   
    Desktop *desktop = director->getDesktop();
    /// showing desktop spec
    desktop->showSpec();
    director->setBuilder(builder2);
    desktop = director->getDesktop();
    desktop->showSpec();
    return 0;
}
