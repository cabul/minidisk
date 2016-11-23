#include "geometry.h"

#include <cassert>
#include <cmath>
#include <cstdlib>

namespace {
double nonzero(double a) {
    const double lim = 1e-10;
    return (a < lim && a > -lim) ? lim : a;
}
double randnext() { return rand() / (RAND_MAX + 1.0); }
}

double Point::dist2(const Point &p) const {
    double dx = p.x - x;
    double dy = p.y - y;
    return dx * dx + dy * dy;
}

double Point::dist(const Point &p) const { return sqrt(dist2(p)); }

Point Disk::randomPoint() const {
    double t = 2 * M_PI * randnext();
    double u = randnext() + randnext();
    double rr = (u > 1.0) ? (2 - u) : u;
    rr *= r;
    return {rr * cos(t) + z.x, rr * sin(t) + z.y};
}

Disk Disk::create(const Point &a) {
    return {a, 0};
}

Disk Disk::create(const Point &a, const Point &b) {
    Point z = {(a.x + b.x) / 2, (a.y + b.y) / 2};
    double r = z.dist(a);
    return {z, r};
}

Disk Disk::create(const Point &a, const Point &b, const Point &c) {
    const double ax2 = a.x * a.x;
    const double bx2 = b.x * b.x;
    const double cx2 = c.x * c.x;
    const double ay2 = a.y * a.y;
    const double by2 = b.y * b.y;
    const double cy2 = c.y * c.y;
    const double m1 = (b.y - a.y) / nonzero(b.x - a.x);
    const double k1 = (bx2 - ax2 + by2 - ay2) / nonzero(b.x - a.x) / 2;
    const double m2 = (c.y - a.y) / nonzero(c.x - a.x);
    const double k2 = (cx2 - ax2 + cy2 - ay2) / nonzero(c.x - a.x) / 2;
    const double zy = (k1 - k2) / nonzero(m1 - m2);
    Point z = {k1 - m1 * zy, zy};
    double r = z.dist(a);
    return {z, r};
}
