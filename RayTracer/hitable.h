#ifndef HITABLEH
#define HITABLEH

#include <iostream>

#include "ray.h"

class material;

struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;
	material *mat_ptr;
};

std::ostream& operator<<(std::ostream &strm, const struct hit_record& rec)
{
	return strm << "HIT RECORD (t, p, normal, material)" << ;
}


class hitable
{
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif // !HITABLEH
