#include"utils.h"
#include"hittable_list.h"
#include"sphere.h"
#include"camera.h"

#include <iostream>

color ray_color(ray& r, const hittable_list& world)
{
    auto RR = 0.8;//俄罗斯轮盘赌的生存概率
    hit_record rec;
    // 这里的t的下界设为0.001是为了防止一些光线弹射到物体上得到的t非常接近0，比如可能出现0.000001这样的值
    if (world.hit(r, 0.001, infinity, rec))
    {
        if (random_double() > RR)return color(0, 0, 0);//概率停止反射
        // 随机选择漫反射光线弹射方向
        point3 target = rec.p + rec.n + random_point_in_unit_sphere();
        ray bounce = ray(rec.p, target - rec.p);
        // 只有0.5的光线发生下一次弹射，其他的被吸收
        return 0.5 * ray_color(bounce, world) / RR;//要除以RR才能得到正常的期望颜色
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

    // 世界
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

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
                pixel_color += ray_color(r, world);
            }
            write_color(std::cout, pixel_color, sample_per_pixel);
        }
    }
    std::cerr << "\nDone\n";
}