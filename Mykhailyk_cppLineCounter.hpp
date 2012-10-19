
#ifndef CPPLINECOUNTER_HPP
#define	CPPLINECOUNTER_HPP

#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class cppLineCounter 
{
public:    
    cppLineCounter();     
    virtual ~cppLineCounter();
    void printLineCounter();
private:
    void stringParse();
    void whiteSpaceTAB();    
    bool checkEndLine();
    bool commentBeginLong();
    void commentBeginShort();    
    int lineCounter,
        currentPos,
        dataStringSize;    
    string dataString;
};

#endif	/* CPPLINECOUNTER_HPP */