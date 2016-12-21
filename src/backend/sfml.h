#ifndef BACKEND_SFML_H
#define BACKEND_SFML_H

#include "../app.h"

#include <SFML/Graphics.hpp>

#include <functional>
#include <vector>

class SfmlBackend : public App::Backend {
  public:
    typedef std::function<void(double, double)> clk_handler;

  private:
    int size;
    int padding;
    int realsize;

    sf::RenderWindow *window = nullptr;

    std::vector<clk_handler> left_clk;
    std::vector<clk_handler> right_clk;

    void drawSetPoint(Point pt);
    void drawBoundPoint(Point pt);
    void drawUnsetPoint(Point pt);
    void drawDisk(Disk dk);

  public:
    SfmlBackend(int size, int padding);
    ~SfmlBackend();

    void render(const std::vector<Point> &points, Disk disk,
                const std::vector<Point> &rset, const App::PointIter &pt);

    void onLeftClick(clk_handler cb) { left_clk.push_back(cb); }
    void onRightClick(clk_handler cb) { right_clk.push_back(cb); }

    void start();
};

#endif // BACKEND_SFML_H
