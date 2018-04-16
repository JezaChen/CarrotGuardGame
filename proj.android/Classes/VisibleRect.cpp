#include "VisibleRect.h"

USING_NS_CC;

Rect VisibleRectUtil::s_visibleRect;

void VisibleRectUtil::init()
{
    s_visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
}

cocos2d::Rect VisibleRectUtil::getVisibleRect()
{
    init();
    return s_visibleRect;
}

cocos2d::Vec2 VisibleRectUtil::left()
{
    init();
    return cocos2d::Vec2(s_visibleRect.origin.x, s_visibleRect.origin.y + s_visibleRect.size.height / 2);
}

cocos2d::Vec2 VisibleRectUtil::right()
{
    init();
    return cocos2d::Vec2(s_visibleRect.origin.x + s_visibleRect.size.width, s_visibleRect.origin.y + s_visibleRect.size.height / 2);
}

cocos2d::Vec2 VisibleRectUtil::top()
{
    init();
    return cocos2d::Vec2(s_visibleRect.origin.x + s_visibleRect.size.width / 2, s_visibleRect.origin.y + s_visibleRect.size.height);
}

cocos2d::Vec2 VisibleRectUtil::bottom()
{
    init();
    return cocos2d::Vec2(s_visibleRect.origin.x + s_visibleRect.size.width / 2, s_visibleRect.origin.y);
}

cocos2d::Vec2 VisibleRectUtil::center()
{
    init();
    return cocos2d::Vec2(s_visibleRect.origin.x + s_visibleRect.size.width / 2, s_visibleRect.origin.y + s_visibleRect.size.height / 2);
}

cocos2d::Vec2 VisibleRectUtil::leftBottom()
{
    init();
    return s_visibleRect.origin;
}

cocos2d::Vec2 VisibleRectUtil::leftTop()
{
    init();
    return cocos2d::Vec2(s_visibleRect.origin.x, s_visibleRect.origin.y + s_visibleRect.size.height);
}

cocos2d::Vec2 VisibleRectUtil::rightBottom()
{
    init();
    return cocos2d::Vec2(s_visibleRect.origin.x + s_visibleRect.size.width, s_visibleRect.origin.y);
}

cocos2d::Vec2 VisibleRectUtil::rightTop()
{
    init();
    return cocos2d::Vec2(s_visibleRect.origin.x + s_visibleRect.size.width, s_visibleRect.origin.y + s_visibleRect.size.height);
}

