#pragma once
#ifndef HITTABLE_H
#include"vec3.h"
#include"ray.h"

//记录交点，交点法线，交点t值，交点是否在物体表面，如果在背面法线取反
struct hit_record
{
    point3 p;//交点
    vec3 n;//交点法线
    double t;//交点t值
    bool front;//是否在物体表面
    inline void setFaceNormal(const vec3& o2p, const ray& r)
    {
        //o2p意为球心O到球面点P的向量
        front = dot(o2p, r.direction()) < 0;
        n = front ? o2p : -o2p;
    }
};

//纯虚函数
class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& record) const = 0;
};
#endif // !HITTABLE_H
