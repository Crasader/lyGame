//
//  LoadingLayer.h
//  VitaminProject
//
//  Created by Yasunori Goto on 2014/11/14.
//  Copyright 2014 GCREST,Inc. All rights reserved.
//

#ifndef __VitaminProject__LoadingLayer__
#define __VitaminProject__LoadingLayer__

//#include "ApplicationManager.h"

class LoadingLayerParameter
{
public:
    std::string _tipText;
};

class LoadingLayer
{
public:
    //CREATE_WITH_FORMAT_FUNC(LoadingLayer);

    LoadingLayer();
    ~LoadingLayer();
    virtual void onEnter();
    void setSceneParameter(LoadingLayerParameter *param);

private:
    void nextScene(float dt);

    LoadingLayerParameter _param;
};


#endif /* defined(__VitaminProject__LoadingLayer__) */
