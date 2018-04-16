#pragma once
#include "cocos2d.h"
#include <list>

USING_NS_CC;

inline double dist(double ax, double ay, double bx, double by)
{
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}

class routeTo
{
private:
    double x;
    double y;
    float timeExec;
public:
    routeTo(double x, double y, int time) :x(x), y(y), timeExec(time) {}
    void setX(double newX)
    {
        x = newX;
    }
    void setY(double newY)
    {
        y = newY;
    }
    double getX()
    {
        return x;
    }
    double getY()
    {
        return y;
    }
    void setTime(int newTime)
    {
        timeExec = newTime;
    }
    int getTime()
    {
        return timeExec;
    }
    Vec2 toVec2()
    {
        return Vec2(x, y);
    }
};

class routeToList
{
private:
    Vector<FiniteTimeAction*> routes;
    double former_x, former_y;
public:
    void addRoute(routeTo r)
    {
        routes.pushBack(MoveTo::create(r.getTime(),Vec2(r.getX(), r.getY())));
        former_x = r.getX();
        former_y = r.getY();
    }
    void addRoute4Time(double x, double y, float time)
    {
        former_x = x;
        former_y = y;
        routes.pushBack(MoveTo::create(time, Vec2(x, y)));
    }
    void addRoute4Speed(double x, double y, double speed)
    {
        FiniteTimeAction* formerRoute = routes.front();
        
        double dst = dist(x, y, former_x, former_y);
        former_x = x; former_y = y;
        double time = dst / speed;
        addRoute4Time(x, y, time);
    }
    void run(Sprite* s)
    {
        auto seq = Sequence::create(routes);
        s->runAction(seq);
    }
};