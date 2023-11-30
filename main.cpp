#include"utils.h"
#include"hittable_list.h"
#include"sphere.h"


#include <iostream>

color ray_color(ray& r, const hittable_list& world)
{
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)>0)
    {
        return (color(1,1,1) + rec.n) * 0.5;//��Χ�仯Ϊ[0,1]
    }
    else {
        vec3 unit_direction = normalize(r.direction());
        // y��һ��Ϊ[-1,1]֮����ӳ�䵽[0,1]��Ϊ���ϵ��
        auto t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
    }
}

int main() {

    // ͼƬ
    const auto aspect_ratio = 16.0 / 9.0;//16:9
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    //����
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));



    // ���
    auto viewport_height = 2.0;//�ӿڸ�
    auto viewport_width = viewport_height * aspect_ratio;//�ӿڿ�
    auto focal_length = 1.0;//����

    //�������ԭ��
    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    // (-viewport_width/2, -viewport_height/2, -focal_length)
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    //��Ⱦ

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    //���ϵ�����
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone\n";
}