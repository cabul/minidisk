#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>

struct Point {
    double x;
    double y;

    double dist2(const Point &p) const;
    double dist(const Point &p) const;
};

inline bool operator==(Point a, Point b) { return a.x == b.x && a.y == b.y; }
inline bool operator!=(Point a, Point b) { return !(a == b); }

struct Disk {
    Point z;
    double r;

    bool contains(const Point &p) const { return z.dist2(p) <= 1.01 * (r * r); }

    Point randomPoint() const;

    static Disk create(const Point &a);
    static Disk create(const Point &a, const Point &b);
    static Disk create(const Point &a, const Point &b, const Point &c);
    static Disk create(const std::vector<Point> &points);
};

#endif // GEOMETRY_H
