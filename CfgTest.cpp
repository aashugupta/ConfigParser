// Please use gcc or g++ to compile.
// Please use version 4.8 or above
// Please avoid using any external libs or downloaded code
// 
// sample suggested compilation cmds
// /usr/bin/g++ -std=c++11 -c -Wall -Werror -ggdb3  -Iinclude -o bin//obj/CfgTest.o CfgTest.cpp
// /usr/bin/g++ -Wall -Werror -o bin//CfgTest path/CfgTest.o <your class>  -lrt -lm -lstdc++ 


#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<stack>
#include<stdio.h>
#include<cstring>
#include<map>
#include<algorithm>
#include"CBCfg.h"


int main(int argc, char** argv)
{
    std::string cfgFile("test.cfg");

    for(int ii = 1; ii < (argc - 1); ++ii) 
    {
      if (strcmp("-c", argv[ii]) == 0) 
          cfgFile = std::string(argv[ii + 1]); 
      std::cout << "argv[" << ii << "]=" << argv[ii] << std::endl;
    }

    CBCfg &cfg = CBCfg::get(); 
    cfg.parseFile(cfgFile);

    const std::vector<std::string>& vec = cfg.getVector("CRB.MarketData.ServerList");
    const std::string& test = cfg.getString("CRB.MarketData.ServerList");

    std::cout << "TEST : " << test << std::endl;


    for (const std::string& str : vec)
    {
      std::string hostKey = "CRB.MarketData.";
      hostKey.append(str).append(".Host");
      std::cout << hostKey << " - " << cfg.getString(hostKey) << std::endl; 

      std::string portKey = "CRB.MarketData.";
      portKey.append(str).append(".Port");
      std::cout << portKey << " - " << cfg.getLong(portKey) << std::endl; 
    }


    long   keyLong   = cfg.getLong   ("keyLong");std::cout << "keyLong="   << keyLong << std::endl;
    float  keyFloat  = cfg.getFloat  ("keyFloat");std::cout << "keyFloat="  << keyFloat << std::endl;
    double keyDouble = cfg.getDouble ("keyDouble");std::cout << "keyDouble=" << keyDouble << std::endl;

    char               keyChar  = cfg.getChar   ("keyChar");std::cout << "keyChar=" << keyChar << std::endl;
    const std::string& keyStr   = cfg.getString ("keyStr");std::cout << "keyStr=" << keyStr << std::endl;

    const std::string& shmName   = cfg.getString ("ShmName");std::cout << "shmName=" << shmName << std::endl;

    std::vector<std::string> v = cfg.getKey("CRB.MarketData"); 
    for(const std::string& e : v) 
    {
        std::cout << e << std::endl; 
    } 

}
