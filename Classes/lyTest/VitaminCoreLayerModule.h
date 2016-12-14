//
//  VitaminCoreLayerModule.hpp
//  client-vitamin
//
//  Created by 後藤 靖則 on 2016/06/07.
//
//

#ifndef VitaminCoreLayerModule_h
#define VitaminCoreLayerModule_h

#include "cocos2d.h"

class VitaminCoreLayer;

class VitaminCoreLayerModule
{
public:
    VitaminCoreLayerModule();
    virtual ~VitaminCoreLayerModule();
    virtual void init(VitaminCoreLayer *layer);

protected:
    VitaminCoreLayer *_parent;
};

#endif /* VitaminCoreLayerModule_h */
