#include "app.h"

#include <algorithm>

void App::randomPoints(int count) {
    Disk center = {{0.5, 0.5}, 0.5};
    for (int i = 0; i < count; ++i) {
        points.push_back(center.randomPoint());
    }
}

void App::addPoint(double x, double y) {
    points.push_back({x, y});
    checkDisk();
}

void App::removePoint(double x, double y) {
    points.erase(std::remove_if(points.begin(), points.end(),
                                [&](Point pt) {
                                    return pt.dist2({x, y}) <= 0.0001;
                                }),
                 points.end());
    checkRset({x, y});
}

bool App::checkDisk() {
    for (auto pt : points) {
        if (!the_disk.contains(pt)) {
            dirty = true;
        }
    }
    return dirty;
}

bool App::checkRset(Point clk) {
    for (auto pt : the_rset) {
        if (clk.dist(pt) <= 0.001) {
            dirty = true;
        }
    }
    return dirty;
}

void App::reset() { points.clear(); }

Disk App::run() {
    if (dirty) {
        the_disk = minidisk(points.begin(), {});
    } else {
        backend.render(points, the_disk, {}, points.begin());
    }
    dirty = false;
    return the_disk;
}

Disk App::minidisk(PointIter p, RSet rset) {
    Disk d;
    if (p == points.end() || rset.size() == 3) {
        d = Disk::create(rset);
    } else {
        d = minidisk(p + 1, rset);
        if (!d.contains(*p)) {
            rset.push_back(*p);
            the_rset = rset;
            d = minidisk(p + 1, rset);
            rset.pop_back();
        }
    }
    backend.render(points, d, rset, p);
    return d;
}
