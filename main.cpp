#include"utils.h"
#include"hittable_list.h"
#include"sphere.h"
#include"camera.h"

#include <iostream>

color ray_color(ray& r, const hittable_list& world, int depth, double RR)
{
    hit_record rec;
    // 这里的t的下界设为0.001是为了防止一些光线弹射到物体上得到的t非常接近0，比如可能出现0.000001这样的值
    if (world.hit(r, 0.001, infinity, rec))
    {
        ray scattered;
        color c;
        if (depth < 0 && random_double() >= RR)return color(0, 0, 0);//概率停止反射 易产生噪点
        if (rec.mat_ptr->scatter(r, rec, c, scattered))
        {
            return c * ray_color(scattered, world, depth - 1, RR) / RR;//要除以RR才能得到正常的期望颜色
        }
        return color(0, 0, 0);
    }
    else {
        vec3 unit_direction = normalize(r.direction());
        // y归一化为[-1,1]之后再映射到[0,1]作为混合系数
        auto t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
    }
}

int main() {
    // 相机
    camera cam;

    // 图片
    const auto aspect_ratio = 16.0 / 9.0;//16:9
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int sample_per_pixel = 100;
    const int max_depth = 3;
    const double RR = 0.9;

    // 世界
    hittable_list world;
    
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5, material_center));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, material_ground));
    world.add(make_shared<sphere>(point3(-1, 0, -1), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1, 0, -1), 0.5, material_right));


    // 渲染
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    //左上到右下
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < sample_per_pixel; ++s)
            {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth, RR);
            }
            write_color(std::cout, pixel_color, sample_per_pixel);
        }
    }
    std::cerr << "\nDone\n";
}