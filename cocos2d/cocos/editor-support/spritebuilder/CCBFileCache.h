//
//  CCBFileCache.h
//  cocos2d_libs
//
//  Created by 大久保 孝一郎 on 2015/07/31.
//
//

#ifndef __cocos2d_libs__CCBFileCache__
#define __cocos2d_libs__CCBFileCache__

#include "cocos2d.h"


class CCBFileCache
{
public:
    static CCBFileCache * getInstance();
    
protected:
    CCBFileCache();
    virtual ~CCBFileCache();
    
public:
    std::shared_ptr<cocos2d::Data> readData(const std::string &fileName);
    
    void clearCache();
    
    ssize_t getCacheSizeLimit()  { return _cacheSizeLimit; }
    void setCacheSizeLimit(ssize_t limit);
    
    ssize_t getCurrentCacheSize()  { return _currentCacheSize; }

private:
    static CCBFileCache * s_instance;
    
    struct CacheContainer {
        std::string fileName;
        std::shared_ptr<cocos2d::Data> dataPtr;
        time_t lastAccessTime;
    };
    
    std::map<std::string, CacheContainer*> _cacheList;
    ssize_t _cacheSizeLimit;
    ssize_t _currentCacheSize;
    
    void dropCacheInLimit();

};

#endif /* defined(__cocos2d_libs__CCBFileCache__) */
