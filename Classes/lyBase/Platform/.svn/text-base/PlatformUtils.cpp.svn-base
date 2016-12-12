
#include "PlatformUtils.h"
#include "RandomUtil.h"
#include "ConfigEnvironment.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "PlatformUtils_objc.h"
#include "platform/android/jni/JniHelper.h"
#endif

#include "LoginManager.h"
#include "CommonSDKDef.h"
#include<sys/timeb.h>

USING_NS_CC;
USING_NS_CC_EXT;

const char* USERID_CRYPT_KEY = "b81674d2309efc5a";
const char* USERID_FILENAME = "001.bin";
const char* CHECK_CHENGE_DEVICE = "002.bin";
const char* FIRST_RESOURCE_DOWNLOAD = "003.bin";
const char* RESOURCE_VERSION = "004.bin";
const char* MASTER_VERSION = "005.bin";
const char* DETECTED_UNMATUCH_VERSION_RESOURCE = "006.bin";
const char* SID_FILENAME = "010.bin";


const char* ACOUNTID_KEY = "fsaoeifjlcie";


std::string PlatformUtils::_accountId;
std::string PlatformUtils::_uuid;
std::string PlatformUtils::_resourceVersion;
std::string PlatformUtils::_masterVersion;
uint8_t* PlatformUtils::_appBinaryHash = nullptr;
uint8_t* PlatformUtils::_requestToken = nullptr;
uint8_t PlatformUtils::_requestHashShuffleCount = 0;


std::string PlatformUtils::_sdkToken;
std::string PlatformUtils::_loginKey;
std::string PlatformUtils::_str64AccountId;

std::string PlatformUtils::getResourceVersion()
{
    return _resourceVersion;
}

void PlatformUtils::saveResourceVersion(std::string resourceVersion)
{
    int totalSize = 0;
    int resourceVersionSize = resourceVersion.size();
    
    totalSize += 4;
    totalSize += resourceVersionSize;
    
    char *buf = new char[totalSize];
    int n = 0;
    
    buf[n++] = (unsigned char)((resourceVersionSize >> 24) & 0xff);
    buf[n++] = (unsigned char)((resourceVersionSize >> 16) & 0xff);
    buf[n++] = (unsigned char)((resourceVersionSize >>  8) & 0xff);
    buf[n++] = (unsigned char)((resourceVersionSize)       & 0xff);
    memcpy(&buf[n], resourceVersion.c_str(), (size_t)resourceVersionSize);
    n += resourceVersionSize;
    
    std::string iv = generateIvString();
    size_t en_size;
    unsigned char* en_buf = AES128Encode((unsigned char*)buf, totalSize, USERID_CRYPT_KEY, iv.c_str(), &en_size);
    CC_SAFE_DELETE_ARRAY(buf);
    
    size_t sv_size = en_size+FBENCRYPT_BLOCK_SIZE;
    unsigned char* sv_buf = new unsigned char[sv_size];
    memcpy(&sv_buf[0], &iv.c_str()[0], iv.size());
    memcpy(&sv_buf[iv.size()], en_buf, en_size);
    CC_SAFE_DELETE_ARRAY(en_buf);
    
    std::string writablePath = getDownloadResourcePath();
    // 環境ごとにファイル使い分け
    std::string fileName = writablePath+ConfigEnvironment::getInstance()->getConnectedEnvironmentName()+RESOURCE_VERSION;
    
    FILE* fp = fopen(fileName.c_str(), "wb");
    if (fp) {
        fwrite(sv_buf, sv_size, 1, fp);
        fclose(fp);
    }
    CC_SAFE_DELETE_ARRAY(sv_buf);
    
    _resourceVersion = resourceVersion;
}

void PlatformUtils::loadResourceVersion()
{
    _resourceVersion = "";

    std::string writablePath = getDownloadResourcePath();
    std::string fileName = writablePath+ConfigEnvironment::getInstance()->getConnectedEnvironmentName()+RESOURCE_VERSION;
    
    ssize_t ld_size;
    unsigned char* ld_buf = FileUtils::getInstance()->getFileData(fileName.c_str(), "rb", &ld_size);
    if (ld_buf != NULL && ld_size >= FBENCRYPT_BLOCK_SIZE)
    {
        std::string iv = std::string((char*)ld_buf, FBENCRYPT_BLOCK_SIZE);
        
        size_t en_size = ld_size-FBENCRYPT_BLOCK_SIZE;
        unsigned char* en_buf = new unsigned char[en_size];
        memcpy(en_buf, &ld_buf[FBENCRYPT_BLOCK_SIZE], en_size);
        
        size_t de_size = 0;
        unsigned char* buf = AES128Decode((unsigned char*)en_buf, en_size, USERID_CRYPT_KEY, iv.c_str(), &de_size);
        
        int n = 0;
        int resourceVersionSize = 0;
        
        resourceVersionSize = ((buf[n+0] << 24) | (buf[n+1] << 16) | (buf[n+2] << 8) | buf[n+3]);
        n += 4;
        if (resourceVersionSize > 0 && resourceVersionSize <= de_size - 4)
        {
            _resourceVersion = std::string((char*)&buf[n], resourceVersionSize);
            n += resourceVersionSize;
        }

        CC_SAFE_DELETE_ARRAY(en_buf);
        CC_SAFE_DELETE_ARRAY(buf);
    }

    CC_SAFE_DELETE_ARRAY(ld_buf);
}

