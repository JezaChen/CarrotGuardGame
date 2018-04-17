//
//  LayerBase.cpp
//  CarrotFantasy
//
//  Created by ºÎãü±ø on 18-4-7.
//
//

#include "EntityLayerBase.h"
#include "Entity.h"

void EntityLayerBase::addEntity(Entity *pEntity)
{
	addChild(pEntity);
}