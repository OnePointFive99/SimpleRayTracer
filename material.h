#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H
#include"utils.h"

class material;

struct hit_record
{
    point3 p;//交点
    vec3 n;//交点法线
    double t;//交点t值
    bool front;//是否在物体表面
    shared_ptr<material> mat_ptr;//材质指针
    inline void setFaceNormal(const vec3& o2p, const ray& r)
    {
        //o2p意为球心O到球面点P的向量
        front = dot(o2p, r.direction()) < 0;
        n = front ? o2p : -o2p;
    }
};

class material {
public:
    virtual bool scatter(const ray& r, const hit_record& rec, color& c, ray& scattered) const = 0;
};

//记录交点，交点法线，交点t值，交点是否在物体表面，如果在背面法线取反


class lambertian : public material {
public:
    color albedo;//反射率
    lambertian(const color& a) : albedo(a){}
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& c, ray& scattered) const override {
        //point3 target = rec.p + rec.n + random_point_on_unit_sphere(); 省略rec.p + rec.n + random_point_on_unit_sphere()-rec.p
        vec3 dir = rec.n + random_point_on_unit_sphere();
        if (dir.near_zero())//反射方向为0
        {
            dir = rec.n;
        }
        scattered = ray(rec.p, dir);
        c = albedo;
        return true;
    }
};

class lambertian_insphere : public material {
public:
    color albedo;//反射率
    lambertian_insphere(const color& a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& c, ray& scattered) const override {
        //point3 target = rec.p + rec.n + random_point_on_unit_sphere(); 省略rec.p + rec.n + random_point_on_unit_sphere()-rec.p
        vec3 dir = rec.n + random_point_in_unit_sphere();
        if (dir.near_zero())//反射方向为0
        {
            dir = rec.n;
        }
        scattered = ray(rec.p, dir);
        c = albedo;
        return true;
    }
};

class lambertian_hemisphere : public material {
public:
    color albedo;//反射率
    lambertian_hemisphere(const color& a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& c, ray& scattered) const override {
        //point3 target = rec.p + rec.n + random_point_on_unit_sphere(); 省略rec.p + rec.n + random_point_on_unit_sphere()-rec.p
        vec3 dir = rec.n + random_point_in_hemisphere(rec.n);
        //不用判断，与n一定同向
        scattered = ray(rec.p, dir);
        c = albedo;
        return true;
    }
};

class metal : public material {
public:
    color albedo;//反射率
    double fuzz;//Glossy反射扰动系数
    metal(const color& a, const double f) : albedo(a), fuzz(f < 1 ? f : 1) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& c, ray& scattered) const override {
        //point3 target = rec.p + rec.n + random_point_on_unit_sphere(); 省略rec.p + rec.n + random_point_on_unit_sphere()-rec.p
        vec3 dir = mirror_reflect(normalize(r_in.direction()), rec.n);//入射光线应为单位向量，计算得到的也是单位向量
        scattered = ray(rec.p, dir + fuzz * random_point_in_unit_sphere());
        c = albedo;
        return (dot(scattered.direction(), rec.n) > 0);
    }
};

#endif // !MATERIAL_H
