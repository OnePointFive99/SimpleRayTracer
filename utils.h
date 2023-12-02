#pragma once
#ifndef UTILS_H
#define UTILS_H

//常用头文件
#include"vec3.h"
#include"ray.h"
#include"color.h"
#include<random>

using std::make_shared;
using std::shared_ptr;


//定义常量
const double infinity = std::numeric_limits<double>::infinity();//double的正无穷
const double pi = 3.1415926535897932385;

//工具函数
//角度转弧度
inline double degree2Radian(double deg)
{
    return deg / 180.0 * pi;
}
//生成[0,1]的随机数
inline double random_double()
{
    //0~1的均匀分布
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator(std::random_device{}());//random_device用于生成均匀整数
    /*
    功能：
        std::mt19937是伪随机数产生器，用于产生高性能的随机数。 C++11引入。
    用法：
        头文件<random>
        返回值为unsigned int,接收一个unsigned int数作为种子。所以可以如下定义
        std::mt19937 mt_rand(std::random_device{}());
        std::mt19937 mt_rand(time(0));
        std::mt19937 mt_rand(std::chrono::system_clock::now().time_since_epoch().count());
    名称由来：
        mt是因为这个伪随机数产生器基于Mersenne Twister算法。
        19937是因为产生随的机数的周期长，可达到2^19937-1。
    */
    return distribution(generator);
}

//生成[min, max]的随机数
inline double random_double(const double& min, const double& max)
{
    return min + (max - min) * random_double();
}

//生成[0,1]的随机向量
inline vec3 random_vector()
{
    return vec3(random_double(), random_double(), random_double());
}

// 生成在[min, max]的随机向量
inline vec3 random_vector(const double& min, const double& max)
{
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

// 生成单位球内的随机一点
inline point3 random_point_in_unit_sphere()
{
    while (true)
    {
        auto p = random_vector(-1, 1);
        if (p.length_squared() >= 1)continue;
        return p;
    }
}

// 生成单位球面上的随机一点
inline point3 random_point_on_unit_sphere()
{
    return normalize(random_point_in_unit_sphere());
}

// 半球内随机取点
inline point3 random_point_in_hemisphere(const vec3& n)
{
    vec3 p = random_point_in_unit_sphere();
    if (dot(p, n) < 0)return -p;//不在同一半球
    else {
        return p;
    }
}

// 镜面反射方向
inline vec3 mirror_reflect(const vec3& v, const vec3& n)
{
    vec3 b = dot(-v, n) * n;
    return v + 2 * b;
}

//计算折射光线
inline vec3 refract(const vec3& R, const vec3& n, double etai_over_etat)
{
    auto cos_theta = fmin(dot(-R, n), 1.0);
    vec3 r_prep = etai_over_etat * (R + cos_theta * n);
    vec3 r_parallel = -sqrt(fabs(1.0 - r_prep.length_squared())) * n;
    return r_prep + r_parallel;
}


#endif // !UTILS_H

