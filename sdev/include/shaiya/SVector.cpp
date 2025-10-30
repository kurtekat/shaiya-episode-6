#include <cmath>
#include "SVector.h"
using namespace shaiya;

// thanks, Cups ^^
double SVector::EuclideanDistance(SVector* u, SVector* v)
{
    auto dx = u->x - v->x;
    auto dz = u->z - v->z;
    return std::sqrt(dx * dx + dz * dz);
}

double SVector::Length(SVector* v)
{
    auto xx = v->x * v->x;
    auto yy = v->y * v->y;
    auto zz = v->z * v->z;
    return std::sqrt(xx + yy + zz);
}
