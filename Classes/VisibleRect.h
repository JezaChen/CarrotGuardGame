/**
* @brief 
* @details 
* @extends 
* @see 
* @authors ³Â½¨ÕÃ
* @date 20180315
* */
#pragma once
#ifndef VISIBLE_RECT_H
#define VISIBLE_RECT_H

#include "cocos2d.h"

class VisibleRectUtil
{
public:
    static cocos2d::Rect getVisibleRect();

    static cocos2d::Vec2 left();
    static cocos2d::Vec2 right();
    static cocos2d::Vec2 top();
    static cocos2d::Vec2 bottom();
    static cocos2d::Vec2 center();
    static cocos2d::Vec2 leftTop();
    static cocos2d::Vec2 rightTop();
    static cocos2d::Vec2 leftBottom();
    static cocos2d::Vec2 rightBottom();

private:
    static void init();
    static cocos2d::Rect s_visibleRect;
};

#endif // !VISIBLE_RECT_H
