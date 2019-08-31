#pragma once
#include <stdlib.h>
#include "vec3.h"

#define M_PI 3.1415927

double drand()
{
	return (double)rand() / RAND_MAX;
}

vec3 random_in_unit_sphere()
{
	vec3 p;

	do
	{
		p = 2.0 * vec3(drand(), drand(), drand()) - vec3(1.0, 1.0, 1.0);
	} while (p.sqrt_length() >= 1.0);

	return p;
}

vec3 random_in_unit_disk()
{
	vec3 p;

	do
	{
		p = 2.0 * vec3(drand(), drand(), 0) - vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0);

	return p;
}

double schlick(double cosine, double ref_idx)
{
	double r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0)*pow((1 - cosine), 5);
}

vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n)*n;
}

bool refract(const vec3& v, const vec3& n, double ni_over_nt, vec3& refracted)
{
	vec3 uv = unit_vector(v);
	double dt = dot(uv, n);
	double discriminant = 1.0 - ni_over_nt * ni_over_nt*(1 - dt * dt);
	if (discriminant > 0)
	{
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else
	{
		return false;
	}
}