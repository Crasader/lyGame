//
//  LocalizedString.cpp
//
//  ly-Game
//
//  Created by loveyur on 2016/12/14
//  Copyright 2016 loveyur. All rights reserved.
//
//

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

#include "LocalizedString.h"

static map<std::string,std::string> localizedStrings;

const char * LocalizedString(const char * mKey,const char * mComment)
{
	LanguageType curLanguage = Application::getInstance()->getCurrentLanguage();
    const char * fileName;
    switch (curLanguage) {
        case LanguageType::ENGLISH:
            fileName = "Localized_en";
            break;
        case LanguageType::JAPANESE:
            fileName = "Localized_jp";
            break;
        /**
         case for more localize
         */
        default:
            fileName = "Localized_en";
            break;
    }

    std::string resultStr;
    
    if (localizedStrings.empty()) 
    {
        // Initialize variables needed
        ssize_t fileSize = 0;
        unsigned char * fileContents = nullptr;
        string line, fullPath, contents;
        
        // Get absolute path of file
        fullPath = CCFileUtils::getInstance()->fullPathForFilename( fileName );
        
        // Get data of file
        fileContents = FileUtils::getInstance()->getFileData( fullPath, "r", &fileSize );
        contents.append( ( char * ) fileContents );
        
        // Create a string stream so that we can use getline( ) on it
        istringstream fileStringStream( contents );
        
        // Get file contents line by line
        while ( std::getline( fileStringStream, line ) )
		{
//            debug_Printf("line :%s",line.c_str());
            if (line.find("/*",0) == string::npos &&
                line.find("//",0) == string::npos &&
                line.find("*/",0) == string::npos ) //filter the valid string of one line
            {
//                debug_Printf("find the line not start with \" /* \"");
                std::string::size_type validPos= line.find('=',0);
                if ( validPos != string::npos) 
                {
//                    debug_Printf("fimd the line contain \" = \"");
                    std::string keyStr = line.substr(0,validPos-1);
                    std::string subStr = line.substr(validPos+1,line.size()-1); // get valid string
 
                    //trim space
                    keyStr.erase(0, keyStr.find_first_not_of(" \t"));
                    keyStr.erase(keyStr.find_last_not_of(" \t") + 1);
                    
                    subStr.erase(0, subStr.find_first_not_of(" \t"));
                    subStr.erase(subStr.find_last_not_of(" \t") + 1);
                    
                    //trim \" 
                    keyStr.erase(0, keyStr.find_first_not_of("\""));
                    keyStr.erase(keyStr.find_last_not_of("\"") + 1);
                    
                    subStr.erase(0, subStr.find_first_not_of("\""));
                    
                    
                    //trim ; character and last \" character
                    subStr.erase(subStr.find_last_not_of(";") + 1);
                    subStr.erase(subStr.find_last_not_of("\"") + 1);
                    
                    
                    //replace line feed with \n
                    string::size_type pos(0);
                    string old_value("\\n");
                    if((pos=subStr.find(old_value))!=string::npos)
                    {
                        for(; pos!=string::npos; pos+=1)
                        {   
                            if((pos=subStr.find(old_value,pos))!=string::npos)
                            {
                                subStr.erase(pos, 2);
                                subStr.insert(pos, 1, '\n');
                            }   
                            else   
                                break;
                        }
                    }
                    
                    localizedStrings.insert(std::pair<std::string, std::string>(keyStr,subStr));
                    
                    const char * keyChars = keyStr.c_str();
                    
                    if (strcmp(keyChars,mKey) == 0) {
                        resultStr = subStr;
                    }
                }
            }
        }
        //must delete fileContents
        if (fileContents!= nullptr) {
            delete [] fileContents;
            fileContents = nullptr;
        }
        
        //return valid value
        if (resultStr.length() > 0){
            return (string(resultStr)).c_str();
        }
        return mKey;
    }
    else
    {
        std::map<std::string,std::string>::iterator itr = localizedStrings.find(std::string(mKey));
        if (itr != localizedStrings.end()) {
            return (itr->second).c_str();
        }
    }
    return mKey;
}
