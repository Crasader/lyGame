//
//  CCBCustomClassLoaderLibrary.h
//  client-vitamin
//
//  Created by 大久保 孝一郎 on 2014/06/26.
//
//

#ifndef __client_vitamin__CCBCustomClassLoaderLibrary__
#define __client_vitamin__CCBCustomClassLoaderLibrary__

#include "cocosbuilder/CocosBuilder.h"


typedef struct {
    const char                *pClassName;       //! クラス名
    cocosbuilder::NodeLoader *pCCNodeLoader;    //! 登録するローダーのポインタ
} CustomClassEntry;

class CCBCustomClassLoaderLibrary {
public:
    
    CCBCustomClassLoaderLibrary();
    
    ~CCBCustomClassLoaderLibrary();
    
    void registerCustomClassLoader();
    
    void unregisterCustomClassLoader();
    
    static CCBCustomClassLoaderLibrary * getInstance();
    
    static void purgeSharedCustomClassLoaderLibrary();
    
    void changeRegisterCustomClassLoader(const char* className, cocosbuilder::NodeLoader* loader);
    
private:
    std::vector<CustomClassEntry> m_customClassEntry;
};


#endif /* defined(__client_vitamin__CCBCustomClassLoaderLibrary__) */
