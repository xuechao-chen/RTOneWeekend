#pragma once
#include "hitable.h"

class hitable_list : public hitable
{
public:
	hitable_list() {}
	hitable_list(hitable **l, int n) { list = l; list_size = n; }

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

	hitable **list;
	int list_size;
};


bool hitable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	hit_record tmp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;

	for (int i = 0; i < list_size; i++)
	{
		if (list[i]->hit(r, t_min, closest_so_far, tmp_rec))
		{
			hit_anything = true;
			closest_so_far = tmp_rec.t;
			rec = tmp_rec;
		}
	}
	return hit_anything;
}

