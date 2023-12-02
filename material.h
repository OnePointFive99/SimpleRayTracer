#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H
#include"utils.h"

class material;

struct hit_record
{
    point3 p;//����
    vec3 n;//���㷨��
    double t;//����tֵ
    bool front;//�Ƿ����������
    shared_ptr<material> mat_ptr;//����ָ��
    inline void setFaceNormal(const vec3& o2p, const ray& r)
    {
        //o2p��Ϊ����O�������P������
        front = dot(o2p, r.direction()) < 0;
        n = front ? o2p : -o2p;
    }
};

class material {
public:
    virtual bool scatter(const ray& r, const hit_record& rec, color& c, ray& scattered) const = 0;
};

//��¼���㣬���㷨�ߣ�����tֵ�������Ƿ���������棬����ڱ��淨��ȡ��


class lambertian : public material {
public:
    color albedo;//������
    lambertian(const color& a) : albedo(a){}
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& c, ray& scattered) const override {
        //point3 target = rec.p + rec.n + random_point_on_unit_sphere(); ʡ��rec.p + rec.n + random_point_on_unit_sphere()-rec.p
        vec3 dir = rec.n + random_point_on_unit_sphere();
        if (dir.near_zero())//���䷽��Ϊ0
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
    color albedo;//������
    lambertian_insphere(const color& a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& c, ray& scattered) const override {
        //point3 target = rec.p + rec.n + random_point_on_unit_sphere(); ʡ��rec.p + rec.n + random_point_on_unit_sphere()-rec.p
        vec3 dir = rec.n + random_point_in_unit_sphere();
        if (dir.near_zero())//���䷽��Ϊ0
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
    color albedo;//������
    lambertian_hemisphere(const color& a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& c, ray& scattered) const override {
        //point3 target = rec.p + rec.n + random_point_on_unit_sphere(); ʡ��rec.p + rec.n + random_point_on_unit_sphere()-rec.p
        vec3 dir = rec.n + random_point_in_hemisphere(rec.n);
        //�����жϣ���nһ��ͬ��
        scattered = ray(rec.p, dir);
        c = albedo;
        return true;
    }
};

class metal : public material {
public:
    color albedo;//������
    double fuzz;//Glossy�����Ŷ�ϵ��
    metal(const color& a, const double f) : albedo(a), fuzz(f < 1 ? f : 1) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& c, ray& scattered) const override {
        //point3 target = rec.p + rec.n + random_point_on_unit_sphere(); ʡ��rec.p + rec.n + random_point_on_unit_sphere()-rec.p
        vec3 dir = mirror_reflect(normalize(r_in.direction()), rec.n);//�������ӦΪ��λ����������õ���Ҳ�ǵ�λ����
        scattered = ray(rec.p, dir + fuzz * random_point_in_unit_sphere());
        c = albedo;
        return (dot(scattered.direction(), rec.n) > 0);
    }
};

#endif // !MATERIAL_H
