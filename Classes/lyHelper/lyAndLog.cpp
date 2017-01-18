#include "lyAndLog.h"

#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <stdarg.h>
#include <pthread.h>



using namespace std;


#include "cocos2d.h"

#define LOG_NAME_LEN    50
#define LOG_BUFF_SIZE   (1024*1024)
#define LOG_PATH    "/mnt/sdcard/"
#define LOG_EXT     ".txt"
#define LOG_MAX_ITEM 10000


lyAndLog::lyAndLog()
{
    resetAttr();
}
lyAndLog::~lyAndLog()
{
    resetAttr();
}
void lyAndLog::resetAttr()
{
    _bExitLogFile = false;
    _nLogItem = 0;
    if(m_pLog != NULL)
    {
        fclose(m_pLog);
    }
    m_szBuffLog = new char[LOG_BUFF_SIZE];
    memset(m_szBuffLog, '\0', sizeof(m_szBuffLog));
    
    
    _szAccountid = (char*)malloc(sizeof(char)*LOG_NAME_LEN);
}



bool lyAndLog::initLog(const char* accountid)
{
    //1、登录成功调用此接口，初始化log文件
    //2、每次登录要重新创建该文件，每个account用户，只保存本次登录log
    //3、打开该文件，保存属性变量
    //4、返回
    resetAttr();

    char log_name[256] = {0};
    //snprintf(log_name, 255, "/mnt/sdcard/%d_%02d_%02d_%s",my_tm.tm_year+1900, my_tm.tm_mon+1, my_tm.tm_mday, accountid);
    snprintf(log_name, 255, "%s%s%s", LOG_PATH,accountid,LOG_EXT);
    //m_pLog = fopen(log_name, "a+"); //不存在就创建，存在追加内容
    m_pLog = fopen(log_name, "w+");    //不存在就创建，存在清空内容
    
    if(m_pLog == NULL)
    {
        cocos2d::log("log_name=%s open error!",log_name);
        return false;
    }
    _bExitLogFile = true;
    strcpy(_szAccountid,accountid);
    cocos2d::log("log_name=%s open right!",log_name);
    return true;
}
void lyAndLog::addLog(const char* format, ...)
{
    //1、如果文件过大，重新创建该文件
    //2、追加log到数据流中
    //3、刷新数据流到文件中
    //4、返回
    cocos2d::log("Log Item=%d",_nLogItem);
    //*
    if (_nLogItem >= LOG_MAX_ITEM) {
        cocos2d::log("重新创建log文件  Accountid=%s",_szAccountid);
        initLog(_szAccountid);
    }
    //*/
    if (!_bExitLogFile)
    {
        cocos2d::log("log文件不存在");
        return;
    }
    struct timeval now = {0,0};
    gettimeofday(&now, NULL);
    time_t t = now.tv_sec;
    struct tm* sys_tm = localtime(&t);
    struct tm my_tm = *sys_tm;
    va_list valst;
    va_start(valst, format);
    string log_str;
    
    int nPos = snprintf(m_szBuffLog, 48, "%d-%02d-%02d %02d:%02d:%02d.%06d\n",
                     my_tm.tm_year+1900, my_tm.tm_mon+1, my_tm.tm_mday,
                     my_tm.tm_hour, my_tm.tm_min, my_tm.tm_sec, now.tv_usec);
    
    int nDiffPos = vsnprintf(m_szBuffLog + nPos, LOG_BUFF_SIZE-1, format, valst);
    m_szBuffLog[nPos + nDiffPos - 1] = '\n';
    log_str = m_szBuffLog;
    fputs(log_str.c_str(), m_pLog);
    va_end(valst);
    _nLogItem++;
    fflush(m_pLog);
}
