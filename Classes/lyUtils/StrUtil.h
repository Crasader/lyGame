//
//  StrUtil.h
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#ifndef __CoreAppFramework__StrUtil__
#define __CoreAppFramework__StrUtil__

#include <string>
#include <vector>

class StrUtil
{
public:
    static std::string getFileName(const std::string &inPath);
    static std::string getBaseName(const std::string &inPath);
    static std::string getExtension(const std::string &inFileName);
    
    static bool isInteger(const std::string &str);
    static bool isNumeric(const std::string &str);
    static std::vector<std::string> componentsSeparatedByString(const std::string &str, const std::string &delimit);
    
    static bool isIntegerChar(const char chr);
    static int charToInt(const char chr);
    //    static int cstrToInt(const char* chrs);
    static int xcharToInt(const char xchr);
    //    static int xcstrToInt(const char* xchrs);
    static void strReplace(std::string& str, const std::string& from, const std::string& to);

    static std::string urlencode(const std::string &str);
    static std::string trim(const std::string& string, const char* trimCharacterList = " \t\v\r\n");
};

#endif /* defined(__CoreAppFramework__StrUtil__) */
