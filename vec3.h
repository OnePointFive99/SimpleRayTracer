#pragma once
#ifndef VEC3_H
#define VEC3_H

#include<cmath>
#include<ostream>


class vec3 {
public:
    double e[3];//��ʵ���Ǹ�����
    vec3() :e{0, 0, 0} {}//Ĭ�Ϲ��캯��
    vec3(double e0, double e1, double e2) : e{e0, e1, e2}{}//���캯��

    double x() const { return e[0]; }//vec.x
    double y() const { return e[1]; }//vec.y
    double z() const { return e[2]; }//vec.z

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }//���ظ���
    double operator[](int i) const { return e[i]; }//�����±������ ������vec3�õĳ�������
    double& operator[](int i) { return e[i]; }//�����±������ �����޸�vec3

    vec3& operator+=(const vec3& v)//����+=�����
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(const double t) //����*=�����
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(const double t) {//����/=�����
        return *this *= 1 / t;
    }

    double length() const
    {
        return sqrt(length_squared());
    }

    double length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    // �Ƿ�ӽ�0
    bool near_zero() const
    {
        const auto s = 1e-9;
        return (fabs(e[0] < s) && (fabs(e[1] < s) && fabs(e[2] < s)));
    }
};
//������vec3������������3D point ��color
using point3 = vec3;
using color = vec3;




/*���ߺ���   ��Ҫ�����������*/
//���
inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}
//�����ӷ�
inline  vec3 operator+(const vec3& v1, const vec3& v2)
{
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}
//��������
inline vec3 operator-(const vec3& v1, const vec3& v2)
{
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}
//������ӦԪ�����
inline vec3 operator*(const vec3& v1, const vec3& v2)
{
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}
//����������
inline vec3 operator*(double k, const vec3& v2)
{
    return vec3(k* v2.e[0], k * v2.e[1], k * v2.e[2]);
}

inline vec3 operator*(const vec3& v2, double k)
{
    return k * v2;
}
//�������Ա���
inline vec3 operator/(const vec3& v2, double k)
{
    return (1/k) * v2;
}

//���
inline double dot(const vec3& v1, const vec3& v2)
{
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

//���
inline vec3 corss(const vec3& v1, const vec3& v2)
{
    return vec3(v1.e[1] * v2.e[2] - v2.e[1] * v1.e[2],
                v2.e[0] * v1.e[2] - v1.e[2] * v2.e[0],
                v1.e[0] * v2.e[1] - v2.e[0] * v1.e[1]);
}

//��һ��
inline vec3 normalize(vec3 v)
{
    return v / v.length();
}




#endif // !VEC3_H
