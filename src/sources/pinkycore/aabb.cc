#include <algorithm>
#include <cmath>
#include <limits>
#include "aabb.h"

using namespace PinkyPi;

AABB::AABB():
	min(std::numeric_limits<PPFloat>::max()),
	max(-std::numeric_limits<PPFloat>::max())
{}

AABB::AABB(const PPFloat minval, const PPFloat maxval)
{
	if(minval < maxval) {
		min = Vector3(minval);
		max = Vector3(maxval);
	} else {
		min = Vector3(maxval);
		max = Vector3(minval);
	}
}

AABB::AABB(const Vector3 minvec, const Vector3 maxvec)
{
	for(int i = 0; i < 3; i++) {
		if(minvec.v[i] < maxvec.v[i]) {
			min.v[i] = minvec.v[i];
			max.v[i] = maxvec.v[i];
		} else {
			min.v[i] = maxvec.v[i];
			max.v[i] = minvec.v[i];
		}
	}
}

void AABB::clear() {
	min = Vector3(std::numeric_limits<PPFloat>::max());
	max = Vector3(-std::numeric_limits<PPFloat>::max());
}

Vector3 AABB::size() const {
	return max - min;
}

void AABB::expand(const Vector3 &p) {
	if(p.x < min.x) min.x = p.x;
	if(p.y < min.y) min.y = p.y;
	if(p.z < min.z) min.z = p.z;
	
	if(p.x > max.x) max.x = p.x;
	if(p.y > max.y) max.y = p.y;
	if(p.z > max.z) max.z = p.z;
}

void AABB::expand(const AABB &aabb) {
	if(min.x > aabb.min.x) min.x = aabb.min.x;
	if(min.y > aabb.min.y) min.y = aabb.min.y;
	if(min.z > aabb.min.z) min.z = aabb.min.z;
	
	if(max.x < aabb.max.x) max.x = aabb.max.x;
	if(max.y < aabb.max.y) max.y = aabb.max.y;
	if(max.z < aabb.max.z) max.z = aabb.max.z;
}

Vector3 AABB::centroid() const {
	return (min + max) * 0.5;
}

bool AABB::isInside(const Vector3 &p) const {
	return ((p.x > min.x && p.y > min.y && p.z > min.z) &&
			(p.x < max.x && p.y < max.y && p.z < max.z) );
}

bool AABB::isIntersect(const Ray &ray, PPFloat tnear, PPFloat tfar) const
{
    PPFloat t = intersection(ray, tnear, tfar);
    return t > 0.0;
}

PPFloat AABB::intersection(const Ray &ray, PPFloat tnear, PPFloat tfar) const {
	PPFloat largest_min = tnear;
    PPFloat smallest_max = tfar;
	
	for(int i = 0; i < 3; i++) {
		PPFloat vdiv = 1.0 / ray.direction.v[i];
		PPFloat tmpmin = (min.v[i] - ray.origin.v[i]) * vdiv;
		PPFloat tmpmax = (max.v[i] - ray.origin.v[i]) * vdiv;
        if(vdiv < 0.0) {
            std::swap(tmpmin, tmpmax);
        }
        
        largest_min = std::max(largest_min, tmpmin);
        smallest_max = std::min(smallest_max, tmpmax);
        
		if(smallest_max < largest_min) {
			return -1.0;
		}
	}
	
    return (largest_min > 0.0)? largest_min : smallest_max;
}
