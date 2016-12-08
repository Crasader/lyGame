//
//  CCBFileCache.cpp
//  cocos2d_libs
//
//  Created by 大久保 孝一郎 on 2015/07/31.
//
//

#include "CCBFileCache.h"

USING_NS_CC;


CCBFileCache * CCBFileCache::s_instance = nullptr;

CCBFileCache * CCBFileCache::getInstance()
{
    if (s_instance == nullptr) {
        s_instance = new CCBFileCache();
    }
    return s_instance;
}


CCBFileCache::CCBFileCache()
: _cacheList()
, _cacheSizeLimit(0)
, _currentCacheSize(0)
{
}


CCBFileCache::~CCBFileCache()
{
    clearCache();
}


std::shared_ptr<cocos2d::Data> CCBFileCache::readData(const std::string &fileName)
{
    time_t currentTime = time(nullptr);
    
    auto searchIt = _cacheList.find(fileName);
    if (searchIt != _cacheList.end()) {
        // found cache
        auto container = searchIt->second;
        container->lastAccessTime = currentTime;
        return container->dataPtr;
    }
    
    auto strPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    auto dataPtr = std::make_shared<Data>(FileUtils::getInstance()->getDataFromFile(strPath));
    
    if (dataPtr->isNull()) {
        return dataPtr;
    }
    
    if (dataPtr->getSize() > _cacheSizeLimit) {
        return dataPtr;
    }
    
    // insert to cache
    CacheContainer *container = new CacheContainer();
    container->fileName = fileName;
    container->dataPtr = dataPtr;
    container->lastAccessTime = currentTime;
    _cacheList.insert(std::make_pair(fileName, container));
    
    _currentCacheSize += dataPtr->getSize();
    
    dropCacheInLimit();
    
    return dataPtr;
}


void CCBFileCache::clearCache()
{
    for (auto &pair : _cacheList) {
        CacheContainer *container = pair.second;
        delete container;
    }
    _cacheList.clear();
    
    _currentCacheSize = 0;
}


void CCBFileCache::dropCacheInLimit()
{
    if (_currentCacheSize <= _cacheSizeLimit) {
        return;
    }
    
    // create cache container vector
    std::vector<CacheContainer*> containerList;
    for (auto &pair : _cacheList) {
        containerList.push_back(pair.second);
    }
    
    // order by lastAccessTime asc
    std::sort(containerList.begin(), containerList.end(), [](const CacheContainer *a, const CacheContainer *b) {
        return a->lastAccessTime < b->lastAccessTime;
    });
    
    // clear caches
    for (CacheContainer *container : containerList) {
        _cacheList.erase(container->fileName);
        _currentCacheSize -= container->dataPtr->getSize();
        delete container;
        
        if (_currentCacheSize <= _cacheSizeLimit) {
            return;
        }
    }
}


void CCBFileCache::setCacheSizeLimit(ssize_t limit)
{
    _cacheSizeLimit = limit;
    
    dropCacheInLimit();
}

