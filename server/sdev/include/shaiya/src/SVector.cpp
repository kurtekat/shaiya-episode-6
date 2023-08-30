#include <cmath>
#include <include/shaiya/include/SVector.h>
using namespace shaiya;

// thanks, Cups ^^
double SVector::EuclideanDistance(SVector* u, SVector* v)
{
    auto dx = u->x - v->x;
    auto dz = u->z - v->z;
    return std::sqrt(dx * dx + dz * dz);
}
