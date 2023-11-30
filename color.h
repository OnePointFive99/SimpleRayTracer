#pragma once
#ifndef COLOR_H
#define COLOR_H

#include"vec3.h"
#include<iostream>
// 将输入数字限定到给的范围[min, max]内
inline double clamp(const double& num, const double& min, const double& max)
{
    if (num > max)return max;
    else if (num < min)return min;
    else {
        return num;
    }
}
//颜色值输出至ppm
void write_color(std::ostream& out, color pixel_color, const int& samples_per_pixel)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // 平均颜色
    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << std::endl;
}

#endif //!COLOR_H