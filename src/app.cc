#include "app.h"

#include <cstdio>

#include <algorithm>

void App::seedPoints(int count) {
    printf("+ creating %d points\n", count);
    Disk center = {{padding + size / 2.0, padding + size / 2.0}, size / 2.0};
    for (int i = 0; i < count; ++i) {
        Point pt = center.randomPoint();
        printf("  (%.0f,%.0f)\n", pt.x, pt.y);
        points.push_back(pt);
    }
}

void App::addPoint(int x, int y) {
    printf("+ add point (%d,%d)\n", x, y);
    points.push_back({x + 0.0, y + 0.0});
}

void App::removePoint(int x, int y) {
    Point click = {x + 0.0, y + 0.0};
    auto rm = std::remove_if(points.begin(), points.end(), [&](Point pt) {
        return click.dist(pt) <= pointSize;
    });
    if (rm != points.end()) {
        printf("+ remove point (%d,%d)\n", x, y);
        points.erase(rm, points.end());
    }
}

void App::reset() {
    points.clear();
    printf("+ reset\n");
}

void App::redraw(sf::RenderWindow &window) {
    window.clear(sf::Color::White);

    sf::CircleShape circle(pointSize, pointDetail);
    circle.setOutlineThickness(pointStroke);
    circle.setOutlineColor(sf::Color::Black);
    circle.setFillColor(sf::Color::Red);

    for (const Point &pt : points) {
        circle.setPosition(round(pt.x - pointSize), round(pt.y - pointSize));
        window.draw(circle);
    }

    window.display();
}

void App::update() {
    frames.clear();
    Frame frame = {points.begin(), {}, {{0, 0}, 0}};
    minidisk(frame);
    curFrame = frames.begin();
}

void App::minidisk(Frame frame) {
    frames.push_back(frame);
    if (frame.pnext == points.end()) {
    } else {
        for (; frame.pnext != points.end(); ++frame.pnext) {
            frame.disk = minidisk(frame);
        }
    }
}

void App::start() {
    sf::RenderWindow window(
        sf::VideoMode(size + 2 * padding, size + 2 * padding), "Demo",
        sf::Style::Close | sf::Style::Titlebar);

    window.clear(sf::Color::White);
    window.display();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed: {
                window.close();
                break;
            }
            case sf::Event::KeyReleased: {
                switch (event.key.code) {
                case sf::Keyboard::Key::S: {
                    seedPoints();
                    break;
                }
                case sf::Keyboard::Key::R: {
                    reset();
                    break;
                }
                case sf::Keyboard::Key::Escape:
                    window.close();
                default:;
                }
                break;
            }
            case sf::Event::MouseButtonReleased: {
                auto btn = event.mouseButton;
                if (btn.button == sf::Mouse::Button::Left) {
                    addPoint(btn.x, btn.y);
                } else if (btn.button == sf::Mouse::Button::Right) {
                    removePoint(btn.x, btn.y);
                }
            }
            default:;
            }
            redraw(window);
        }
        sf::sleep(sf::milliseconds(50));
    }
}
