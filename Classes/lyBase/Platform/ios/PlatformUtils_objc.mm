
#include "PlatformUtils.h"
#import <CommonCrypto/CommonCryptor.h>
#import <sys/sysctl.h>
#import <mach/mach.h>
#import <mach/mach_host.h>
#import <sys/xattr.h>

USING_NS_CC;
USING_NS_CC_EXT;

std::string static_getAppName()
{
    NSString *appName = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleDisplayName"];
    return [appName UTF8String];
}

std::string PlatformUtils::getAppName()
{
    return static_getAppName();
}

const char* static_getVersionString() {
    return [[[NSBundle mainBundle] objectForInfoDictionaryKey: @"CFBundleShortVersionString"] UTF8String];
}
const char* static_getBuildVersionString() {
    return [[[NSBundle mainBundle] objectForInfoDictionaryKey: @"CFBundleVersion"] UTF8String];
}

std::string static_generateUUID() {
    CFUUIDRef uuidRef = CFUUIDCreate(nil);
    NSString *uuid = [(NSString*) CFUUIDCreateString(nil, uuidRef) autorelease];
    return [uuid UTF8String];
}

std::string PlatformUtils::getVersionString() {
    return std::string(static_getVersionString());
}
std::string PlatformUtils::getBuildVersionString()
{
    return std::string(static_getBuildVersionString());
}
std::string PlatformUtils::generateUUID() {
    return static_generateUUID();
}

std::string PlatformUtils::getCachePath()
{
//    return static_getCachePath();
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
    NSString *cacheDirectory = [paths objectAtIndex:0];
    std::string strRet = [cacheDirectory UTF8String];
    strRet.append("/");
    return strRet;
}

std::string PlatformUtils::getDocumentPath()
{
//    return static_getDocumentPath();
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentationDirectory, NSUserDomainMask, YES);
    NSString *documentDirectory = [paths objectAtIndex:0];
    NSError *error = nil;
    
    std::string strRet = [documentDirectory UTF8String];
    strRet.append("/");
    return strRet;
}

std::string PlatformUtils::getDownloadResourcePath()
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
    NSString *documentDirectory = [paths objectAtIndex:0];
    NSError *error = nil;
    
    std::string strRet = [documentDirectory UTF8String];
    strRet.append("/");
    return strRet;
}

std::string static_getCachePath()
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
    NSString *cacheDirectory = [paths objectAtIndex:0];
    std::string strRet = [cacheDirectory UTF8String];
    strRet.append("/");
    return strRet;
}

std::string static_getDocumentPath()
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentationDirectory, NSUserDomainMask, YES);
    NSString *documentDirectory = [paths objectAtIndex:0];
    NSError *error = nil;
    
    std::string strRet = [documentDirectory UTF8String];
    strRet.append("/");
    return strRet;
}

const char* static_getDeviceString() {
    size_t size;
    sysctlbyname("hw.machine", NULL, &size, NULL, 0);
    char *machine = (char*)malloc(size);
    sysctlbyname("hw.machine", machine, &size, NULL, 0);
    NSString *platformName = [NSString stringWithCString:machine encoding:NSUTF8StringEncoding];
    free(machine);
    
    return [platformName UTF8String];
}

std::string PlatformUtils::getDeviceString() {
    return std::string(static_getDeviceString());
}

const char* static_getOSVersionString() {
    return [ [[UIDevice currentDevice]systemVersion] UTF8String];
}

std::string PlatformUtils::getOSVersionString() {
    return std::string(static_getOSVersionString());
}

std::string PlatformUtils::getBrandString() {
    return "";
}

std::string PlatformUtils::getAppBinaryPath()
{
    NSString *appFilePath = [[NSBundle mainBundle]  executablePath];
    
    return [appFilePath UTF8String];
}

@interface NSData (NSData_Extension)
- (NSData *)AES128Operation:(CCOperation)operation key:(NSString *)key iv:(NSString *)iv;
- (NSData *)AES128Encrypt:(NSString *)key iv:(NSString *)iv;
- (NSData *)AES128Decrypt:(NSString *)key iv:(NSString *)iv;
@end

//------------------------------------------------------------------------------------------
// AES128
@implementation NSData (NSData_Extension)
- (NSData *)AES128Operation:(CCOperation)operation key:(NSString *)key iv:(NSString *)iv compatibleMode:(bool)compatibleMode
{
    char keyBuf[kCCKeySizeAES128 + 1];
    memset(keyBuf, 0, sizeof(keyBuf));
    [key getCString:keyBuf maxLength:sizeof(keyBuf) encoding:NSUTF8StringEncoding];
    
    char ivBuf[kCCBlockSizeAES128 + 1];
    memset(ivBuf, 0, sizeof(ivBuf));
    [iv getCString:ivBuf maxLength:sizeof(ivBuf) encoding:NSUTF8StringEncoding];
    
    NSUInteger dataLength = [self length];
    size_t bufferSize = dataLength + kCCBlockSizeAES128;
    void *buffer = malloc(bufferSize);
    
    size_t numBytesCrypted = 0;
    CCCryptorStatus cryptStatus = CCCrypt(operation,
                                          kCCAlgorithmAES128,
                                          kCCOptionPKCS7Padding | (compatibleMode ? kCCOptionECBMode : 0x0000),
                                          keyBuf,
                                          kCCBlockSizeAES128,
                                          ivBuf,
                                          [self bytes],
                                          dataLength,
                                          buffer,
                                          bufferSize,
                                          &numBytesCrypted);
    
    if (cryptStatus == kCCSuccess) {
        return [NSData dataWithBytesNoCopy:buffer length:numBytesCrypted];
    }
    free(buffer);
    return nil;
}

