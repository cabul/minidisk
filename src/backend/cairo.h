#ifndef BACKEND_CAIRO_H
#define BACKEND_CAIRO_H

#include <string>

#include <cairo.h>

#include "../app.h"

class CairoBackend : public App::Backend {
    std::string out;
    int size;
    int padding;
    int realsize;

    int counter;
    char *outfile;
    size_t outsize;

    cairo_t *cr;
    cairo_surface_t *surf;

    void drawSetPoint(Point pt);
    void drawUnsetPoint(Point pt);
    void drawBoundaryPoint(Point pt);
    void drawDisk(Disk dk);
    void randomColor();

  public:
    CairoBackend(std::string out, int size, int padding);
    ~CairoBackend();

    void render(const std::vector<Point> &points, Disk disk,
                const std::vector<Point> &rset, const App::PointIter &pt);
};

#endif // BACKEND_CAIRO_H