std::string PlatformUtils::getMasterVersion()
{
    return _masterVersion;
}

void PlatformUtils::saveMasterVersion(std::string masterVersion)
{
    int totalSize = 0;
    int masterVersionSize = masterVersion.size();
    
    totalSize += 4;
    totalSize += masterVersionSize;
    
    char *buf = new char[totalSize];
    int n = 0;
    
    buf[n++] = (unsigned char)((masterVersionSize >> 24) & 0xff);
    buf[n++] = (unsigned char)((masterVersionSize >> 16) & 0xff);
    buf[n++] = (unsigned char)((masterVersionSize >>  8) & 0xff);
    buf[n++] = (unsigned char)((masterVersionSize)       & 0xff);
    memcpy(&buf[n], masterVersion.c_str(), (size_t)masterVersionSize);
    n += masterVersionSize;
    
    std::string iv = generateIvString();
    size_t en_size;
    unsigned char* en_buf = AES128Encode((unsigned char*)buf, totalSize, USERID_CRYPT_KEY, iv.c_str(), &en_size);
    CC_SAFE_DELETE_ARRAY(buf);
    
    size_t sv_size = en_size+FBENCRYPT_BLOCK_SIZE;
    unsigned char* sv_buf = new unsigned char[sv_size];
    memcpy(&sv_buf[0], &iv.c_str()[0], iv.size());
    memcpy(&sv_buf[iv.size()], en_buf, en_size);
    CC_SAFE_DELETE_ARRAY(en_buf);
    
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string fileName = writablePath+ConfigEnvironment::getInstance()->getConnectedEnvironmentName().c_str()+MASTER_VERSION;
    FILE* fp = fopen(fileName.c_str(), "wb");
    if (fp) {
        fwrite(sv_buf, sv_size, 1, fp);
        fclose(fp);
    }
    CC_SAFE_DELETE_ARRAY(sv_buf);
    
    _masterVersion = masterVersion;
}

void PlatformUtils::loadMasterVersion()
{
    _masterVersion = "";
    
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string fileName = writablePath+ConfigEnvironment::getInstance()->getConnectedEnvironmentName().c_str()+MASTER_VERSION;
    
    ssize_t ld_size;
    unsigned char* ld_buf = FileUtils::getInstance()->getFileData(fileName.c_str(), "rb", &ld_size);
    if (ld_buf != NULL && ld_size >= FBENCRYPT_BLOCK_SIZE)
    {
        std::string iv = std::string((char*)ld_buf, FBENCRYPT_BLOCK_SIZE);
        
        size_t en_size = ld_size-FBENCRYPT_BLOCK_SIZE;
        unsigned char* en_buf = new unsigned char[en_size];
        memcpy(en_buf, &ld_buf[FBENCRYPT_BLOCK_SIZE], en_size);
        CC_SAFE_DELETE_ARRAY(ld_buf);
        
        size_t de_size = 0;
        unsigned char* buf = AES128Decode((unsigned char*)en_buf, en_size, USERID_CRYPT_KEY, iv.c_str(), &de_size);
        
        CC_SAFE_DELETE_ARRAY(en_buf);
        
        int n = 0;
        int masterVersionSize = 0;
        
        masterVersionSize = ((buf[n+0] << 24) | (buf[n+1] << 16) | (buf[n+2] << 8) | buf[n+3]);
        n += 4;
        if (masterVersionSize > 0 && masterVersionSize <= de_size - 4)
        {
            _masterVersion = std::string((char*)&buf[n], masterVersionSize);
            n += masterVersionSize;
        }
        
        CC_SAFE_DELETE_ARRAY(buf);
    }
}

void PlatformUtils::set64AccoutId(std::string accoutId)
{
#ifdef USE_SDK_LOGIN
    PlatformUtils::_str64AccountId = accoutId;
#else
    PlatformUtils::_accountId = accoutId;
#endif
}
std::string PlatformUtils::getAccountLocalID()
{
    return _accountId;
}

template<>
double PlatformUtils::getAccountId() {
#ifdef USE_SDK_LOGIN
    return atof(PlatformUtils::_str64AccountId.c_str());
#else
    return atof(_accountId.c_str());
#endif
}

