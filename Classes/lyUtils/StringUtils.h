//
//  StringUtils.h
//  Gcrest
//
//  Created by 横道 晃司 on 2014/08/14.
//
//

#ifndef Gcrest_StringUtils_h
#define Gcrest_StringUtils_h

// TODO: とりあえずcocos2d-xのやつよぶ
#include "deprecated/CCString.h"

#include <vector>
#include <string>
#include <functional>
#include <sstream>

//namespace Donut {
//    
//namespace StringUtils {
// 
//    template<typename T>
//    std::string toString(T arg)
//    {
//        std::stringstream ss;
//        ss << arg;
//        return ss.str();
//    }
//    
//    std::string format(const char* format, ...)
//    {
//#define CC_MAX_STRING_LENGTH (1024*100)
//        
//        std::string ret;
//        
//        va_list ap;
//        va_start(ap, format);
//        
//        char* buf = (char*)malloc(CC_MAX_STRING_LENGTH);
//        if (buf != nullptr)
//        {
//            vsnprintf(buf, CC_MAX_STRING_LENGTH, format, ap);
//            ret = buf;
//            free(buf);
//        }
//        va_end(ap);
//        
//        return ret;
//    }
//}
//    
//}

#endif
