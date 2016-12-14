//
//  VitaminCoreLayerModule.cpp
//  client-vitamin
//
//  Created by 後藤 靖則 on 2016/06/07.
//
//

#include "VitaminCoreLayerModule.h"

VitaminCoreLayerModule::VitaminCoreLayerModule()
: _parent(nullptr)
{
}

VitaminCoreLayerModule::~VitaminCoreLayerModule()
{
}

void VitaminCoreLayerModule::init(VitaminCoreLayer *parent)
{
    _parent = parent;
}
