
#include "Mykhailyk_cppLineCounter.hpp"

cppLineCounter::cppLineCounter() 
{        
    lineCounter = 0;
    stringParse();    
}

bool cppLineCounter::commentBeginLong()
{
    for(; currentPos <= dataStringSize; ++ currentPos)
    {
        if(dataString[currentPos] == '*')       
            if(checkEndLine())
                if(dataString[currentPos + 1] == '/')
                {
                    ++ currentPos;
                    return true;
                }        
    }
    return false;
}

void cppLineCounter::commentBeginShort()
{
    if(checkEndLine())    
        if(dataString[++ currentPos] == '/')
            while(dataStringSize >= currentPos)
            {
                ++ currentPos;
            }                   
}

void cppLineCounter::whiteSpaceTAB()
{
    while(dataString[currentPos] == ' ' || dataString[currentPos] == '\t')
    {
        ++ currentPos;
    }
    -- currentPos;  // for main loop
}

bool cppLineCounter::checkEndLine()
{
    return dataStringSize >= currentPos;
}

void cppLineCounter::stringParse()
{
    bool longCommentEnd = true, 
         cppLine = false;

    ifstream inpFile;    
    string fName;
    cout << "Input fName: ";
    cin >> fName;    
        
    inpFile.open(fName);
  
    if(inpFile.is_open())   
    {
        while(getline(inpFile, dataString))
        {                    
            dataStringSize = dataString.size();
            for(currentPos = 0; currentPos < dataStringSize; ++ currentPos)      // main loop
            {                        
                if(!longCommentEnd)
                    longCommentEnd = commentBeginLong();
                else
                {
                    switch(dataString[currentPos])
                    {
                        case '/' : 
                        {
                            // comment begin       
                            if(checkEndLine())
                            {
                                if(dataString[currentPos + 1] == '*')                            
                                    // multiline comment
                                    longCommentEnd = commentBeginLong();
                                else                        
                                    if(dataString[currentPos + 1] == '/')
                                        // inline comment
                                        commentBeginShort();
                                    else
                                        // cpp string
                                        if(!cppLine)
                                            cppLine = true;
                            }                        
                            break;
                        }  
                        case ' ' :
                        {
                            // white space
                            whiteSpaceTAB();
                            break;
                        }
                        case '\t' : 
                        {
                            // TAB
                            whiteSpaceTAB();
                            break;
                        }
                        default : 
                        {
                            // cpp string
                            if(!cppLine)
                                cppLine = true;
                            break;
                        }
                    }
                }
            }
            if(cppLine)
            {
                ++ lineCounter;
                cppLine = false;
            }
        }
        inpFile.close();
    }
    else
        cout << "File !open." << endl;
    
}

void cppLineCounter::printLineCounter()
{
    cout << lineCounter << endl;
}

cppLineCounter::~cppLineCounter() 
{
    dataString.clear();    
}