#ifndef _lyStringOper_H_
#define _lyStringOper_H_

/*** ***
	lyStringOper
	by Shixc 2014-01-28
*** ***/
#include <cctype>
#include <iostream> 

#include <algorithm>



class lyStringOper
{
public:
	//c语言格式的字符串大小转换
	static const char* CToLower(const char* szInStr, char* szOutStr, unsigned short& wLen);
	static const char* CToUpper(const char* szInStr, char* szOutStr, unsigned short& wLen);
	//C++语言格式的字符串大小转换
	static void CppToLower(std::string& s);
	static void CppToUpper(std::string& s);
	//计算字符串字符个数
	static int CalcCount(const char * pszText);
	//编码格式转换
	//Wstr类型转换成utf8
	static void WStr2UTF8(std::string& dest, const std::wstring& src);
	static std::string WStrToUTF8(const std::wstring& str);


	static bool IsAllChinese(unsigned char* szStr);
	static bool IsNoneChinese(unsigned char* szStr);
	static bool IsAllNumber(unsigned char* szStr);
	static bool IsNoneNumber(unsigned char* szStr);


private:
	char ToLower_( char c );
	char ToUpper_( char c );
};


#endif //_lyStringOper_H_
