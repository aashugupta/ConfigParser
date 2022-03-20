#ifndef __CBCfg_H__
#define __CBCfg_H__

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<stack>
#include<stdio.h>
#include<cstring>
#include<map>
#include<set>
#include<algorithm>

class CBCfg
{
private: 

    std::map<std::string, std::string> keyVals;
    std::map< std::string, std::vector<std::string> > keyValsVector;
    std::map< std::string, std::set<std::string> > keyValsSet;
    CBCfg()  { }

public:

    static CBCfg& get()
    {
        static CBCfg instance;
        return instance;
    }

    CBCfg(CBCfg const&)             = delete;  // Copy constructor
    CBCfg(CBCfg&& )                 = delete;  // Move constructor
    CBCfg& operator=(CBCfg const&)  = delete;  // Copy assignment
    CBCfg& operator=(CBCfg const&&) = delete;  // Move assignment

    void parseFile(std::string& file);

    bool isDelimStart(char c)
    {
        return c == '{';
    }
    bool isDelimEnd(char c)
    {
        return c == '}';
    }

    bool isListSeparator(char c)
    {
        return c == ',';
    }

    long getLong(std::string key);
    float getFloat(std::string key);
    double getDouble(std::string key);
    char getChar(std::string key);
    std::string getString(std::string key);

    std::vector<std::string> getVector(std::string key);
    std::vector<std::string> getKey(std::string key);

    std::vector<std::string> getSubStrings(const std::string & str, char sep);
};


#endif
