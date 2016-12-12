
#include "PlatformUtils_objc.h"
#include "JavaClassNameKey.h"
#include <android/log.h>
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <sys/stat.h>

#define  LOG_TAG    "PlatformUtils_objc"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;
using namespace std;

extern "C" {

string PlatformUtils_objc::generateUUID() {
	std::string ret;
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_UUID, "generateUUID", "()Ljava/lang/String;"))
	{
		jstring jStr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		const char* str = t.env->GetStringUTFChars(jStr, nullptr);
		ret = str;

		t.env->ReleaseStringUTFChars(jStr, str);
		t.env->DeleteLocalRef(jStr);
		t.env->DeleteLocalRef(t.classID);
	}

	return ret;
}

string PlatformUtils_objc::getAppName() {
	std::string ret;
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_APPINFO, "getAppName", "()Ljava/lang/String;"))
	{
		jstring jStr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		const char* str = t.env->GetStringUTFChars(jStr, nullptr);
		ret = str;
#ifdef DEBUG
		CCLOG("RFCommon_objc::getVersionString : %s", ret.c_str());
#endif

		t.env->ReleaseStringUTFChars(jStr, str);
		t.env->DeleteLocalRef(jStr);
		t.env->DeleteLocalRef(t.classID);
	}

	return ret;
}

string PlatformUtils_objc::getVersionString() {
	std::string ret;
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_BUILDINFO, "getVersionName", "()Ljava/lang/String;"))
	{
		jstring jStr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		const char* str = t.env->GetStringUTFChars(jStr, nullptr);
		ret = str;
#ifdef DEBUG
		CCLOG("RFCommon_objc::getVersionString : %s", ret.c_str());
#endif

		t.env->ReleaseStringUTFChars(jStr, str);
		t.env->DeleteLocalRef(jStr);
		t.env->DeleteLocalRef(t.classID);
	}

	return ret;
}
int PlatformUtils_objc::getVersionCode() {
	int ret;
	JniMethodInfo t;
	jint jVersionId;
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_BUILDINFO, "getVersionCode", "()I"))
	{
		jVersionId = t.env->CallStaticIntMethod(t.classID, t.methodID);
		ret = jVersionId;
		t.env->DeleteLocalRef(t.classID);
	}

	return ret;
}
unsigned char* PlatformUtils_objc::AES128Cryption(int mode, const unsigned char *data, size_t dataSize, const char *key, const char *iv, size_t *size) {
	unsigned char *str = NULL;
	JniMethodInfo m;
	if (JniHelper::getStaticMethodInfo(m, CLASS_NAME_CRYPT, "crypt", "(I[BLjava/lang/String;Ljava/lang/String;)[B"))
	{
		//CCLOG("AES128Cryption 1");
		jbyteArray jDataArray = m.env->NewByteArray(dataSize);
		//CCLOG("AES128Cryption 2");
		jsize len = m.env->GetArrayLength(jDataArray);
		//CCLOG("AES128Cryption 3");
		jboolean isCopy;
		//CCLOG("AES128Cryption 4");
		jbyte *jDatas = m.env->GetByteArrayElements(jDataArray, &isCopy);
		//CCLOG("AES128Cryption 5");
		for(int i=0; i<dataSize; i++)
		{
				jDatas[i] = (jbyte)data[i];
		}
		//CCLOG("AES128Cryption 6");
		if (isCopy == JNI_TRUE)
		{
				m.env->ReleaseByteArrayElements(jDataArray, jDatas, 0);
		}
		else
		{
				m.env->ReleaseByteArrayElements(jDataArray, jDatas, JNI_COMMIT);
		}
		//CCLOG("AES128Cryption 7");
		jstring jKey = m.env->NewStringUTF(key);
		//CCLOG("AES128Cryption 8");
		jstring jIv = m.env->NewStringUTF(iv);
		//CCLOG("AES128Cryption 9");
		jbyteArray jResult = (jbyteArray)m.env->CallStaticObjectMethod(m.classID, m.methodID, (jint)mode, jDataArray, jKey, jIv);
		//CCLOG("AES128Cryption 10");
		len = m.env->GetArrayLength(jResult);
		jDatas = m.env->GetByteArrayElements(jResult, &isCopy);
		str = new unsigned char[(int)len + 1];
		for(int i=0; i<(int)len; i++)
		{
			str[i] = jDatas[i];
		}
		if (isCopy == JNI_TRUE)
		{
			m.env->ReleaseByteArrayElements(jResult, jDatas, 0);
		}
		else
		{
			m.env->ReleaseByteArrayElements(jResult, jDatas, JNI_COMMIT);
		}

		m.env->DeleteLocalRef(m.classID);
		*size = (int)len;
	}
	return str;
}

