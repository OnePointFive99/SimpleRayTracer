#pragma once
#ifndef RAY_H
#define RAY_H
#include"vec3.h"

//�������̣�y = origin + t * dir
class ray
{
public:
    ray() {}//Ĭ�Ϲ��캯��
    //�����޸Ķ���ֵ�ĺ�������Ϊconst����
    ray(const point3& origin, const vec3& direction) :
        orig(origin), dir(direction) {}//���캯��
    point3 origin() const { return orig; }
    vec3 direction() const{ return dir; }

    point3 at(double t) const {
        return orig + t * dir;
    }

    point3 orig;
    vec3 dir;
};

#endif // !RAY_H