// TODO: deprecated 非推奨ですdoubleにしよう
template<>
long PlatformUtils::getAccountId() {
#ifdef USE_SDK_LOGIN
    return atol(PlatformUtils::_str64AccountId.c_str());
#else
    return atol(_accountId.c_str());
#endif
}

template<>
int64_t PlatformUtils::getAccountId() {
#ifdef USE_SDK_LOGIN
    return atoll(PlatformUtils::_str64AccountId.c_str());
#else
    return atoll(_accountId.c_str());
#endif
}

template<>
std::string PlatformUtils::getAccountId() {
#ifdef USE_SDK_LOGIN
    return _str64AccountId ;
#else
    return _accountId ;
#endif
}

std::string PlatformUtils::getAccountId() {
#ifdef USE_SDK_LOGIN
    return _str64AccountId ;
#else
    return _accountId ;
#endif
}
bool PlatformUtils::isAccountId() {
    return !_accountId.empty();
}

std::string PlatformUtils::getUUID() {
#ifdef USE_SDK_LOGIN
    std::string text = LoginManager::GetInstance()->m_Uid + LoginManager::GetInstance()->m_sdkName;
    int nChannelId = LoginManager::GetInstance()->channelId();
    if (nChannelId != 0 )
    {
        text.append(String::createWithFormat("%d", nChannelId)->getCString());
    }
    const char* plaintext = text.c_str();
    //    CCLOG("plaintext = %s",plaintext);
    unsigned char buffer[cocos2d::extension::CCCrypto::MD5_BUFFER_LENGTH];
    cocos2d::extension::CCCrypto::MD5((void*)plaintext, strlen(plaintext), buffer);
    std::string uuid = PlatformUtils::hextostr(buffer);
    return uuid;
#else
    return _uuid;
#endif
}

void PlatformUtils::calcUUID() {
    _uuid = generateUUID();
}

void PlatformUtils::saveFinishedCheckChangeDevice() {
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string fileName = writablePath+ConfigEnvironment::getInstance()->getConnectedEnvironmentName().c_str()+CHECK_CHENGE_DEVICE;
    FILE* fp = fopen(fileName.c_str(), "wb");
    if (fp) {
        fwrite((void*)0, 0, 1, fp);
        fclose(fp);
    }
}

bool PlatformUtils::isFinishedCheckChangeDevice() {
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string fileName = writablePath+ConfigEnvironment::getInstance()->getConnectedEnvironmentName().c_str()+CHECK_CHENGE_DEVICE;
    
    ssize_t ld_size;
    unsigned char* ld_buf = FileUtils::getInstance()->getFileData(fileName.c_str(), "rb", &ld_size);
    if(ld_buf != NULL) {
        free(ld_buf);
        return true;
    }
    return false;
}

void PlatformUtils::saveFinishedFirstResourceDownload() {
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string fileName = writablePath+ConfigEnvironment::getInstance()->getConnectedEnvironmentName().c_str()+FIRST_RESOURCE_DOWNLOAD;
    FILE* fp = fopen(fileName.c_str(), "wb");
    if (fp) {
        fwrite((void*)0, 0, 1, fp);
        fclose(fp);
    }
}

bool PlatformUtils::isFinishedFirstResourceDownload() {
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string fileName = writablePath+ConfigEnvironment::getInstance()->getConnectedEnvironmentName().c_str()+FIRST_RESOURCE_DOWNLOAD;
    
    ssize_t ld_size;
    unsigned char* ld_buf = FileUtils::getInstance()->getFileData(fileName.c_str(), "rb", &ld_size);
    if(ld_buf != NULL) {
        free(ld_buf);
        return true;
    }
    return false;
}

void PlatformUtils::saveUserKeyData(std::string accountId, std::string uuid) {
#ifdef USE_SDK_LOGIN
    UserDefault::getInstance()->setStringForKey(ACOUNTID_KEY, accountId);
#else
    int totalSize = 0;
    int userKeySize = accountId.size();
    int uuidSize = uuid.size();
    
    totalSize += 4;
    totalSize += userKeySize;
    totalSize += 4;
    totalSize += uuidSize;
    
    char *buf = new char[totalSize];
    int n = 0;
    
    buf[n++] = (unsigned char)((userKeySize >> 24) & 0xff);
    buf[n++] = (unsigned char)((userKeySize >> 16) & 0xff);
    buf[n++] = (unsigned char)((userKeySize >>  8) & 0xff);
    buf[n++] = (unsigned char)((userKeySize)       & 0xff);
    memcpy(&buf[n], accountId.c_str(), (size_t)userKeySize);
    n += userKeySize;
    
    buf[n++] = (unsigned char)((uuidSize >> 24) & 0xff);
    buf[n++] = (unsigned char)((uuidSize >> 16) & 0xff);
    buf[n++] = (unsigned char)((uuidSize >>  8) & 0xff);
    buf[n++] = (unsigned char)((uuidSize)       & 0xff);
    memcpy(&buf[n], uuid.c_str(), (size_t)uuidSize);
    
    std::string iv = generateIvString();
    size_t en_size;
    unsigned char* en_buf = AES128Encode((unsigned char*)buf, totalSize, USERID_CRYPT_KEY, iv.c_str(), &en_size);
    CC_SAFE_DELETE_ARRAY(buf);
    
    size_t sv_size = en_size+FBENCRYPT_BLOCK_SIZE;
    unsigned char* sv_buf = new unsigned char[sv_size];
    memcpy(&sv_buf[0], &iv.c_str()[0], iv.size());
    memcpy(&sv_buf[iv.size()], en_buf, en_size);
    CC_SAFE_DELETE_ARRAY(en_buf);
    
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string fileName = writablePath+ConfigEnvironment::getInstance()->getConnectedEnvironmentName().c_str()+USERID_FILENAME;
    FILE* fp = fopen(fileName.c_str(), "wb");
    if (fp) {
        fwrite(sv_buf, sv_size, 1, fp);
        fclose(fp);
    }
    CC_SAFE_DELETE_ARRAY(sv_buf);
#endif
}