- (NSData *)AES128Encrypt:(NSString *)key iv:(NSString *)iv compatibleMode:(bool)compatibleMode
{
    return [self AES128Operation:kCCEncrypt key:key iv:iv compatibleMode:compatibleMode];
}

- (NSData *)AES128Decrypt:(NSString *)key iv:(NSString *)iv compatibleMode:(bool)compatibleMode
{
    return [self AES128Operation:kCCDecrypt key:key iv:iv compatibleMode:compatibleMode];
}
@end

unsigned char* static_AES128Encode(const unsigned char *data, size_t dataSize, const char *key, const char *iv, size_t *size, bool compatibleMode) {
    NSString *_key = [NSString stringWithCString:key encoding:NSUTF8StringEncoding];
    NSString *_iv = [NSString stringWithCString:iv encoding:NSUTF8StringEncoding];
    
    NSData *tmp =  [NSData dataWithBytes:(const void *)data length:dataSize];
    NSData *en_data = [tmp AES128Encrypt:_key iv:_iv compatibleMode:compatibleMode];
    
    size_t len = [en_data length];
    unsigned char* byteData = new unsigned char[len];
    memcpy(byteData, [en_data bytes], len);
    
    if(size != NULL) {
        *size = len;
    }
    
    return byteData;
}

unsigned char* static_AES128Decode(const unsigned char *data, size_t dataSize, const char *key, const char *iv, size_t *size, bool compatibleMode) {
    NSString *_key = [NSString stringWithCString:key encoding:NSUTF8StringEncoding];
    NSString *_iv = [NSString stringWithCString:iv encoding:NSUTF8StringEncoding];
    
    NSData *tmp =  [NSData dataWithBytes:(const void *)data length:dataSize];
    NSData *de_data = [tmp AES128Decrypt:_key iv:_iv compatibleMode:compatibleMode];
    
    size_t len = [de_data length];
    unsigned char* byteData = new unsigned char[len];
    memcpy(byteData, [de_data bytes], len);
    
    if(size != NULL) {
        *size = len;
    }
    
    return byteData;
}

unsigned char* PlatformUtils::AES128Encode(const unsigned char *data, size_t dataSize, const char *key, const char *iv, size_t *size, bool compatibleMode) {
    return static_AES128Encode(data, dataSize, key, iv, size, compatibleMode);
}

unsigned char* PlatformUtils::AES128Decode(const unsigned char *data, size_t dataSize, const char *key, const char *iv, size_t *size, bool compatibleMode) {
    return static_AES128Decode(data, dataSize, key, iv, size, compatibleMode);
}

void static_createDirectoryByFullPath(const char* dir) {
    NSString* path = [NSString stringWithCString: dir encoding:NSUTF8StringEncoding];
    [[NSFileManager defaultManager] createDirectoryAtPath:path withIntermediateDirectories:NO attributes:nil error:nil];
}

bool PlatformUtils::createDirectoryByFullPath(const char* dir) {
    static_createDirectoryByFullPath(dir);
    return true;
}

bool PlatformUtils::addDoNotBackupAttribute(const char *cpath)
{
    NSError *error = nil;
    NSString *path = [NSString stringWithCString: cpath encoding:NSUTF8StringEncoding];
    NSURL *url = [NSURL fileURLWithPath:path];
    BOOL success = [url setResourceValue: [NSNumber numberWithBool: YES]
                                  forKey: NSURLIsExcludedFromBackupKey error: &error];

    return success;
}

cocos2d::Rect static_getUIScreenBounds() {
    CGRect rect = [[UIScreen mainScreen] bounds];
    return cocos2d::Rect(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}
cocos2d::Rect static_getUIScreenFrame() {
    CGRect rect = [[UIScreen mainScreen] applicationFrame];
    return cocos2d::Rect(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

cocos2d::Rect PlatformUtils::getUIScreenFrame() {
    return static_getUIScreenFrame();
}
cocos2d::Rect PlatformUtils::getUIScreenBounds() {
    return static_getUIScreenBounds();
}

long PlatformUtils::getUsedMemory()
{
    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;
    
    if (task_info(current_task(), TASK_BASIC_INFO, (task_info_t)&t_info, &t_info_count) != KERN_SUCCESS)
    {
        return 0;
    }
    
    return t_info.resident_size;
}

void PlatformUtils::moveTaskToBack()
{
}
