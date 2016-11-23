#ifndef APP_H
#define APP_H

#include <cstdlib>
#include <ctime>

#include <vector>

#include <SFML/Graphics.hpp>

#include "geometry.h"

class App {
    static constexpr int pointSize = 4;
    static constexpr int pointDetail = 128;
    static constexpr int pointStroke = 2;

    typedef std::vector<Point>::const_iterator PointRef;

    struct Frame {
        PointRef pnext;
        std::vector<Point> rset;
        Disk disk;
    };

    typedef std::vector<Frame>::const_iterator FrameRef;

    std::vector<Frame> frames;

    int size, padding;
    std::vector<Point> points;
    Disk disk = {{0, 0}, 0};

    FrameRef curFrame;

    void redraw(sf::RenderWindow &window);

    void seedPoints(int count = 10);
    void addPoint(int x, int y);
    void removePoint(int x, int y);

    void reset();

    void update();
    void minidisk(Frame frame);

  public:
    App(int size, int padding = 10) : size(size), padding(padding) {}

    void start();
};

#endif // APP_H