void PlatformUtils::loadUserKeyData() {
#ifdef USE_SDK_LOGIN
    _accountId = UserDefault::getInstance()->getStringForKey(ACOUNTID_KEY, std::string("0")).c_str();
#else
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string fileName = writablePath+ConfigEnvironment::getInstance()->getConnectedEnvironmentName().c_str()+USERID_FILENAME;
    
    ssize_t ld_size;
    unsigned char* ld_buf = FileUtils::getInstance()->getFileData(fileName.c_str(), "rb", &ld_size);
    
    if (ld_buf != NULL && ld_size >= FBENCRYPT_BLOCK_SIZE)
    {
        std::string iv = std::string((char*)ld_buf, FBENCRYPT_BLOCK_SIZE);
        
        size_t en_size = ld_size-FBENCRYPT_BLOCK_SIZE;
        unsigned char* en_buf = new unsigned char[en_size];
        memcpy(en_buf, &ld_buf[FBENCRYPT_BLOCK_SIZE], en_size);
        CC_SAFE_DELETE_ARRAY(ld_buf);
        
        size_t de_size;
        unsigned char* buf = AES128Decode((unsigned char*)en_buf, en_size, USERID_CRYPT_KEY, iv.c_str(), &de_size);
        
        CC_SAFE_DELETE_ARRAY(en_buf);
        
        int n = 0;
        int userKeySize = 0;
        int uuidSize = 0;
        
        userKeySize = ((buf[n+0] << 24) | (buf[n+1] << 16) | (buf[n+2] << 8) | buf[n+3]);
        n += 4;
        _accountId = std::string((char*)&buf[n], userKeySize);
        n += userKeySize;
        
        uuidSize = ((buf[n+0] << 24) | (buf[n+1] << 16) | (buf[n+2] << 8) | buf[n+3]);
        n += 4;
        _uuid = std::string((char*)&buf[n], uuidSize);
        
        CC_SAFE_DELETE_ARRAY(buf);
    } else {
        _accountId = "";
        _uuid = "";
    }
#endif
}

void PlatformUtils::saveDetectedUnmatchVersionResource(bool flg)
{
    auto writablePath = getDownloadResourcePath();
    auto fileName = writablePath + ConfigEnvironment::getInstance()->getConnectedEnvironmentName() + DETECTED_UNMATUCH_VERSION_RESOURCE;
    FILE* fp = fopen(fileName.c_str(), "wb");
    if (fp) {
        char data = flg;
        fwrite(&data, 1, 1, fp);
        fclose(fp);
    }
}

bool PlatformUtils::isDetectedUnmatchVersionResource()
{
    auto writablePath = getDownloadResourcePath();
    auto fileName = writablePath + ConfigEnvironment::getInstance()->getConnectedEnvironmentName() + DETECTED_UNMATUCH_VERSION_RESOURCE;
    
    ssize_t ld_size;
    unsigned char* ld_buf = FileUtils::getInstance()->getFileData(fileName.c_str(), "rb", &ld_size);
    if (ld_buf)
    {
        char flg = *ld_buf;
        free(ld_buf);
        return flg;
    }
    return false;
}

const uint8_t* PlatformUtils::getAppBinaryHash()
{
    if (_appBinaryHash != nullptr) {
        return _appBinaryHash;
    }
    
    _appBinaryHash = new uint8_t[CCCrypto::MD5_BUFFER_LENGTH];
    
    std::string path = PlatformUtils::getAppBinaryPath();
    CCLOG("binary path = %s", path.c_str());
    
    auto fp = fopen(path.c_str(), "rb");
    if (fp == nullptr) {
        CCLOG("open failure");
        return nullptr;
    }
    
    MD5_CTX ctx;
    MD5_EX_Init(&ctx);
    
    while (true) {
        unsigned char buffer[4096];
        size_t readSize = fread(buffer, sizeof(unsigned char), sizeof(buffer)/sizeof(unsigned char), fp);
        
        if (readSize > 0) {
            MD5_EX_Update(&ctx, buffer, readSize);
        }
        else {
            break;
        }
    }
    
    MD5_EX_Final(_appBinaryHash, &ctx);

    fclose(fp);
    
    return _appBinaryHash;
}

