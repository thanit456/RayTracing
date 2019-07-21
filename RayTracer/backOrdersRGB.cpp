#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include <random>
#include "material.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define	CHANNEL_NUM 3

//float hit_sphere(const vec3& center, float radius, const ray& r)
//{
//	vec3 oc = r.origin() - center;
//	float a = dot(r.direction(), r.direction());
//	float b = 2.0 * dot(oc, r.direction());
//	float c = dot(oc, oc) - radius * radius;
//	float discriminant = b * b - 4 * a * c;
//	
//	if (discriminant < 0)
//	{
//		return -1.0;
//	}
//	else
//		return (-b + sqrt(discriminant)) / (2.0*a);
//}



vec3 color(const ray& r, hitable *world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec))
	{
		ray scattered;
		vec3 attenuation;
		std::cout << "DEPTH : " << depth << std::endl;
		std::cout << "scatter : " << (rec.mat_ptr)->scatter(r, rec, attenuation, scattered);
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * color(scattered, world, depth + 1);
		else
			return vec3(0, 0, 0);
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}

}

int main()
{
	const int width = 200, height = 100;
	const int randomAA = 100;

	uint8_t *pixels = new uint8_t[width * height * CHANNEL_NUM];

	std::cout << "size : " << width * height*CHANNEL_NUM << std::endl;
	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	hitable *list[4];
	//list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
	//list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0)));
	list[0] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2)));
	list[1] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8)));
	hitable *world = new hitable_list(list, 2);

	camera cam;

	int index = 0;

	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			vec3 col(0, 0, 0);
			
			for (int s = 0; s < randomAA; s++)
			{
				float u = float(i + rand()/(RAND_MAX + 1.0)) / float(width);
				float v = float(j + rand() / (RAND_MAX + 1.0)) / float(height);

				ray r = cam.get_ray(u, v);

				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world, 0);
			}

			col /= float(randomAA);
			
			// reduce absorption of diffusing object
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			//std::cout << index << " " << j << " " << i << std::endl;
			pixels[index++] = ir;
			pixels[index++] = ig;
			pixels[index++] = ib;

			//std::cout << ir << " " << ig << " " << ir << std::endl;

		}
	}

	stbi_write_png("metal.png", width, height, CHANNEL_NUM, pixels, width*CHANNEL_NUM);

	delete[] pixels;
}