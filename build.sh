#!/bin/bash

g++ -std=c++11 -c -Wall -Werror -ggdb3  -Iinclude -o bin/obj/CfgTest.o CfgTest.cpp
g++ -std=c++11 -c -Wall -Werror -ggdb3  -Iinclude -o bin/obj/CBCfg.o CBCfg.cpp
g++ -Wall -Werror -o bin/CfgTest bin/obj/CfgTest.o bin/obj/CBCfg.o  -lrt -lm -lstdc++

