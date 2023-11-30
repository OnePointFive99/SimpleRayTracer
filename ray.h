#pragma once
#ifndef RAY_H
#define RAY_H
#include"vec3.h"

//参数方程，y = origin + t * dir
class ray
{
public:
    ray() {}//默认构造函数
    //不会修改对象值的函数声明为const函数
    ray(const point3& origin, const vec3& direction) :
        orig(origin), dir(direction) {}//构造函数
    point3 origin() const { return orig; }
    vec3 direction() const{ return dir; }

    point3 at(double t) const {
        return orig + t * dir;
    }

    point3 orig;
    vec3 dir;
};

#endif // !RAY_H

