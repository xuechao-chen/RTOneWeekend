#pragma once
#include "hitable.h"

class sphere : public hitable
{
public:
	sphere() {}
	sphere(vec3 cen, double r, material* m) : center(cen), radius(r), mat_ptr(m) {}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

	vec3 center;
	double radius;
	material* mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	vec3 oc = r.origin() - center;
	
	double a = dot(r.direction(), r.direction());
	double b = dot(oc, r.direction());
	double c = dot(oc, oc) - radius * radius;
	double discriminant = b * b - a * c;

	if (discriminant > 0)
	{
		double tmp = (-b - sqrt(b*b - a * c)) / a;
		if (tmp < t_max && tmp > t_min)
		{
			rec.t = tmp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		tmp = (-b + sqrt(b*b - a * c)) / a;
		if (tmp < t_max && tmp> t_min)
		{
			rec.t = tmp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}