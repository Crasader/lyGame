//
//  lyISoundInterfaces.h
//  ly-client
//	声音管理类基类接口
//  Created by loveyur on 2016/11/11
//


#ifndef __lyGame__lyISoundInterfaces__
#define __lyGame__lyISoundInterfaces__


class lyISoundInterfaces
{
public:
    virtual void preloadBGM(const char* name) = 0;
    virtual void playBGM(const char* name, bool isLoop=true) = 0;
    virtual void playBGM(const int bgmId, bool isLoop=true) = 0;
    virtual void stopBGM() = 0;
    
    virtual unsigned int playSE(const char* name, bool isLoop=false) = 0;
    virtual unsigned int playSE(const int seId, bool isLoop=false) = 0;
    virtual void stopSE(unsigned int playSeId) = 0;
    virtual void stopAllSE() = 0;
    
    virtual void preloadSE(const int seId) = 0;
    virtual void unloadSE(const int seId) = 0;
};


#endif  /* defined(__lyGame__lyISoundInterfaces__) */
