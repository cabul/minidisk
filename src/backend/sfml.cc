#include "sfml.h"

void SfmlBackend::drawDisk(Disk dk) {
    sf::CircleShape circle(dk.r*size, 64);
    circle.setPosition(round(dk.z.x*size+padding-(dk.r*size)), round(dk.z.y*size+padding-(dk.r*size)));
    circle.setFillColor(sf::Color(255,255,255));
    circle.setOutlineColor(sf::Color(0,0,0));
    circle.setOutlineThickness(2);
    window->draw(circle);
}

void SfmlBackend::drawBoundPoint(Point pt) {
    sf::CircleShape circle(4, 64);
    circle.setPosition(round(pt.x*size+padding-2), round(pt.y*size+padding-2));
    circle.setFillColor(sf::Color(255,0,0));
    circle.setOutlineColor(sf::Color(0,0,0));
    circle.setOutlineThickness(2);
    window->draw(circle);
}

void SfmlBackend::drawSetPoint(Point pt) {
    sf::CircleShape circle(4, 64);
    circle.setPosition(round(pt.x*size+padding-2), round(pt.y*size+padding-2));
    circle.setFillColor(sf::Color(255,255,255));
    circle.setOutlineColor(sf::Color(0,0,0));
    circle.setOutlineThickness(2);
    window->draw(circle);
}

void SfmlBackend::drawUnsetPoint(Point pt) {
    sf::CircleShape circle(4, 64);
    circle.setPosition(round(pt.x*size+padding-2), round(pt.y*size+padding-2));
    circle.setFillColor(sf::Color(128,128,128));
    circle.setOutlineColor(sf::Color(0,0,0));
    circle.setOutlineThickness(2);
    window->draw(circle);
}

SfmlBackend::SfmlBackend(int size, int padding)
    : size(size), padding(padding), realsize(size + padding * 2) {
    window = new sf::RenderWindow(sf::VideoMode(realsize, realsize), "Demo", sf::Style::Titlebar|sf::Style::Close);
    window->clear(sf::Color(255, 255, 255));
    window->display();
}

SfmlBackend::~SfmlBackend() { delete window; }

void SfmlBackend::render(const std::vector<Point> &points, Disk disk,
                         const std::vector<Point> &rset,
                         const App::PointIter &pnext) {
    if (!window) return;

    window->clear(sf::Color(255, 255, 255));

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
        drawBoundPoint(pt);
    }

    window->display();

    sf::sleep(sf::milliseconds(10));
}

void SfmlBackend::start() {
    if (!window) return;

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (auto cb : left_clk) {
                        cb((event.mouseButton.x - padding + 0.0) / size,
                           (event.mouseButton.y - padding + 0.0) / size);
                    }
                } else {
                    for (auto cb : right_clk) {
                        cb((event.mouseButton.x - padding + 0.0) / size,
                           (event.mouseButton.y - padding + 0.0) / size);
                    }
                }
            }
        }
    }
}
