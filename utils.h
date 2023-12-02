#pragma once
#ifndef UTILS_H
#define UTILS_H

//����ͷ�ļ�
#include"vec3.h"
#include"ray.h"
#include"color.h"
#include<random>

using std::make_shared;
using std::shared_ptr;


//���峣��
const double infinity = std::numeric_limits<double>::infinity();//double��������
const double pi = 3.1415926535897932385;

//���ߺ���
//�Ƕ�ת����
inline double degree2Radian(double deg)
{
    return deg / 180.0 * pi;
}
//����[0,1]�������
inline double random_double()
{
    //0~1�ľ��ȷֲ�
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator(std::random_device{}());//random_device�������ɾ�������
    /*
    ���ܣ�
        std::mt19937��α����������������ڲ��������ܵ�������� C++11���롣
    �÷���
        ͷ�ļ�<random>
        ����ֵΪunsigned int,����һ��unsigned int����Ϊ���ӡ����Կ������¶���
        std::mt19937 mt_rand(std::random_device{}());
        std::mt19937 mt_rand(time(0));
        std::mt19937 mt_rand(std::chrono::system_clock::now().time_since_epoch().count());
    ����������
        mt����Ϊ���α���������������Mersenne Twister�㷨��
        19937����Ϊ������Ļ��������ڳ����ɴﵽ2^19937-1��
    */
    return distribution(generator);
}

//����[min, max]�������
inline double random_double(const double& min, const double& max)
{
    return min + (max - min) * random_double();
}

//����[0,1]���������
inline vec3 random_vector()
{
    return vec3(random_double(), random_double(), random_double());
}

// ������[min, max]���������
inline vec3 random_vector(const double& min, const double& max)
{
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

// ���ɵ�λ���ڵ����һ��
inline point3 random_point_in_unit_sphere()
{
    while (true)
    {
        auto p = random_vector(-1, 1);
        if (p.length_squared() >= 1)continue;
        return p;
    }
}

// ���ɵ�λ�����ϵ����һ��
inline point3 random_point_on_unit_sphere()
{
    return normalize(random_point_in_unit_sphere());
}

// ���������ȡ��
inline point3 random_point_in_hemisphere(const vec3& n)
{
    vec3 p = random_point_in_unit_sphere();
    if (dot(p, n) < 0)return -p;//����ͬһ����
    else {
        return p;
    }
}

// ���淴�䷽��
inline vec3 mirror_reflect(const vec3& v, const vec3& n)
{
    vec3 b = dot(-v, n) * n;
    return v + 2 * b;
}

//�����������
inline vec3 refract(const vec3& R, const vec3& n, double etai_over_etat)
{
    auto cos_theta = fmin(dot(-R, n), 1.0);
    vec3 r_prep = etai_over_etat * (R + cos_theta * n);
    vec3 r_parallel = -sqrt(fabs(1.0 - r_prep.length_squared())) * n;
    return r_prep + r_parallel;
}


#endif // !UTILS_H

