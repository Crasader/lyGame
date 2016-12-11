#ifndef __GameCommon__H_
#define __GameCommon__H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "CCCrypto.h"

extern "C" {
#include "md5.h"
}

#define USE_LUA 0

#define FBENCRYPT_BLOCK_SIZE    16

// Android上位機種のMoved誤判定しきい値
#define LITTLE_DISTANCE                     0.10f

// 画面サイズ定義
#define IPHONE4_WIDTH 320
#define IPHONE4_HEIGHT 480

#define IPHONE5_WIDTH 320
#define IPHONE5_HEIGHT 568

#define IPAD_WIDTH 320
#define IPAD_HEIGHT 512
#define LOGIN_KEY "loginKey"
class PlatformUtils {

public:
    static std::string getMasterVersion();
    static void saveMasterVersion(std::string masterVersion);
    static void loadMasterVersion();
    template<class T> static T getAccountId();
    CC_DEPRECATED_ATTRIBUTE static std::string getAccountId();  // int64_t 対応おわったら消しましょう
    static bool isAccountId();
    
    static std::string getUUID();
    static void calcUUID();
    static void saveFinishedCheckChangeDevice();
    static bool isFinishedCheckChangeDevice();
    static void saveFinishedFirstResourceDownload();
    static bool isFinishedFirstResourceDownload();
    static void saveUserKeyData(std::string accountId, std::string uuid);
    static void loadUserKeyData();
    static std::string getResourceVersion();
    static void saveResourceVersion(std::string resourceVersion);
    static void loadResourceVersion();
    static void saveDetectedUnmatchVersionResource(bool flg);
    static bool isDetectedUnmatchVersionResource();
    static const uint8_t* getAppBinaryHash();
    // オリジナル：getAppBinaryHash
    static const uint8_t* getPrevVersionInfo()
    {
        if (_appBinaryHash != nullptr) {
            return _appBinaryHash;
        }

        _appBinaryHash = new uint8_t[cocos2d::extension::CCCrypto::MD5_BUFFER_LENGTH];
//  #define CLOSE_FUN 马俊松修改
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        std::string path = PlatformUtils::getAppBinaryPath();
#else
        std::string path =cocos2d::FileUtils::getInstance()->fullPathForFilename("fonts/ModeMinAStd-B.ttf");
#endif
        
        CCLOG("binary path = %s", path.c_str());

        auto fp = fopen(path.c_str(), "rb");
        if (fp == nullptr) {
            CCLOG("open failure");
            return nullptr;
        }

        MD5_CTX ctx;
        MD5_EX_Init(&ctx);

        unsigned int aabb = 0;
        while (true) {
            unsigned char buffer[4096];
            size_t readSize = fread(buffer, sizeof(unsigned char), sizeof(buffer)/sizeof(unsigned char), fp);

            aabb++;
            if (readSize > 0) {
                MD5_EX_Update(&ctx, buffer, readSize);
            }
            else {
                break;
            }
            aabb ^= 0xbf;
        }
        aabb |= 0x1;
        aabb %= 2;

        for (int i = 0; i < aabb; i++) {
            MD5_EX_Final(_appBinaryHash, &ctx);
        }

        return _appBinaryHash;
    }
    static void set64AccoutId(std::string accoutId);
    static std::string getAccountLocalID();
    
    // オリジナル：getRequestToken
    static const uint8_t* commonPlatformInfo()
    {
        return _requestToken;
    }
    // オリジナル：createRequestValidationCode
    static std::string clearPlatformCache(const std::string &reqParam)
    {
        uint8_t salt = rand() % 0xff;

        auto appBinaryHash = getPrevVersionInfo();
        auto requestToken = commonPlatformInfo();

        uint8_t maskedAppBinaryHash[cocos2d::extension::CCCrypto::MD5_BUFFER_LENGTH];
        uint8_t maskedRequestToken[cocos2d::extension::CCCrypto::MD5_BUFFER_LENGTH];

        unsigned int aabb = 0;
        if (appBinaryHash != nullptr) {
            for (int i = 0; i < cocos2d::extension::CCCrypto::MD5_BUFFER_LENGTH; i++) {
                maskedAppBinaryHash[i] = appBinaryHash[i] ^ salt;
                aabb++;
            }
        }
        if (requestToken != nullptr) {
            for (int i = 0; i < cocos2d::extension::CCCrypto::MD5_BUFFER_LENGTH; i++) {
                maskedRequestToken[i] = requestToken[i] ^ salt;
                aabb ^= 0xbf;
            }
        }
        aabb |= 0x1;
        aabb %= 2;

        std::string maskedAppBinaryHashText = hextostr(maskedAppBinaryHash);
        std::string maskedRequestTokenText = hextostr(maskedRequestToken);

        uint8_t requestHash[cocos2d::extension::CCCrypto::MD5_BUFFER_LENGTH];

        for (int i = 0; i < aabb; i++) {
            MD5_CTX ctx;
            MD5_EX_Init(&ctx);
            MD5_EX_Update(&ctx, const_cast<std::string::value_type*>(maskedAppBinaryHashText.c_str()), maskedAppBinaryHashText.size());
            MD5_EX_Update(&ctx, const_cast<std::string::value_type*>(maskedRequestTokenText.c_str()), maskedRequestTokenText.size());
            MD5_EX_Update(&ctx, const_cast<std::string::value_type*>(reqParam.c_str()), reqParam.size());
            MD5_EX_Final(requestHash, &ctx);
        }
        
        // レスポンス改ざんを通知
        for (int i = 0; i < _requestHashShuffleCount; i++) {
            MD5_CTX ctx;
            MD5_EX_Init(&ctx);
            MD5_EX_Update(&ctx, requestHash, cocos2d::extension::CCCrypto::MD5_BUFFER_LENGTH);
            MD5_EX_Final(requestHash, &ctx);
        }

        std::string str;
        str += cocos2d::StringUtils::format("%03d", salt);
        str += cocos2d::StringUtils::format("-%s", maskedAppBinaryHashText.c_str());
        str += cocos2d::StringUtils::format("-%s", maskedRequestTokenText.c_str());
        str += cocos2d::StringUtils::format("-%s", hextostr(requestHash).c_str());
        return str;
    }
    