unsigned char* PlatformUtils::generateIv() {
    unsigned char* buf = new unsigned char[FBENCRYPT_BLOCK_SIZE];
    for(int i=0; i<FBENCRYPT_BLOCK_SIZE; i++) {
        buf[i] = RANDOM(16);
    }
    return buf;
}

std::string PlatformUtils::generateIvString() {
    char buf[FBENCRYPT_BLOCK_SIZE+1] = {0};
    unsigned char* piv = generateIv();
    
    for(int i=0; i<FBENCRYPT_BLOCK_SIZE; i++) {
        sprintf(&buf[i], "%1x", piv[i]);
    }
    
    buf[FBENCRYPT_BLOCK_SIZE] = '\0';
    
    delete [] piv;
    
    return std::string(buf);
}

// ID暗号化・復号化
// とりあえずmonstersのパクってます
std::string PlatformUtils::encode(const char* dat, int size) {
    static char buf[1024];
    int n = 0;
    
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%04x", size);
    n += 4;
    
    for(int i=0; i<size; i++) {
        sprintf(&buf[n++], "%1x", RANDOM(16));
        sprintf(&buf[n++], "%1x", RANDOM(16));
        buf[n++] = dat[i] + 0x21;
        sprintf(&buf[n++], "%1x", RANDOM(16));
    }
    strcat(buf, generateIvString().c_str());
    
    return std::string(buf);
}

std::string PlatformUtils::decode(const char* dat, int size) {
    static char buf[1024];
    static char buf2[12];
    
    int i=0, j=0, n=0;
    
    memset(buf, 0, sizeof(buf));
    memset(buf2, 0, sizeof(buf2));
    memcpy(buf2, dat, 4);
    buf2[5] = 0;
    int max = (int)strtol(buf2, NULL, 16);
    
    n += 4;
    for(i=0; i<size; i++) {
        n++;
        n++;
        buf[j++] = dat[n++] - 0x21;
        n++;
        
        if(j >= max) break;
    }
    
    return std::string(buf);
}

void PlatformUtils::saveSidData(std::string sid) {
    int totalSize = 0;
    int sidSize = sid.size();
    
    totalSize += 4;
    totalSize += sidSize;
    
    char *buf = new char[totalSize];
    int n = 0;
    
    buf[n++] = (unsigned char)((sidSize >> 24) & 0xff);
    buf[n++] = (unsigned char)((sidSize >> 16) & 0xff);
    buf[n++] = (unsigned char)((sidSize >>  8) & 0xff);
    buf[n++] = (unsigned char)((sidSize)       & 0xff);
    memcpy(&buf[n], sid.c_str(), (size_t)sidSize);
    
    std::string iv = generateIvString();
    size_t en_size;
    unsigned char* en_buf = AES128Encode((unsigned char*)buf, totalSize, USERID_CRYPT_KEY, iv.c_str(), &en_size);
    CC_SAFE_DELETE_ARRAY(buf);
    
    size_t sv_size = en_size+FBENCRYPT_BLOCK_SIZE;
    unsigned char* sv_buf = new unsigned char[sv_size];
    memcpy(&sv_buf[0], &iv.c_str()[0], iv.size());
    memcpy(&sv_buf[iv.size()], en_buf, en_size);
    CC_SAFE_DELETE_ARRAY(en_buf);
    
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string fileName = writablePath+ConfigEnvironment::getInstance()->getConnectedEnvironmentName().c_str()+SID_FILENAME;
    FILE* fp = fopen(fileName.c_str(), "wb");
    if (fp) {
        fwrite(sv_buf, sv_size, 1, fp);
        fclose(fp);
    }
    
    CC_SAFE_DELETE_ARRAY(sv_buf);
    
}

