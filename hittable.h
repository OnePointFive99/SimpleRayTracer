#pragma once
#ifndef HITTABLE_H
#define HITTABLE_H
#include"vec3.h"
#include"ray.h"
#include"material.h"

//´¿Ðéº¯Êý
class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& record) const = 0;
};
#endif // !HITTABLE_H