    static void setMasterdataHashCheckError(bool error) {
        if (error) {
            _requestHashShuffleCount |=  0x01;
        }
        else {
            _requestHashShuffleCount &= ~0x01;
        }
    }
    static void setResponseHashCheckError(bool error) {
        if (error) {
            _requestHashShuffleCount |=  0x02;
        }
        else {
            _requestHashShuffleCount &= ~0x02;
        }
    }
    static uint8_t getResponseHashCheckResultCode() {
        return _requestHashShuffleCount;
    }
    static void setResponseHashCheckResultCode(uint8_t code) {
        _requestHashShuffleCount = code;
    }
    
    static unsigned char* generateIv();
    static std::string generateIvString();
    static std::string getUseragent();
    
    static std::string createRequestTimeString();
    static std::string createCheckKey(std::string requestTime);
    
    static void setRequestToken(const std::string &token);
    static const uint8_t* getRequestToken();
    static std::string createRequestValidationCode(const std::string &reqParam);
    
    static std::string encode(const char* dat, int size);
    static std::string decode(const char* dat, int size);

    static void saveSidData(std::string sid);
    static std::string loadSidData();

    static int64_t getTimeMilliSeconds();
    
    static time_t getUnixTime();
    static int getRandom(int min,int max);
    
    static std::string getAppName();
    static std::string getVersionString();
    //byshixc  添加版本号
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    static int getVersionCode();
#else
    static std::string getBuildVersionString();
#endif
    static std::string generateUUID();
    static std::string getCachePath();
    static std::string getDocumentPath();
    static std::string getDownloadResourcePath();
    static std::string getAppBinaryPath();
    static std::string getDeviceString();
    static std::string getOSVersionString();
    static std::string getBrandString();
    
    static std::string hextostr(unsigned char* bin);
    static void strtohex(const std::string &text, uint8_t *outbuf, size_t outbufSize);
    
    static void userIdCrypt(std::string str , std::string &encoded);
    
    static unsigned char* AES128Encode(const unsigned char *data, size_t dataSize, const char *key, const char *iv, size_t *size, bool compatibleMode = false);
    static unsigned char* AES128Decode(const unsigned char *data, size_t dataSize, const char *key, const char *iv, size_t *size, bool compatibleMode = false);
    static unsigned char* AES128Encode_Userid(const unsigned char *data, size_t dataSize, const char *key, const char *iv, size_t *size);

    static bool createDirectoryByFullPath(const char* dir);
    static bool addDoNotBackupAttribute(const char *url);
    
    static cocos2d::Rect getUIScreenFrame();
    static cocos2d::Rect getUIScreenBounds();
    static float getViewHiddenHeight();
    
    static bool isALittleDistance(cocos2d::Touch *now, cocos2d::Vec2 &prev);
    
    static std::string urlEncode(const std::string &data);

    static long getUsedMemory();
    static void moveTaskToBack();

    static int compareVersionString(const std::string& str1, const std::string& str2);
    static std::vector<std::string> split(const std::string& str, char delimiter);

    
    static void setToken(std::string token)
    {
        _sdkToken =token;
    }
    static std::string getToken()
    {
        return _sdkToken;
    }
    static std::string getLoginKey()
    {
        return _loginKey;
    }
    static void setLoginKey(std::string str_)
    {
        
        _loginKey = str_;
    }

    
private:
    static std::string _accountId;
    static std::string _uuid;
    static std::string _resourceVersion;
    static std::string _masterVersion;
    
    static uint8_t *_appBinaryHash;
    static uint8_t *_requestToken;
    static uint8_t _requestHashShuffleCount;
    
    
    static std::string _loginKey; //服务器返回的针对对用户登录的key值
    static std::string _str64AccountId;       //Login 返回的
    static std::string _sdkToken;       //SDK 返回的
    
};

#endif
