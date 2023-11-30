#pragma once
#ifndef HITTABLE_LIST_H
#include<memory>
#include<vector>
#include"hittable.h"

using std::shared_ptr;

class hittable_list : public hittable
{
public:
    //存类的指针对象，用->访问对象成员
    std::vector<shared_ptr<hittable>> objects;
    hittable_list(){}
    hittable_list(shared_ptr<hittable> object) { add(object); }
    void clear() { objects.clear(); }
    void add(shared_ptr<hittable> object) { objects.push_back(object); }

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& record) const override;
};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& record) const
{
    hit_record tmp_record;
    bool hit_anything = false;
    //从最远t开始更新最近点的t
    auto closest_t = t_max;
    for (const auto& object : objects)
    {
        if (object->hit(r, t_min, closest_t, tmp_record))
        {
            hit_anything = true;
            closest_t = tmp_record.t;
            record = tmp_record;
        }
    }

    return hit_anything;
}



#endif // !HITTABLE_LIST_H

