#ifndef _LYLOG_H_
#define _LYLOG_H_

/*** ***
	lyAndLog
	by Shixc 2014-01-28
*** ***/


#include <stdio.h>
#include <iostream>
#include <string>
#include <stdarg.h>
#include <pthread.h>
#include <deque>

using namespace std;

class lyAndLog
{
public:
    lyAndLog();
    virtual ~lyAndLog();
    
    static lyAndLog* getInstance()
    {
        static lyAndLog instance;
        return &instance;
    }
    
    bool initLog(const char* filename);
    void addLog(const char* format, ...);


private:
    void resetAttr();
    
    FILE*   m_pLog;
    char*   m_szBuffLog;
    bool    _bExitLogFile;
    int     _nLogItem;
    char*   _strFileName;
};


#endif