unsigned char* PlatformUtils_objc::AES128Cryption_Userid(int mode, const unsigned char *data, size_t dataSize, const char *key, const char *iv, size_t *size) {
	unsigned char *str = NULL;
	JniMethodInfo m;
	if (JniHelper::getStaticMethodInfo(m, CLASS_NAME_CRYPT, "crypt_userid", "(I[BLjava/lang/String;Ljava/lang/String;)[B"))
	{
		//CCLOG("AES128Cryption 1");
		jbyteArray jDataArray = m.env->NewByteArray(dataSize);
		//CCLOG("AES128Cryption 2");
		jsize len = m.env->GetArrayLength(jDataArray);
		//CCLOG("AES128Cryption 3");
		jboolean isCopy;
		//CCLOG("AES128Cryption 4");
		jbyte *jDatas = m.env->GetByteArrayElements(jDataArray, &isCopy);
		//CCLOG("AES128Cryption 5");
		for(int i=0; i<dataSize; i++)
		{
            jDatas[i] = (jbyte)data[i];
		}
		//CCLOG("AES128Cryption 6");
		if (isCopy == JNI_TRUE)
		{
            m.env->ReleaseByteArrayElements(jDataArray, jDatas, 0);
		}
		else
		{
            m.env->ReleaseByteArrayElements(jDataArray, jDatas, JNI_COMMIT);
		}
		//CCLOG("AES128Cryption 7");
		jstring jKey = m.env->NewStringUTF(key);
		//CCLOG("AES128Cryption 8");
		jstring jIv = m.env->NewStringUTF(iv);
		//CCLOG("AES128Cryption 9");
		jbyteArray jResult = (jbyteArray)m.env->CallStaticObjectMethod(m.classID, m.methodID, (jint)mode, jDataArray, jKey, jIv);
		//CCLOG("AES128Cryption 10");
		len = m.env->GetArrayLength(jResult);
		jDatas = m.env->GetByteArrayElements(jResult, &isCopy);
		str = new unsigned char[(int)len + 1];
		for(int i=0; i<(int)len; i++)
		{
			str[i] = jDatas[i];
		}
		if (isCopy == JNI_TRUE)
		{
			m.env->ReleaseByteArrayElements(jResult, jDatas, 0);
		}
		else
		{
			m.env->ReleaseByteArrayElements(jResult, jDatas, JNI_COMMIT);
		}
        
		m.env->DeleteLocalRef(m.classID);
		*size = (int)len;
	}
	return str;
}


bool PlatformUtils_objc::createDirectoryByFullPath(const char* dir)
{
        bool r = false;
        struct stat st;
        if (stat(dir, &st) != 0)
        {
                // 0755 dir make
                r = (mkdir(dir, S_IRWXU | (S_IRGRP | S_IXGRP) | (S_IROTH | S_IXOTH)) == 0);
        #ifdef DEBUG
                CCLOG("createDirectoryByFullPath done: %s, %d", dir, r);
        #endif
        }
        else
        {
#ifdef DEBUG
                CCLOG("createDirectoryByFullPath : %s is already exist.", dir);
#endif
                r = true;
        }
        return r;
}

std::string PlatformUtils_objc::getUseragent()
{
    std::string str;
    str = "";
    JniMethodInfo m;
    if (JniHelper::getStaticMethodInfo(m, CLASS_NAME_BUILDINFO, "getUseragent", "()Ljava/lang/String;"))
    {
        jstring ret = (jstring)m.env->CallStaticObjectMethod(m.classID, m.methodID);
        const char *buffer = m.env->GetStringUTFChars(ret, nullptr);
        str = buffer;
        m.env->ReleaseStringUTFChars(ret, buffer);
        m.env->DeleteLocalRef(ret);
        m.env->DeleteLocalRef(m.classID);
    }
    return str;
}

string PlatformUtils_objc::getDeviceString() {
	std::string ret;
	JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_BUILDINFO, "getModelName", "()Ljava/lang/String;"))
    {
        jstring jStr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        const char* str = t.env->GetStringUTFChars(jStr, nullptr);
        ret = str;
        
        t.env->ReleaseStringUTFChars(jStr, str);
        t.env->DeleteLocalRef(jStr);
        t.env->DeleteLocalRef(t.classID);
    }

	return ret;
}
    
string PlatformUtils_objc::getOSVersionString() {
	std::string ret;
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_BUILDINFO, "getOSVersion", "()Ljava/lang/String;"))
	{
		jstring jStr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		const char* str = t.env->GetStringUTFChars(jStr, nullptr);
		ret = str;

		t.env->ReleaseStringUTFChars(jStr, str);
		t.env->DeleteLocalRef(jStr);
		t.env->DeleteLocalRef(t.classID);
	}

	return ret;
}

std::string PlatformUtils_objc::getAppBinaryPath()
{
    std::string ret;
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_BUILDINFO, "getAppBinaryPath", "()Ljava/lang/String;"))
    {
        jstring jStr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        const char* str = t.env->GetStringUTFChars(jStr, nullptr);
        ret = str;
        
        t.env->ReleaseStringUTFChars(jStr, str);
        t.env->DeleteLocalRef(jStr);
        t.env->DeleteLocalRef(t.classID);
    }
    
    return ret;
}
    
float PlatformUtils_objc::getViewHiddenHeight()
{
	float ret = 0.0f;
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_APPINFO, "getViewHiddenHeight", "()F"))
	{
		ret = (float)t.env->CallStaticFloatMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}

	return ret;
}

string PlatformUtils_objc::getBrandString() {
    std::string ret;
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_BUILDINFO, "getBrandString", "()Ljava/lang/String;"))
    {
        jstring jStr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        const char* str = t.env->GetStringUTFChars(jStr, nullptr);
        ret = str;
        
        t.env->ReleaseStringUTFChars(jStr, str);
        t.env->DeleteLocalRef(jStr);
        t.env->DeleteLocalRef(t.classID);
    }
    
    return ret;
}

unsigned long PlatformUtils_objc::getUsedMemory()
{
	long ret = 0;
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_MEMORY, "getUsedMemory", "()J"))
	{
		ret = (long)t.env->CallStaticLongMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}

	return ret;
}

bool PlatformUtils_objc::moveTaskToBack()
{
	JniMethodInfo t;
	bool ret = false;

	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME_APPTASK, "moveTaskToBack", "()Z"))
	{
		ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}

	return ret;
}

}
