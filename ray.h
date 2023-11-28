#pragma once
#ifndef RAY_H
#define RAY_H
#include"vec3.h"

//参数方程，y = origin + t * dir
class ray
{
public:
    ray() {}
    ray(const point3& origin, const vec3& direction) :
        orig(origin), dir(direction) {}
    point3 origin() { return orig; }
    vec3 direction() { return dir; }

    point3 at(double t) const {
        return orig + t * dir;
    }

    point3 orig;
    vec3 dir;
};

#endif // !RAY_H

