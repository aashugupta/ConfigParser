#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<stdio.h>
#include<cstring>
#include<sstream>
#include"CBCfg.h"


void CBCfg::parseFile(std::string& file)
{
    std::ifstream cfgFile(file);
    std::string line;
    std::string contentWithoutSpaces;

    while(std::getline(cfgFile, line))
    {
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

        if(line == "") // empty line, skip it
            continue;
        contentWithoutSpaces += line;
    }

    std::string currToken ;
    std::string key;
    std::string val;
    int delimStartCount = 0;
    for(size_t i = 0; i < contentWithoutSpaces.size() ; ++i )
    {
        if(isDelimStart(contentWithoutSpaces[i]))
        {
            //std::cout << "Got opening delimiter delimStartCount : "  << delimStartCount << std::endl;

            if( delimStartCount )
                key = key + "." + currToken;
            else
                key  = currToken;

            delimStartCount += 1;

            currToken = "";
        }
        else if(isDelimEnd(contentWithoutSpaces[i]))
        {
            //std::cout << "Got close delimiter delimStartCount : "  << delimStartCount << std::endl;

            val = currToken;
            
            keyVals[key] = val;

            currToken = "";
            size_t findDot = key.find_last_of(".");
            if(findDot  != std::string::npos)
            {
                std::string prevKeyLastPart = key.substr(findDot+1);
                key = key.substr(0,findDot);

                if(keyValsSet.find(key) == keyValsSet.end())
                {
                   std::set<std::string> keySet ;
                   keySet.insert(prevKeyLastPart); 
                   keyValsSet[key] = keySet;
                }
                else
                {
                   keyValsSet[key].insert(prevKeyLastPart);
                }

            }
            delimStartCount -= 1;
            if(!delimStartCount)
            {
                key = "";
            }
        }
        else
        {

            currToken += contentWithoutSpaces[i];

            //std::cout << "currToken : " << currToken <<  " key : " << key <<  std::endl;
        }

    }

    for(const auto& kv : keyVals)
    {
        //std::cout << "Key : " << kv.first << " Value : " << kv.second << std::endl;
       
        size_t pos = kv.second.find(",");
        if(pos != std::string::npos)
        {
            std::vector<std::string> list  = getSubStrings(kv.second, ',') ;
            keyValsVector[kv.first] = list;
        }
    }
 
    for(const auto& kv : keyValsSet)
    {
        for(const auto& val : kv.second)
        {
            //std::cout << "keyValsSet : Key : " << kv.first << " Val : "  << val <<  std::endl;
            if(keyValsVector.find(key) == keyValsVector.end()) 
                keyValsVector[kv.first].push_back(val);
        }
    }
   
}

std::vector<std::string> CBCfg::getSubStrings(const std::string & str, char sep)
{
    std::vector<std::string> list;
    std::stringstream ss(str);
    while(ss.good())
    {
        std::string substr;
        getline( ss, substr, sep);
        list.push_back(substr);
    }

    return list; // list is converted to r-value and return value is move constructed.
}

long CBCfg::getLong(std::string key)
{
    std::string str = getString(key);

    long val = std::stol(str);
    return val;
}

float CBCfg::getFloat(std::string key)
{
    std::string str = getString(key);
    float val = std::stof(str);
    return val;
}

double CBCfg::getDouble(std::string key)
{
    std::string str = getString(key);
    double val = std::stod(str);
    return val;
}

char CBCfg::getChar(std::string key)
{
    std::string str = getString(key);
    return str[0];
}

std::string CBCfg::getString(std::string key)
{
    std::string ret = "";
    if(keyVals.find(key) != keyVals.end())
        ret = keyVals[key];

    return ret;
}

std::vector<std::string> CBCfg::getVector(std::string key)
{
    return getKey(key);
}

std::vector<std::string> CBCfg::getKey(std::string key)
{
    std::vector<std::string> retVector;

    //std::cout << "Checking for key : " << key << std::endl;
    if(keyValsVector.find(key) != keyValsVector.end())
    {
        retVector = keyValsVector[key];
    }
    
    return retVector;
}