std::string PlatformUtils::loadSidData() {
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string fileName = writablePath+ConfigEnvironment::getInstance()->getConnectedEnvironmentName().c_str()+SID_FILENAME;
    
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
    ssize_t ld_size;
#else
    ssize_t ld_size;
#endif
    unsigned char* ld_buf = FileUtils::getInstance()->getFileData(fileName.c_str(), "rb", &ld_size);
    
    if (ld_buf != NULL && ld_size >= FBENCRYPT_BLOCK_SIZE)
    {
        std::string iv = std::string((char*)ld_buf, FBENCRYPT_BLOCK_SIZE);
        
        size_t en_size = ld_size-FBENCRYPT_BLOCK_SIZE;
        unsigned char* en_buf = new unsigned char[en_size];
        memcpy(en_buf, &ld_buf[FBENCRYPT_BLOCK_SIZE], en_size);
        CC_SAFE_DELETE_ARRAY(ld_buf);
        
        size_t de_size;
        unsigned char* buf = AES128Decode((unsigned char*)en_buf, en_size, USERID_CRYPT_KEY, iv.c_str(), &de_size);
        CC_SAFE_DELETE_ARRAY(en_buf);
        
        int n = 0;
        int sidSize = 0;
        
        sidSize = ((buf[n+0] << 24) | (buf[n+1] << 16) | (buf[n+2] << 8) | buf[n+3]);
        n += 4;
        
        std::string sid =std::string((char*)&buf[n], sidSize);
        
        CC_SAFE_DELETE_ARRAY(buf);
        
        return sid;
    }
    return "";
}

std::string PlatformUtils::hextostr(unsigned char* bin)
{
    int binLength = CCCrypto::MD5_BUFFER_LENGTH;
    static const char* hextable = "0123456789abcdef";
    int strLength = binLength * 2 + 1;
    char str[strLength];
    memset(str, 0, strLength);
    int ci = 0;
    for (int i = 0; i < binLength; ++i)
    {
        unsigned char c = bin[i];
        str[ci++] = hextable[(c >> 4) & 0x0f];
        str[ci++] = hextable[c & 0x0f];
    }
    
    return std::string(str);
}

void PlatformUtils::strtohex(const std::string &text, uint8_t *outbuf, size_t outbufSize)
{
    int index = 0;

    for (auto ch : text) {
        if (index / 2 >= outbufSize) {
            break;
        }
        
        uint8_t chVal = 0x00;
        
        if ('0' <= ch && ch <= '9') {
            chVal = ch - '0';
        }
        else if ('a' <= ch && ch <= 'f') {
            chVal = ch - 'a' + 0x0a;
        }
        else if ('A' <= ch && ch <= 'F') {
            chVal = ch - 'A' + 0x0a;
        }
        else {
            chVal = 0x00;
        }
        
        if (index % 2 == 0) {
            outbuf[index / 2] = static_cast<uint8_t>(chVal << 4);
        }
        else {
            outbuf[index / 2] |= chVal;
        }
        
        index++;
    }
}

void PlatformUtils::userIdCrypt(std::string str , std::string &encoded){
    std::string iv = generateIvString();
	std::string original = str;
	// pkcs5Padding(original);
    size_t en_size;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    unsigned char* en_buf = AES128Encode((unsigned char*)original.c_str(), original.size(), "4Skqz1Bso0ka7tpa", iv.c_str(), &en_size);
#else
    unsigned char* en_buf = AES128Encode_Userid((unsigned char*)original.c_str(), original.size(), "4Skqz1Bso0ka7tpa", iv.c_str(), &en_size);
#endif
    
    unsigned char* tmp = new unsigned char[iv.size() + en_size ];
    memcpy(tmp, iv.c_str(), iv.size());
    memcpy(tmp+iv.size(), en_buf, en_size);
    
    int encodeLength = (iv.size() + en_size) * 2;
    char* encode = new char[encodeLength];
    CCCrypto::encodeBase64(tmp, iv.size() + en_size, encode, encodeLength);
    
    int size = strlen(encode);
    if (encode[size-1] == '\n') {
        encode[size-1] = '\0';
    }
    
    encoded= encode;
    
    delete[] tmp;
    delete[] encode;
    delete[] en_buf;
}

// ミリ秒単位の時間取得
int64_t PlatformUtils::getTimeMilliSeconds() {
    timeval time;
    gettimeofday(&time, NULL);
    int64_t millisecs = ((int64_t)time.tv_sec * 1000) + ((int64_t)time.tv_usec / 1000);
    return millisecs;
}

// UNIXタイム取得
time_t PlatformUtils::getUnixTime() {
    time_t t;
    t = time(NULL);
    return t;
}

//乱数取得
int PlatformUtils::getRandom(int min,int max)
{
    int sa = max - min;
    return (rand()%(sa + 1)) + min;
}

std::string PlatformUtils::getUseragent()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return PlatformUtils_objc::getUseragent();
#else
    std::string str;
    str = "";
    return str;
#endif
}

std::string PlatformUtils::createRequestTimeString()
{
    time_t now = getUnixTime() + 3600 * 24 * 0;
    char *timeStr = ctime(&now);

    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));
    strptime(timeStr, "%a %b %d %H:%M:%S %Y\n", &tm);
    
    char buf[128] = {};
    sprintf(buf, "%.4d%.2d%.2d%.2d%.2d%.2d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    return buf;
}

