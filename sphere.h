#pragma once
#ifndef SPHERE_H
#define SPHERE_H
#include"hittable.h"
//�����࣬������hittable����
//���캯��
//�Զ��幹�캯��
//��������
//�����麯��

class sphere : public hittable
{
public:
    point3 center;//����
    double radius;//�뾶
    shared_ptr<material> mat_ptr; //����
    sphere(){}
    sphere(const point3& c, const double& r, const shared_ptr<material>& m):center(c), radius(r), mat_ptr(m) {}
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& record) const override;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& record) const
{
    //Ӳ����������t�ķ��� b*b * t^2 + 2*b*(A-C) * t + (A-C)^2 - r^2 = 0
    //��ʽ��һ����ϵ��Ϊż���������ʽ�ɻ���
    vec3 p_c = r.origin() - center;//A-C
    //auto a = dot(r.direction(), r.direction());����length_squared()
    auto a = r.direction().length_squared();
    //auto b = 2.0 * dot(r.direction(), p_c);
    auto h = dot(r.direction(), p_c);
    auto c = dot(p_c, p_c) - radius * radius;
    //auto result = b * b - 4 * a * c;
    auto result = h * h - a * c;
    if (result < 0)return false;
    
    //�ҵ���������������ĵ�
    auto t = (-h - sqrt(result)) / a;
    if (t < t_min || t_max < t)
    {
        t = (-h + sqrt(result)) / a;
        if (t < t_min || t_max < t)return false;//�����㶼���ڿ��ӷ�Χ��
    }

    //��¼������Ϣ
    record.t = t;
    record.p = r.at(t);
    vec3 o2p = normalize(r.at(t) - center);//�������ĵ��������
    record.setFaceNormal(o2p, r);
    record.mat_ptr = mat_ptr;
    return true;
}
#endif // !SPHERE_H

