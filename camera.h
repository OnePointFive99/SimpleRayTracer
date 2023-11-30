#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include"utils.h"

class camera
{
public:
	camera() 
	{
        const auto aspect_ratio = 16.0 / 9.0;//16:9
        // 相机
        auto viewport_height = 2.0;//视口高
        auto viewport_width = viewport_height * aspect_ratio;//视口宽
        auto focal_length = 1.0;//焦距

        //坐标轴和原点
        origin = point3(0, 0, 0);
        horizontal = vec3(viewport_width, 0, 0);
        vertical = vec3(0, viewport_height, 0);
        // (-viewport_width/2, -viewport_height/2, -focal_length)
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
	};

    ray get_ray(double u, double v) const
    {
        return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }

private:
    point3 origin;
    vec3 horizontal;
    vec3 vertical;
    point3 lower_left_corner;
};

#endif // !CAMERA_H
