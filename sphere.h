#pragma once
#ifndef SPHERE_H
#define SPHERE_H
#include"hittable.h"
//球体类，派生自hittable基类
//构造函数
//自定义构造函数
//析构函数
//重载虚函数

class sphere : public hittable
{
public:
    point3 center;//球心
    double radius;//半径
    shared_ptr<material> mat_ptr; //材质
    sphere(){}
    sphere(const point3& c, const double& r, const shared_ptr<material>& m):center(c), radius(r), mat_ptr(m) {}
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& record) const override;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& record) const
{
    //硬编码求解关于t的方程 b*b * t^2 + 2*b*(A-C) * t + (A-C)^2 - r^2 = 0
    //上式子一次项系数为偶数，求根公式可化简
    vec3 p_c = r.origin() - center;//A-C
    //auto a = dot(r.direction(), r.direction());改用length_squared()
    auto a = r.direction().length_squared();
    //auto b = 2.0 * dot(r.direction(), p_c);
    auto h = dot(r.direction(), p_c);
    auto c = dot(p_c, p_c) - radius * radius;
    //auto result = b * b - 4 * a * c;
    auto result = h * h - a * c;
    if (result < 0)return false;
    
    //找到满足条件的最近的点
    auto t = (-h - sqrt(result)) / a;
    if (t < t_min || t_max < t)
    {
        t = (-h + sqrt(result)) / a;
        if (t < t_min || t_max < t)return false;//两个点都不在可视范围内
    }

    //记录交点信息
    record.t = t;
    record.p = r.at(t);
    vec3 o2p = normalize(r.at(t) - center);//计算球心到点的向量
    record.setFaceNormal(o2p, r);
    record.mat_ptr = mat_ptr;
    return true;
}
#endif // !SPHERE_H