// checkKey = uuid + yyyyMMddHHmmss + 付加キーを３回ハッシュかけたもの
std::string PlatformUtils::createCheckKey(std::string requestTime)
{
    std::string uuid = PlatformUtils::getUUID();
    std::string hashKey = "_cb";
    
    std::string hashCheckSeedStr = uuid + requestTime + hashKey;
    
    std::string result;
    unsigned char buffer[CCCrypto::MD5_BUFFER_LENGTH];
    CCCrypto::MD5((void*)hashCheckSeedStr.c_str(), strlen(hashCheckSeedStr.c_str()), buffer);
    unsigned char buffer2[CCCrypto::MD5_BUFFER_LENGTH];
    CCCrypto::MD5((void*)buffer, CCCrypto::MD5_BUFFER_LENGTH, buffer2);
    unsigned char buffer3[CCCrypto::MD5_BUFFER_LENGTH];
    CCCrypto::MD5((void*)buffer2, CCCrypto::MD5_BUFFER_LENGTH, buffer3);
    result = PlatformUtils::hextostr(buffer3);
    return result;
}

void PlatformUtils::setRequestToken(const std::string &token)
{
    if (_requestToken == nullptr) {
        _requestToken = new uint8_t[CCCrypto::MD5_BUFFER_LENGTH];
    }
    
    strtohex(token, _requestToken, CCCrypto::MD5_BUFFER_LENGTH);
}

const uint8_t* PlatformUtils::getRequestToken()
{
    return _requestToken;
}

std::string PlatformUtils::createRequestValidationCode(const std::string &reqParam)
{
    uint8_t salt = rand() % 0xff;
    
    auto appBinaryHash = getAppBinaryHash();
    auto requestToken = getRequestToken();
    
    uint8_t maskedAppBinaryHash[CCCrypto::MD5_BUFFER_LENGTH];
    uint8_t maskedRequestToken[CCCrypto::MD5_BUFFER_LENGTH];
    
    if (appBinaryHash != nullptr) {
        for (int i = 0; i < CCCrypto::MD5_BUFFER_LENGTH; i++) {
            maskedAppBinaryHash[i] = appBinaryHash[i] ^ salt;
        }
    }
    if (requestToken != nullptr) {
        for (int i = 0; i < CCCrypto::MD5_BUFFER_LENGTH; i++) {
            maskedRequestToken[i] = requestToken[i] ^ salt;
        }
    }
    
    std::string maskedAppBinaryHashText = hextostr(maskedAppBinaryHash);
    std::string maskedRequestTokenText = hextostr(maskedRequestToken);
    
    uint8_t requestHash[CCCrypto::MD5_BUFFER_LENGTH];
    
    MD5_CTX ctx;
    MD5_EX_Init(&ctx);
    MD5_EX_Update(&ctx, const_cast<std::string::value_type*>(maskedAppBinaryHashText.c_str()), maskedAppBinaryHashText.size());
    MD5_EX_Update(&ctx, const_cast<std::string::value_type*>(maskedRequestTokenText.c_str()), maskedRequestTokenText.size());
    MD5_EX_Update(&ctx, const_cast<std::string::value_type*>(reqParam.c_str()), reqParam.size());
    MD5_EX_Final(requestHash, &ctx);

    return StringUtils::format("%03d-%s-%s-%s",
                               salt,
                               maskedAppBinaryHashText.c_str(),
                               maskedRequestTokenText.c_str(),
                               hextostr(requestHash).c_str());
}

bool PlatformUtils::isALittleDistance(cocos2d::Touch *now, cocos2d::Vec2 &prev)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
    auto glview = Director::getInstance()->getOpenGLView();
	Point moveDistance;
	moveDistance = ccpSub(now->getLocationInView(), prev);
	float dis;
	dis = sqrtf(moveDistance.x*moveDistance.x + moveDistance.y*moveDistance.y);
	float factor = ( glview->getScaleX() + glview->getScaleY() ) / 2;
	return fabs(dis * factor / Device::getDPI()) < LITTLE_DISTANCE;
#else
    return false;
#endif
}

float PlatformUtils::getViewHiddenHeight()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return PlatformUtils_objc::getViewHiddenHeight();
#else
	return 0.0f;
#endif
}

std::string PlatformUtils::urlEncode(const std::string &data)
{
    static const char* hextable = "0123456789abcdef";
    
    const char *baseTextPtr = data.c_str();
    size_t baseTextSize = data.size();
    
    char *encodedText = new char[data.size() * 3 + 1];
    char *encodedTextPtr = encodedText;
    
    for (int i = 0; i < baseTextSize; i++) {
        char ch = baseTextPtr[i];
        
        if (   ('0' <= ch && ch <= '9')
            || ('a' <= ch && ch <= 'z')
            || ('A' <= ch && ch <= 'Z')
            || ch == '-'
            || ch == '.'
            || ch == '_'
            || ch == '~'
            )
        {
            encodedTextPtr[0] = ch;
            encodedTextPtr += 1;
        }
        else {
            unsigned char chValue = static_cast<unsigned char>(ch);
            
            encodedTextPtr[0] = '%';
            encodedTextPtr[1] = hextable[(chValue & 0xf0) >> 4];
            encodedTextPtr[2] = hextable[chValue & 0x0f];
            
            encodedTextPtr += 3;
        }
    }
    
    encodedTextPtr[0] = '\0';
    std::string resultText = std::string(encodedText);
    
    delete[] encodedText;
    return resultText;
}

