//
//  StrUtil.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "StrUtil.h"
#include <string>
#include <algorithm>

using namespace std;

/*!
 * パスからファイル名のみ取り出す
 * @param[in] path パス
 * @return ファイル名
 */
std::string StrUtil::getFileName(const std::string &path)
{
    size_t pos1;
    
    pos1 = path.rfind('\\');
    if (pos1 != std::string::npos)
    {
        return path.substr(pos1+1, path.size()-pos1-1);
    }
    
    pos1 = path.rfind('/');
    if (pos1 != std::string::npos)
    {
        return path.substr(pos1+1, path.size()-pos1-1);
    }
    
    return path;
}

/*!
 * パスからファイルベース名のみ取り出す
 * @param[in] path パス
 * @return ファイル名
 */
std::string StrUtil::getBaseName(const std::string &inPath)
{
    size_t pos1;
    std::string path = std::string(inPath.c_str());
    
    pos1 = path.rfind('\\');
    if (pos1 != std::string::npos)
    {
        path = path.substr(pos1+1, path.size()-pos1-1);
    }
    
    pos1 = path.rfind('/');
    if (pos1 != std::string::npos)
    {
        path = path.substr(pos1+1, path.size()-pos1-1);
    }
    
    pos1 = path.rfind('.');
    if (pos1 != std::string::npos)
    {
        path = path.substr(0, pos1);
    }
    
    return path;
}

/*!
 * ファイル名から拡張子を取り出す
 * @param[in] path パス
 * @return ファイル名
 */
std::string StrUtil::getExtension(const std::string &inFileName)
{
    std::string filename(inFileName.c_str());
    std::string::size_type idx;
    std::string extension;
    
    idx = filename.rfind('.');
    
    if(idx != std::string::npos)
    {
        extension = filename.substr(idx+1);
    }
    else
    {
        extension = "";
    }
    return extension;
}

/*!
 * 文字列が整数値を表しているかを調べる
 * @param[inout] str 文字列
 * @return 整数値ならtrue
 */
bool StrUtil::isInteger(const std::string &str)
{
    if(str.find_first_not_of("-0123456789 \t") != std::string::npos) {
        return false;
    }
    
    return true;
}

/*!
 * 文字列が実数値を表しているかを調べる
 * @param[inout] str 文字列
 * @return 実数値ならtrue
 */
bool StrUtil::isNumeric(const std::string &str)
{
    if(str.find_first_not_of("-0123456789. Ee\t") != std::string::npos) {
        return false;
    }
    
    return true;
}

std::vector<std::string> StrUtil::componentsSeparatedByString(const std::string &inStr, const std::string &delimit)
{
    std::vector<std::string> result;
    std::string str = std::string(inStr.c_str());
    int    ptr;
    while ((ptr = str.find_first_of(delimit)) != str.npos)
    {
        if (ptr > 0)
        {
            result.push_back(str.substr(0, ptr));
        }
        str = str.substr(ptr + 1);
    }
    
    if (str.length() > 0)
    {
        result.push_back(str);
    }
    return result;
}


bool StrUtil::isIntegerChar(const char chr)
{
    return (chr >= 0x30 && chr <= 0x39);
}

int StrUtil::charToInt(const char chr)
{
    int     result = 0;
    //    char    chars[2];
    //    chars[0] = chr;
    //    chars[1] = '\0';
    
    //    result = std::atoi(chars);
    //std::sscanf(chars, "%d", &result);
    
    if (chr >= 0x30 && chr <= 0x39)
    {
        result = (int)chr - 0x30;
    }
    
    
    return result;
}

/*
 int StrUtil::cstrToInt(const char* chrs)
 {
 //    int     result = 0;
 //    std::sscanf(chrs, "%d", &result);
 //    return result;
 
 return std::atoi(chrs);
 }
 */

int StrUtil::xcharToInt(const char xchr)
{
    //    int     result = 0;
    //    char    chars[2];
    //    chars[0] = xchr;
    //    chars[1] = '\0';
    //    std::sscanf(chars, "%x", &result);
    
    int result = 0;
    if (xchr >= 0x30 && xchr <= 0x39)
    {
        result = (int)xchr - 0x30;
    }
    else
    {
        switch (xchr) {
            case 'a':
            case 'A':
                result = 10;
                break;
            case 'b':
            case 'B':
                result = 11;
                break;
            case 'c':
            case 'C':
                result = 12;
                break;
            case 'd':
            case 'D':
                result = 13;
                break;
            case 'e':
            case 'E':
                result = 14;
                break;
            case 'f':
            case 'F':
                result = 15;
                break;
            default:
                result = 0;
                break;
        }
    }
    
    
    return result;
}

/*
 int StrUtil::xcstrToInt(const char* xchrs)
 {
 int     result = 0;
 std::sscanf(xchrs, "%x", &result);
 
 return result;
 }
 */

// 文字列中から文字列を検索して別の文字列に置換する
void StrUtil::strReplace(std::string& str, const std::string& from, const std::string& to) {
    std::string::size_type pos = 0;
    while(pos = str.find(from, pos), pos != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
}

// 与えられた文字列をurlエンコードして返す
string StrUtil::urlencode(const string& str)
{
    const string url_letters("-.0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz~");
    std::string ret;

    for (string::const_iterator p = str.begin(); p != str.end(); ++p)
    {
        if (binary_search(url_letters.begin(), url_letters.end(), *p))
        {
            ret += *p;
        }
        else
        {
            char work[32];
            sprintf(work, "%%%02X", *p & 0xFF);
            ret += work;
        }
    }
    
    return ret;
}

std::string StrUtil::trim(const std::string& string, const char* trimCharacterList)
{
    std::string result;
    std::string::size_type left = string.find_first_not_of(trimCharacterList);
    if (left != std::string::npos)
    {
        std::string::size_type right = string.find_last_not_of(trimCharacterList);
        result = string.substr(left, right - left + 1);
    }
    
    return result;
}
