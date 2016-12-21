#ifndef APP_H
#define APP_H

#include <vector>

#include "geometry.h"

class App {
  public:
    typedef std::vector<Point>::const_iterator PointIter;
    typedef std::vector<Point> RSet;

    class Backend {
      public:
        virtual void render(const std::vector<Point> &points, Disk disk,
                            const std::vector<Point> &rset,
                            const PointIter &pt) = 0;
    };

  private:

    bool dirty = false;

    Backend &backend;

    std::vector<Point> points;

    Disk the_disk;
    std::vector<Point> the_rset;

    Disk minidisk(PointIter pnext, RSet rset);

    bool checkDisk();
    bool checkRset(Point pt);

  public:
    App(Backend &backend) : backend(backend){};

    void randomPoints(int count);
    void addPoint(double x, double y);
    void removePoint(double x, double y);
    void reset();

    Disk run();
};

#endif // APP_H