int PlatformUtils::compareVersionString(const std::string& str1, const std::string& str2)
{
    auto version1 = split(str1, '.');
    auto version2 = split(str2, '.');
    
    // major
    auto major1 = version1.size() > 0 ? atoi(version1[0].c_str()) : 0;
    auto major2 = version2.size() > 0 ? atoi(version2[0].c_str()) : 0;
    if (major1 != major2)
    {
        return major2 - major1;
    }
    
    // minor
    auto minor1 = version1.size() > 1 ? atoi(version1[1].c_str()) : 0;
    auto minor2 = version2.size() > 1 ? atoi(version2[1].c_str()) : 0;
    if (minor1 != minor2)
    {
        return minor2 - minor1;
    }
    
    // revision
    auto rev1 = version1.size() > 2 ? atoi(version1[2].c_str()) : 0;
    auto rev2 = version2.size() > 2 ? atoi(version2[2].c_str()) : 0;
    return rev2 - rev1;
}

std::vector<std::string> PlatformUtils::split(const std::string &str, char delimiter)
{
    std::vector<std::string> res;
    size_t current = 0, found;
    while((found = str.find_first_of(delimiter, current)) != std::string::npos)
    {
        res.push_back(std::string(str, current, found - current));
        current = found + 1;
    }
    res.push_back(std::string(str, current, str.size() - current));
    return res;
}



#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

static std::string cachePath;

std::string PlatformUtils::generateUUID()
{
	return PlatformUtils_objc::generateUUID();
}

std::string PlatformUtils::getAppName()
{
	return PlatformUtils_objc::getAppName();
}

std::string PlatformUtils::getVersionString()
{
	return PlatformUtils_objc::getVersionString();
}
//add byshixc 版本号
int PlatformUtils::getVersionCode()
{
    return PlatformUtils_objc::getVersionCode();
}
//end
std::string PlatformUtils::getCachePath() {
	if (cachePath.empty()) {
		cachePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	}
    return cachePath;
}

std::string PlatformUtils::getDownloadResourcePath() {
    if (cachePath.empty()) {
        cachePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    }
    return cachePath;
}

std::string PlatformUtils::getAppBinaryPath()
{
    return PlatformUtils_objc::getAppBinaryPath();
}

std::string PlatformUtils::getDeviceString()
{
	return PlatformUtils_objc::getDeviceString();
}

std::string PlatformUtils::getOSVersionString()
{
	return PlatformUtils_objc::getOSVersionString();
}

std::string PlatformUtils::getBrandString()
{
    return PlatformUtils_objc::getBrandString();
}

bool PlatformUtils::createDirectoryByFullPath(const char* dir) {
    return PlatformUtils_objc::createDirectoryByFullPath(dir);
}

bool PlatformUtils::addDoNotBackupAttribute(const char *path)
{
	// Android not support
	return false;
}

unsigned char* PlatformUtils::AES128Encode(const unsigned char *data, size_t dataSize, const char *key, const char *iv, size_t *size, bool compatibleMode) {
    return PlatformUtils_objc::AES128Cryption(0, data, dataSize, key, iv, size);
}

unsigned char* PlatformUtils::AES128Decode(const unsigned char *data, size_t dataSize, const char *key, const char *iv, size_t *size, bool compatibleMode) {
    return PlatformUtils_objc::AES128Cryption(1, data, dataSize, key, iv, size);
}

unsigned char* PlatformUtils::AES128Encode_Userid(const unsigned char *data, size_t dataSize, const char *key, const char *iv, size_t *size) {
    return PlatformUtils_objc::AES128Cryption_Userid(0, data, dataSize, key, iv, size);
}

cocos2d::Rect PlatformUtils::getUIScreenFrame() {
    //TODO:仮実装
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    return Rect(origin.x,origin.y,visibleSize.width,visibleSize.height);
}

cocos2d::Rect PlatformUtils::getUIScreenBounds() {
    //TODO:仮実装
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    return Rect(origin.x,origin.y,visibleSize.width,visibleSize.height);
}

long PlatformUtils::getUsedMemory()
{
	return PlatformUtils_objc::getUsedMemory();
}

void PlatformUtils::moveTaskToBack()
{
	PlatformUtils_objc::moveTaskToBack();
}

#endif
