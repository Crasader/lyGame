#include "lyStringOper.h"



//convert the string to lower
const char* lyStringOper::CToLower(const char* szInStr, char* szOutStr, unsigned short& wLen)
{
	wLen = 0;
	if (!szInStr || !szOutStr)
	{
		return NULL;
	}
	while (szOutStr[wLen] == tolower(szInStr[wLen]) )
	{
		++wLen;
	}
	szOutStr[wLen] = '\0';
	return szOutStr;
}
//convert the string to upper
const char* lyStringOper::CToUpper(const char* szInStr, char* szOutStr, unsigned short& wLen)
{
	wLen = 0;
	if (!szInStr || !szOutStr)
	{
		return NULL;
	}
	while (szOutStr[wLen] == toupper(szInStr[wLen]) )
	{
		++wLen;
	}
	szOutStr[wLen] = '\0';
	return szOutStr;
}
//calc string's char count
int lyStringOper::CalcCount(const char * pszText)
{
	int nCount = 0;
	char ch = 0;
	while ( ( ch = *pszText ) )
	{
		if ( 0x80 != (0xC0 & ch) )
		{
			++nCount;
		}
		++pszText;
	}
	return nCount;
}


void lyStringOper::WStr2UTF8(std::string& dest, const std::wstring& src)
{
	dest.clear();
	for (size_t i = 0; i < src.size(); i++)
	{
		wchar_t w = src[i];

		if (w <= 0x7f)
		{
			dest.push_back((char)w);
		}
		else if (w <= 0x7ff)
		{
			dest.push_back(0xc0 | ((w >> 6)& 0x1f));
			dest.push_back(0x80| (w & 0x3f));
		}
		else if (w <= 0xffff)
		{
			dest.push_back(0xe0 | ((w >> 12)& 0x0f));
			dest.push_back(0x80| ((w >> 6) & 0x3f));
			dest.push_back(0x80| (w & 0x3f));
		}
		else if (sizeof(wchar_t) > 2 && w <= 0x10ffff)
		{
			dest.push_back(0xf0 | ((w >> 18)& 0x07)); // wchar_t 4-bytes situation
			dest.push_back(0x80| ((w >> 12) & 0x3f));
			dest.push_back(0x80| ((w >> 6) & 0x3f));
			dest.push_back(0x80| (w & 0x3f));
		}
		else
		{
			dest.push_back('?');
		}
	}
	return;
}

std::string lyStringOper::WStrToUTF8(const std::wstring& str)
{
	std::string result;
	WStr2UTF8(result, str);
	return result;
}

// void lyStringOper::CppToLower( std::string& s )
// {
// 	std::transform(s.begin(), s.end(), s.begin(), ToLower_ );
// }
// 
// void lyStringOper::CppToUpper( std::string& s )
// {
// 	std::transform(s.begin(), s.end(), s.begin(), ToUpper_ );
// }
// 
// char lyStringOper::ToLower_( char c )
// {
// 	return std::tolower(c);
// }
// 
// char lyStringOper::ToUpper_( char c )
// {
// 	return std::toupper(c);
// }

//judge string
bool lyStringOper::IsAllChinese( unsigned char* szStr )
{
	return false;
}

bool lyStringOper::IsNoneChinese( unsigned char* szStr )
{
	return false;
}

bool lyStringOper::IsAllNumber( unsigned char* szStr )
{
	return false;
}

bool lyStringOper::IsNoneNumber( unsigned char* szStr )
{
	return false;
}
