//
//  lySoundManager.h
//  ly-client
//  UI控件基类
//  Created by loveyur on 2016/11/11
//

#ifndef ly_lySoundManager_h
#define ly_lySoundManager_h

#include "IyISoundInterfaces.h"
#include <string>

class lySoundManager   : public lyISoundInterfaces
{
public:
    lySoundManager();
    virtual ~lySoundManager();
    static lySoundManager* getInstance(void);
    
    virtual bool init();
    virtual void preloadBGM(const char* name);
    virtual void playBGM(const char* name, bool isLoop=true);
    virtual void playBGM(const int bgmId, bool isLoop=true);
    virtual void stopBGM();
    
    virtual unsigned int playSE(const char* name, bool isLoop=false);
    virtual unsigned int playSE(const int seId, bool isLoop=false);
    virtual void stopSE(unsigned int playSeId);
    virtual void stopAllSE();
    virtual void preloadSE(const int seId);
    virtual void unloadSE(const int seId);
      
private:
    std::string   bgmExtension;
    std::string   seExtension;
};

#endif #endif  /* defined(ly_lySoundManager_h) */
