#include "cairo.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>

namespace {
double randnext() { return rand() / (RAND_MAX + 1.0); }
}

void CairoBackend::randomColor() {
    cairo_set_source_rgb(cr, randnext(), randnext(), randnext());
}

void CairoBackend::drawSetPoint(Point pt) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_arc(cr, pt.x * size, pt.y * size, 3, 0, 2 * M_PI);
    cairo_stroke(cr);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_arc(cr, pt.x * size, pt.y * size, 3, 0, 2 * M_PI);
    cairo_fill(cr);
}

void CairoBackend::drawUnsetPoint(Point pt) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_arc(cr, pt.x * size, pt.y * size, 3, 0, 2 * M_PI);
    cairo_stroke(cr);
    cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
    cairo_arc(cr, pt.x * size, pt.y * size, 3, 0, 2 * M_PI);
    cairo_fill(cr);
}

void CairoBackend::drawBoundaryPoint(Point pt) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_arc(cr, pt.x * size, pt.y * size, 3, 0, 2 * M_PI);
    cairo_stroke(cr);
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_arc(cr, pt.x * size, pt.y * size, 3, 0, 2 * M_PI);
    cairo_fill(cr);
}

void CairoBackend::drawDisk(Disk dk) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_arc(cr, dk.z.x * size, dk.z.y * size, dk.r * size, 0, 2 * M_PI);
    cairo_stroke(cr);
}

CairoBackend::CairoBackend(std::string out, int size, int padding)
    : out(out), size(size), padding(padding), realsize(size + padding * 2) {
    surf = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, realsize, realsize);
    cr = cairo_create(surf);
    counter = 0;
    outsize = out.size() + 20;
    outfile = new char[outsize];
}

CairoBackend::~CairoBackend() {
    delete[] outfile;
    cairo_surface_destroy(surf);
    cairo_destroy(cr);
}

void CairoBackend::render(const std::vector<Point> &points, Disk disk,
                          const std::vector<Point> &rset,
                          const App::PointIter &pnext) {
    cairo_set_source_rgb(cr, 255, 255, 255);
    cairo_rectangle(cr, 0, 0, realsize, realsize);
    cairo_fill(cr);

    cairo_translate(cr, padding + 0.0, padding + 0.0);
    cairo_set_source_rgb(cr, 0, 0, 0);

    drawDisk(disk);

    for (auto pt = points.begin(); pt < pnext; ++pt) {
        drawUnsetPoint(*pt);
    }

    for (auto pt = pnext; pt < points.end(); ++pt) {
        drawSetPoint(*pt);
    }

    // for (auto pt : points) {
    //     drawPoint(pt);
    // }

    for (auto pt : rset) {
        drawBoundaryPoint(pt);
    }

    cairo_translate(cr, -padding + 0.0, -padding + 0.0);

    printf("frame %d\n", counter);
    snprintf(outfile, outsize, out.c_str(), counter++);

    cairo_surface_write_to_png(surf, outfile);
}
