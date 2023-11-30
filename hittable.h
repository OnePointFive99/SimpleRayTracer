#pragma once
#ifndef HITTABLE_H
#include"vec3.h"
#include"ray.h"

//��¼���㣬���㷨�ߣ�����tֵ�������Ƿ���������棬����ڱ��淨��ȡ��
struct hit_record
{
    point3 p;//����
    vec3 n;//���㷨��
    double t;//����tֵ
    bool front;//�Ƿ����������
    inline void setFaceNormal(const vec3& o2p, const ray& r)
    {
        //o2p��Ϊ����O�������P������
        front = dot(o2p, r.direction()) < 0;
        n = front ? o2p : -o2p;
    }
};

//���麯��
class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& record) const = 0;
};
#endif // !HITTABLE_H
