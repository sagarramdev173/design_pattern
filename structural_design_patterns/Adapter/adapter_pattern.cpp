/**
 * @file adapter_pattern.cpp
 * @author Sagar ramdev (sagarramdev173@gmail.com)
 * @brief Implementing adapter pattern where we can convert XML data to JSON data
 * @version 0.1
 * @date 2024-05-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>

using namespace std;

/**
 * @brief Xml data class which contains xml data
 * 
 */
class XMLData{
    private:
    string _xmldata;
    public:
        XMLData(string data) : _xmldata(data){}
       string getXMLData(){
           return _xmldata;
       }
};

/**
 * @brief Data analytics tool class which process the json data given to it
 * 
 */
class DataAnalyticsTool{
    private:
    string _JsonData;
    public:
        DataAnalyticsTool(){};
        DataAnalyticsTool(string data) : _JsonData(data){};
        virtual void analyseData(){
            cout << "analyzing data in data analytics tool: " << _JsonData << endl;
        }
};

/**
 * @brief client class which process the data given by data analytics tool
 * 
 */
class client{
    public:
    void ProcessData(DataAnalyticsTool* tool){        
        cout<<"inside the client class, i'm going to process the data"<<endl;
        tool->analyseData();
    }
};

/**
 * @brief Adapter class which converts xml data to json and overrides the analyseData method
 *         in which it will process the xml data but gives the simulation that it
 *         processing json data
 * 
 */
class Adapter: public DataAnalyticsTool{
    private:
    XMLData * pXMLdata;
    public:
    Adapter(XMLData* pXMLdata) {
        this ->pXMLdata = pXMLdata;
    }
    void analyseData() override{
        string data = pXMLdata->getXMLData();
        cout<< "Converting XML to JSON: " << data << endl;             
    }
};

/**
 * @brief main appilcation program to demonstrate adapter pattern
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    XMLData *data = new XMLData("My sample XML data");
    DataAnalyticsTool *tool = new Adapter(data);
    client *app_client = new client();
    app_client->ProcessData(tool);
    return 0;
}
