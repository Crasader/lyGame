#ifndef __PlatformUtils_objc_H_
#define __PlatformUtils_objc_H_

#include "cocos2d.h"

class PlatformUtils_objc
{
public:
    static std::string getAppName();
	static std::string getVersionString();
	static int getVersionCode();
	static std::string generateUUID();
	static unsigned char* AES128Cryption(int mode, const unsigned char *data, size_t dataSize, const char *key, const char *iv, size_t *size);
	static unsigned char* AES128Cryption_Userid(int mode, const unsigned char *data, size_t dataSize, const char *key, const char *iv, size_t *size);
	static bool createDirectoryByFullPath(const char* dir);
	static std::string getUseragent();
	static std::string getDeviceString();
	static std::string getOSVersionString();
	static std::string getAppBinaryPath();
	static float getViewHiddenHeight();
	static std::string getBrandString();
	static unsigned long getUsedMemory();
	static bool moveTaskToBack();
};

#endif // __PlatformUtils_objc_H_
